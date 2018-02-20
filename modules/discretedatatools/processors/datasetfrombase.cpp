/*********************************************************************
 *  Author  : Anke Friederici
 *  Init    : Wednesday, January 24, 2018 - 14:15:43
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <discretedatatools/processors/datasetfrombase.h>
#include <inviwo/core/processors/processorinfo.h>
#include <discretedata/structuredgrid.h>

namespace inviwo
{
    const ProcessorInfo DataSetFromVolume::processorInfo_
    {
        "org.inviwo.kth.DataSetFromVolume",     // Class identifier
        "Data Set from Volume",             // Display name
        "Data Set",                         // Category
        CodeState::Experimental,            // Code state
        Tags::None                          // Tags
    };

    DataSetFromVolume::DataSetFromVolume()
        : Processor()
        , portInData("BaseData")
        , portInDataSet("PrioDataSet")
        , portOutData("DataSetOutput")
        , channelName("dataName", "Data Name", "default") 
    {
        addPort(portInData);
        addPort(portOutData);
        addPort(portInDataSet);
        portInDataSet.setOptional(true);
        addProperty(channelName);

        // Todo: change name on channelName change
    }



    void DataSetFromVolume::process()
    {
        DataSet* dataSet 
            = portInDataSet.isConnected() && portInDataSet.hasData()
            ? new DataSet(*portInDataSet.getData())
            : new DataSet();

        auto volume = portInData.getData();
        const VolumeRAM* dataRAM = volume->getRepresentation<VolumeRAM>();

        auto dims = dataRAM->getDimensions();
        ind numElements = dims.x * dims.y * dims.z;

        // Add structured grid
        if (!dataSet->Grid)
            dataSet->Grid = std::make_shared<StructuredGrid>(GridPrimitive::Volume, std::vector<ind>({ (ind)dims.x, (ind)dims.y, (ind)dims.z }));


        // Copy data.
        const void* dataConst = dataRAM->getData();
        char* data = new char[dataRAM->getNumberOfBytes()];
        memcpy(data, dataConst, dataRAM->getNumberOfBytes());

        DataFormatId type = dataRAM->getDataFormatId();
        Channel* channel;

        switch (type)
        {
        case DataFormatId::Float16:
            channel = new BufferChannel<f16     >((f16     *)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
        case DataFormatId::Float32:
            channel = new BufferChannel<glm::f32>((glm::f32*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Float64:
            channel = new BufferChannel<glm::f64>((glm::f64*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Int8:
            channel = new BufferChannel<glm::i8 >((glm::i8 *)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Int16:
            channel = new BufferChannel<glm::i16>((glm::i16*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Int32:
            channel = new BufferChannel<glm::i32>((glm::i32*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Int64:
            channel = new BufferChannel<glm::i64>((glm::i64*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::UInt8:
            channel = new BufferChannel<glm::u8 >((glm::u8 *)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::UInt16:
            channel = new BufferChannel<glm::u16>((glm::u16*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::UInt32:
            channel = new BufferChannel<glm::u32>((glm::u32*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::UInt64:
            channel = new BufferChannel<glm::u64>((glm::u64*)data, numElements, 1, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Float16:
            channel = new BufferChannel<f16     >((f16     *)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Float32:
            channel = new BufferChannel<glm::f32>((glm::f32*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Float64:
            channel = new BufferChannel<glm::f64>((glm::f64*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Int8:
            channel = new BufferChannel<glm::i8 >((glm::i8 *)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Int16:
            channel = new BufferChannel<glm::i16>((glm::i16*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Int32:
            channel = new BufferChannel<glm::i32>((glm::i32*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2Int64:
            channel = new BufferChannel<glm::i64>((glm::i64*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2UInt8:
            channel = new BufferChannel<glm::u8 >((glm::u8 *)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2UInt16:
            channel = new BufferChannel<glm::u16>((glm::u16*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2UInt32:
            channel = new BufferChannel<glm::u32>((glm::u32*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec2UInt64:
            channel = new BufferChannel<glm::u64>((glm::u64*)data, numElements, 2, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Float16:
            channel = new BufferChannel<f16     >((f16     *)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Float32:
            channel = new BufferChannel<glm::f32>((glm::f32*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Float64:
            channel = new BufferChannel<glm::f64>((glm::f64*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Int8:
            channel = new BufferChannel<glm::i8 >((glm::i8 *)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Int16:
            channel = new BufferChannel<glm::i16>((glm::i16*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Int32:
            channel = new BufferChannel<glm::i32>((glm::i32*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3Int64:
            channel = new BufferChannel<glm::i64>((glm::i64*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3UInt8:
            channel = new BufferChannel<glm::u8 >((glm::u8 *)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3UInt16:
            channel = new BufferChannel<glm::u16>((glm::u16*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3UInt32:
            channel = new BufferChannel<glm::u32>((glm::u32*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec3UInt64:
            channel = new BufferChannel<glm::u64>((glm::u64*)data, numElements, 3, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Float16:
            channel = new BufferChannel<f16     >((f16     *)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Float32:
            channel = new BufferChannel<glm::f32>((glm::f32*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Float64:
            channel = new BufferChannel<glm::f64>((glm::f64*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Int8:
            channel = new BufferChannel<glm::i8 >((glm::i8 *)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Int16:
            channel = new BufferChannel<glm::i16>((glm::i16*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Int32:
            channel = new BufferChannel<glm::i32>((glm::i32*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4Int64:
            channel = new BufferChannel<glm::i64>((glm::i64*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4UInt8:
            channel = new BufferChannel<glm::u8 >((glm::u8 *)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4UInt16:
            channel = new BufferChannel<glm::u16>((glm::u16*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4UInt32:
            channel = new BufferChannel<glm::u32>((glm::u32*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        case DataFormatId::Vec4UInt64:
            channel = new BufferChannel<glm::u64>((glm::u64*)data, numElements, 4, channelName.get(), GridPrimitive::Vertex);
            break;
        default:
            ivwAssert(false, "No valid type set");
        }

        dataSet->Channels.addChannel(channel);
        portOutData.setData(dataSet);
    }

    const ProcessorInfo DataSetFromVolume::getProcessorInfo() const
    {
        return processorInfo_;
    }

} // namespace

