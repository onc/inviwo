/*********************************************************************
 *  Author  : Tino Weinkauf
 *  Init    : Monday, February 26, 2018 - 15:00:01
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <modules/discretedatatools/processors/volumefromdataset.h>
#include <modules/discretedata/structuredgrid.h>
#include <inviwo/core/datastructures/volume/volume.h>
#include <inviwo/core/datastructures/volume/volumeramprecision.h>

namespace inviwo
{

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo VolumeFromDataSet::processorInfo_
{
    "org.inviwo.VolumeFromDataSet",      // Class identifier
    "Volume From Data Set",                // Display name
    "Undefined",              // Category
    CodeState::Experimental,  // Code state
    Tags::None,               // Tags
};

const ProcessorInfo VolumeFromDataSet::getProcessorInfo() const
{
    return processorInfo_;
}


VolumeFromDataSet::VolumeFromDataSet()
    :portInDataSet("InDataSet")
    ,portOutVolume("OutVolume")
{
    addPort(portInDataSet);
    addPort(portOutVolume);
    //addProperty();
}


void VolumeFromDataSet::process()
{
    //Get data
    auto pInDataSet = portInDataSet.getData();
    if (!pInDataSet) return;

    auto pStructuredGrid = pInDataSet->getGrid<StructuredGrid>();
    if (!pStructuredGrid || pStructuredGrid->getDimension() != 3) return;

    //TODO: Get first channel for now.
    auto car = pInDataSet->Channels.ChannelSet.cbegin();
    SharedConstChannel Data = car->second;
    if (!Data) return;

    std::shared_ptr<const BufferChannel<double>> Buffer = std::dynamic_pointer_cast<const BufferChannel<double>, const Channel>(Data);
    if (!Buffer) return;


    ////Setup Inviwo's data structures

    ////Set the bounding box
    //// - The basis represents the size of the bbox, i.e., the lengths of its sides
    //// - Essentially, the scaling factors you need to make a [0,1]^3 box the correct size
    //glm::mat3 basis(1.0f);
    ////basis[0][0] = xmax - xmin;
    ////basis[1][1] = ymax - ymin;
    ////basis[2][2] = zmax - zmin;
    //basis[0][0] = 1.0;
    //basis[1][1] = 1.0;
    //basis[2][2] = 1.0;
    //// - The offset is the lower left corner.
    //glm::vec3 offset(0.0, 0.0, 0.0);

    ////Create volume and fill in data
    //auto volume = std::make_shared<Volume>();
    //// - bbox
    //volume->setBasis(basis);
    //volume->setOffset(offset);
    //// - dimensions
    //size3_t dimensions = {
    //                        pStructuredGrid->getNumCellsInDimension(0) + 1,
    //                        pStructuredGrid->getNumCellsInDimension(1) + 1,
    //                        pStructuredGrid->getNumCellsInDimension(2) + 1
    //                     };
    //volume->setDimensions(dimensions);
    //// - format
    //auto format = DataFormatBase::get(NumericType::Float, Buffer->getNumComponents(), 64);
    //volume->setDataFormat(format);
    //// - representation. A RAM representation since the data is already in memory.
    //auto volRAM = createVolumeRAM(dimensions, format, Buffer->get(0));
    //volume->addRepresentation(volRAM);
    //// - min and max
    //volume->dataMap_.initWithFormat(format);
    ////SetMinMaxForInviwoDataMap(pData, NumToRead, volume);

}

} // namespace

