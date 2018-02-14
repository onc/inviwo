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

// Methods
public:
    virtual std::vector<ind> getConnections(ind index, GridPrimitive from, GridPrimitive to) const;

protected:
    std::vector<ind> NumCellsPerDimension;
};

} // namespace