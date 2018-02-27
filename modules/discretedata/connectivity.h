/*********************************************************************
 *  Author  : Tino Weinkauf and Anke Friederici
 *  Init    : Friday, August 11, 2017 - 16:10:52
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>

#include "discretedata/connectionmap.h"
#include "discretedata/datachannel.h"
#include "discretedata/util.h"

namespace inviwo
{


class ElementRange;
class ElementIterator;

/** \class Connectivity
    \brief Basis interface of all connectivity types.

    The connectivity between coordinates creates a mesh,
    a graph, a cell complex, or some other structure.
    It joins coordinates to a larger entity
    and puts them in a neighborhood relation.

    A connectivity can define several neighborhood relations.
    For example, a uniform grid would have 0D vertices,
    1D grid edges, 2D grid faces, and 3D grid cells/voxels.
    The connectivity defines these neighborhood relations
    and allows iterating over them.

    This refers to the 'topological space'
    in <em>Vector-Bundle Classes Form Powerful Tool for Scientific Visualization</em>,
    Butler and Bryson, 1992.

    Connectivity and Coordinates jointly define the manifold
    in the above paper.

    @author Tino Weinkauf and Anke Friederici
*/
class IVW_MODULE_DISCRETEDATA_API Connectivity
{
// Construction / Deconstruction
public:
    Connectivity(GridPrimitive gridDimension)
        : GridDimension(gridDimension)
        , NumGridPrimitives(gridDimension + 1, -1) {} // Initialize sizes with -1. Overwrite when known.
    virtual ~Connectivity() = default;

// Methods
public:
    /** \brief Returns the maximal dimension of the grid */
    GridPrimitive getDimension() const { return GridDimension; }

    /** \brief Return the number of elements of the given type
    *   @param elementType Type to get number of
    *   @return Number of elements
    */
    virtual ind getNumElements(GridPrimitive elementType) const;

    /** \brief Get the map from one element to another
    *   E.g. cell to its vertices, vertex to its neighbors, vertex to connected faces
    *   @param index Index of element in dimension from
    *   @param from Dimension the index lives in
    *   @param to Dimension the result lives in
    *   @return All connected indices in dimension to
    */
    virtual std::vector<ind> getConnections(ind index, GridPrimitive from, GridPrimitive to) const = 0;

    /** \brief Range of all elements to iterate over
    *   @param dim Dimension to return the elements of
    */
    ElementRange all(GridPrimitive dim) const;

    /** \brief Get the measure (i.e., length, area, volume...) of an element
    *   @param dim Dimension of element (edge, face, volume...)
    *   @Param index Index of respective element type
    */
    virtual double getPrimitiveMeasure(GridPrimitive dim, ind index) const { return -1; }

    /** \brief Get the measure (i.e., length, area, volume...) of an element
    *   @param element Element to get measure of
    */
    virtual double getPrimitiveMeasure(ElementIterator& element) const;

// Attributes
protected:
    /** Highest dimension of GridPrimitives */
    GridPrimitive GridDimension;

    /** Saves the known number of primitves */
    mutable std::vector<ind> NumGridPrimitives;

public:
    /** Vertex positions */
    std::shared_ptr<const Channel> Vertices;
};

} // namespace

#include <discretedata/elementiterator.h>
