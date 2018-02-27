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
#include "elementiterator.h"
#include "util.h"

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

namespace
{
std::vector<ind> sameLevelConnection(const ind idxLin, const std::vector<ind>& index, const std::vector<ind>& size)
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
}

std::vector<ind> StructuredGrid::getConnections(ind idxLin, GridPrimitive from, GridPrimitive to) const
{
    if (from == to && from == GridDimension)
    {
        // Linear Index to nD Cell Index.
        ind idxCutoff = idxLin;
        std::vector<ind> index(NumCellsPerDimension.size(), -1);
        for (ind dim = 0; dim < (ind)NumCellsPerDimension.size(); ++dim)
        {
            ind dimSize = NumCellsPerDimension[dim];
            index[dim] = idxCutoff % dimSize;
            idxCutoff = (ind)(idxCutoff / dimSize);
        }
        return sameLevelConnection(idxLin, index, NumCellsPerDimension);
    }

    if (from == to && from == GridPrimitive::Vertex)
    {
        std::vector<ind> vertDims;
        for (ind dim : NumCellsPerDimension)
        {
            vertDims.push_back(dim + 1);
        }

        // Linear Index to nD Vertex Index.
        ind idxCutoff = idxLin;
        std::vector<ind> index(vertDims.size(), -1);
        for (ind dim = 0; dim < (ind)vertDims.size(); ++dim)
        {
            ind dimSize = vertDims[dim];
            index[dim] = idxCutoff % dimSize;
            idxCutoff = (ind)(idxCutoff / dimSize);
        }

        return sameLevelConnection(idxLin, index, vertDims);
    }

    if (from == GridDimension && to == GridPrimitive::Vertex)
    {
        // Have indices in "ascending order", i.e., indices always grow.
        ind dimensionProduct = 1;
        std::vector<ind> vertDims;
        vertDims.push_back(idxLin);
        for (int dim = 0; dim < GridDimension; ++dim)
        {
            ind numVerts = vertDims.size();
            for (ind idxPrev = 0; idxPrev < numVerts; ++idxPrev)
                vertDims.push_back(vertDims[idxPrev] + dimensionProduct);
            dimensionProduct *= NumCellsPerDimension[dim] + 1;
        }

        return vertDims;
    }

    if (from == GridPrimitive::Vertex && to == GridDimension)
    {
        //Compute dimensions for vertices
        std::vector<ind> vertDims;
        for (ind dim : NumCellsPerDimension)
        {
            vertDims.push_back(dim + 1);
        }

        const ind NumDimensions = vertDims.size();

        // Linear Index to nD Vertex Index.
        ind idxCutoff = idxLin;
        std::vector<ind> VertexIndex(vertDims.size(), -1);
        for(ind dim(0);dim<NumDimensions;dim++)
        {
            ind dimSize = vertDims[dim];
            VertexIndex[dim] = idxCutoff % dimSize;
            idxCutoff = (ind)(idxCutoff / dimSize);
        }

        //Prepare neighbors
        std::vector<ind> CellNeighbors;
        const ind MaxNeighbors = 1i64<<NumDimensions;
        CellNeighbors.reserve(MaxNeighbors);

        //Compute neighbors
        std::vector<ind> CurrentNeighbor;
        for(ind i(0);i<MaxNeighbors;i++)
        {
            //Base index is the vertex index. The same cell index is the upper-right one of the neighbors.
            CurrentNeighbor = VertexIndex;

            //Generate new neighbor index
            for(ind d(0);d<NumDimensions;d++)
            {
                if (i & (1i64<<d)) CurrentNeighbor[d]--;
            }

            //Is it in the allowed range? And compute linear index while checking.
            bool bOk(true);
            ind CurrentNeighborLinearIndex(0);
            ind DimensionProduct(1);
            for(ind d(0);bOk&&d<NumDimensions;d++)
            {
                if (CurrentNeighbor[d] < 0 || CurrentNeighbor[d] >= NumCellsPerDimension[d])
                {
                    bOk = false;
                }

                CurrentNeighborLinearIndex += CurrentNeighbor[d] * DimensionProduct;
                DimensionProduct *= NumCellsPerDimension[d];
            }

            //If so, let's add it.
            if (bOk) CellNeighbors.push_back(CurrentNeighborLinearIndex);
        }

        return CellNeighbors;
    }

    ivwAssert(false, "Not implemented yet.");
    return std::vector<ind>();
}

ind StructuredGrid::getNumCellsInDimension(ind dim) const
{
    IVW_ASSERT(NumCellsPerDimension[dim] >= 0, "Number of elements not known yet.");
    return NumCellsPerDimension[dim];
}

double StructuredGrid::getPrimitiveMeasure(GridPrimitive dim, ind index) const
{
    if (!this->Vertices)
        return -1;

    // Only implemented 3D bodies so far.
    if (dim != GridPrimitive::Volume)
        return -1;

    double measure = -1;

    // TODO: Make this kind of code obsolete or at least compact.
    switch (Vertices->getDataFormatId())
    {
    case DataFormatId::Float16:
        measure = computeHexVolume<float>(index);
        break;
    case DataFormatId::Float32:
        measure = computeHexVolume<glm::f32>(index);
        break;
    case DataFormatId::Float64:
        measure = computeHexVolume<glm::f64>(index);
        break;
    case DataFormatId::Int8:
        measure = computeHexVolume<glm::i8 >(index);
        break;
    case DataFormatId::Int16:
        measure = computeHexVolume<glm::i16>(index);
        break;
    case DataFormatId::Int32:
        measure = computeHexVolume<glm::i32>(index);
        break;
    case DataFormatId::Int64:
        measure = computeHexVolume<glm::i64>(index);
        break;
    case DataFormatId::UInt8:
        measure = computeHexVolume<glm::u8 >(index);
        break;
    case DataFormatId::UInt16:
        measure = computeHexVolume<glm::u16>(index);
        break;
    case DataFormatId::UInt32:
        measure = computeHexVolume<glm::u32>(index);
        break;
    case DataFormatId::UInt64:
        measure = computeHexVolume<glm::u64>(index);
        break;

    default:
        LogWarn("Data type not supported. Edit " << __FILE__);
        break;
    }

    return measure;
}
} // namespace

