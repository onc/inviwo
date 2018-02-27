/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Monday, January 29, 2018 - 14:13:45
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include "discretedata/connectivity.h"

namespace inviwo
{

    class ElementIterator;

/** \class StructuredGrid
    \brief A curvilinear grid in nD

    @author Anke Friederici and Tino Weinkauf
*/
class IVW_MODULE_DISCRETEDATA_API StructuredGrid : public Connectivity
{ 
// Construction / Deconstruction
public:
    /** \brief Create an nD grid
    *   @param gridDimension Dimension of grid (not vertices)
    *   @param gridSize Number of cells in each dimension, expect size gridDimension+1
    */
    StructuredGrid(GridPrimitive gridDimension, const std::vector<ind>& numCellsPerDim);
    virtual ~StructuredGrid() = default;

    ind getNumCellsInDimension(ind dim) const;

    virtual double getPrimitiveMeasure(GridPrimitive dim, ind index) const override;

// Methods
public:
    virtual std::vector<ind> getConnections(ind index, GridPrimitive from, GridPrimitive to) const;

//Attributes
protected:
    template<typename T>
    double computeHexVolume(ind index) const;

protected:
    std::vector<ind> NumCellsPerDimension;
};


template<typename T>
double StructuredGrid::computeHexVolume(ind index) const
{
    // Work with respective type
    std::shared_ptr<const DataChannel<T>> doubleVertices = std::dynamic_pointer_cast<const DataChannel<T>, const Channel>(Vertices);
    if (!doubleVertices)
        return -1;

    // Get all corner points.
    auto corners = getConnections(index, GridPrimitive::Volume, GridPrimitive::Vertex);
    IVW_ASSERT(corners.size() == 8, "Not a hexahedron.");

    // Tetrahedron corners
    static constexpr ind tetrahedra[5][4] =
        { {0, 3, 5, 6}
        , {0, 5, 3, 1}
        , {0, 6, 5, 4}
        , {0, 3, 6, 2}
        , {3, 5, 6, 7} };

    // Setup variables for measure calculation
    double measure = 0;
    double cornerMatrix[4][3];
    T vertex[3];

    // Calculate measure of 5 tetrahedra
    for (ind tet = 0; tet < 5; tet++)
    {
        for (ind corner = 0; corner < 4; corner++)
        {
            ind cornerIndex = corners[tetrahedra[tet][corner]];
            doubleVertices->fill(vertex, cornerIndex);
            for (ind dim = 0; dim < 3; ++dim)
            {
                cornerMatrix[corner][dim] = double(vertex[dim]);
            }
        }
        
        // Compute measure and sum
        measure += inviwo::util::tetrahedronVolume(cornerMatrix);
    }

    return measure;
}

} // namespace