/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Wednesday, February 21, 2018 - 15:07:31
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <discretedatatools/processors/computegridmeasure.h>

namespace inviwo
{

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo ComputeGridMeasure::processorInfo_
{
    "org.inviwo.ComputeGridMeasure",      // Class identifier
    "Compute Grid Measure",               // Display name
    "Data Set",               // Category
    CodeState::Experimental,  // Code state
    Tags::None,               // Tags
};

const ProcessorInfo ComputeGridMeasure::getProcessorInfo() const
{
    return processorInfo_;
}


ComputeGridMeasure::ComputeGridMeasure()
    : Processor()
    , dataInport("InputData")
    , dataOutport("ExtendedData")
    , dimensionToMeasure("dimensionToMeasure", "Grid Primitive to compute Measure on")
{
    addPort(dataInport);
    addPort(dataOutport);
    addProperty(dimensionToMeasure);

    dataInport.onConnect([this]() { this->updatePrimitiveOptions(); });
    dataInport.onChange([this]() { this->updatePrimitiveOptions(); });
}

void ComputeGridMeasure::updatePrimitiveOptions()
{
    std::shared_ptr<const Connectivity> grid;
    dimensionToMeasure.clearOptions();

    // Nothing connected, nothing to choose
    if (!dataInport.getData() || (grid = dataInport.getData()->Grid))
        return;

    for (int dim = 1; dim < grid->getDimension(); ++dim)
    {
        std::string dimString = "" + std::to_string(dim) + "D";
        std::string addString = "";
        switch (dim)
        {
        case 1:
            addString = " (Edges)";
            break;
        case 2:
            addString = " (Faces)";
            break;
        case 3:
            addString = " (Volumes)";
            break;
        default:
            break;
        }
        dimensionToMeasure.addOption(dimString, dimString + addString, dim);
        dimensionToMeasure.set(grid->getDimension());
    }
}

void ComputeGridMeasure::process()
{
    const auto& grid = dataInport.getData()->Grid;
    GridPrimitive dimensionToProcess = (GridPrimitive)dimensionToMeasure.get();

    if (dimensionToProcess < 1 || dimensionToProcess > grid->getDimension())
        return;

    // Setup buffer to store data in
    ind numElements = grid->getNumElements(dimensionToProcess);
    auto volumeBuffer = std::make_shared<BufferChannel<double>>
        ( numElements
        , 1
        , "Measure" + dimensionToMeasure.getDisplayName()
        , dimensionToProcess );
    
    // Compute measures per element
    for (auto element : grid->all(dimensionToProcess))
        *(volumeBuffer->get(element.getIndex())) = grid->getPrimitiveMeasure(element);

    auto outData = std::make_shared<DataSet>(*dataInport.getData());

    outData->Channels.addChannel(std::dynamic_pointer_cast<Channel, BufferChannel<double>>(volumeBuffer));
    dataOutport.setData(outData);
}

} // namespace

