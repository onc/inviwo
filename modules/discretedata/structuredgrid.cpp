/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Monday, January 29, 2018 - 14:13:45
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include "structuredgrid.h"
#include "analyticchannel.h"

namespace inviwo
{

StructuredGrid::StructuredGrid(GridPrimitive gridDimension, const std::vector<ind>& numCellsPerDim)
    : Connectivity(gridDimension)
    , NumCellsPerDimension(numCellsPerDim)
{
    ivwAssert(numCellsPerDim.size() == gridDimension, "Grid dimension should match cell dimension.");
    NumCellsPerDimension = std::vector<ind>(numCellsPerDim);

    ind numCells = 1;
    ind numVerts = 1;
    for (ind dim = GridPrimitive::Vertex; dim < gridDimension; ++dim)
    {
        numCells *= NumCellsPerDimension[dim];
        numVerts *= NumCellsPerDimension[dim] + 1;
    }

    NumGridPrimitives[gridDimension] = numCells;
    NumGridPrimitives[GridPrimitive::Vertex] = numVerts;
}

std::vector<ind> sameLevelConnection(ind idxLin, std::vector<ind> index, std::vector<ind> size)
{
    ivwAssert(index.size() == size.size(), "Dimensions of input not matching.");

    std::vector<ind> neighbors;
    ind dimensionProduct = 1;
    for (int dim = 0; dim < size.size(); ++dim)
    {
        if (index[dim] > 0)
            neighbors.push_back(idxLin - dimensionProduct);
        if (index[dim] < size[dim]-1)
            neighbors.push_back(idxLin + dimensionProduct);

        dimensionProduct *= size[dim];
    }

    return neighbors;
}


std::vector<ind> StructuredGrid::getConnections(ind idxLin, GridPrimitive from, GridPrimitive to) const
{
    ind idxCutoff = idxLin;

    // nD Index.
    std::vector<ind> index(NumCellsPerDimension.size(), -1);
    for (ind dim = 0; dim < NumCellsPerDimension.size(); ++dim)
    {
        ind dimSize = NumCellsPerDimension[dim];
        index[dim] = idxCutoff % dimSize;
        idxCutoff = (ind)(idxCutoff / dimSize);
    }

    if (from == to && from == GridDimension)
        return sameLevelConnection(idxLin, index, NumCellsPerDimension);

    if (from == to && from == GridPrimitive::Vertex)
    {
        std::vector<ind> vertDims;
        for (ind dim : NumCellsPerDimension)
            vertDims.push_back(dim + 1);
        return sameLevelConnection(idxLin, index, vertDims);
    }

    if (from == GridDimension && to == GridPrimitive::Vertex)
    {
        ind dimensionProduct = 1;
        std::vector<ind> vertDims;
        vertDims.push_back(idxLin);
        for (int dim = 0; dim < GridDimension; ++dim)
        {
            ind numVerts = vertDims.size();
            for (ind idxPrev = 0; idxPrev < numVerts; ++idxPrev)
                vertDims.push_back(vertDims[idxPrev] + dimensionProduct);
            dimensionProduct *= NumCellsPerDimension[dim];
        }

        return vertDims;
    }

    ivwAssert(false, "Not implemented yet.");
    return std::vector<ind>();
}

} // namespace

