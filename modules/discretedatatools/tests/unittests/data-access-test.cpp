/*********************************************************************
 *  Author  : Anke Friederici
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <warn/push>
#include <warn/ignore/all>
#include <gtest/gtest.h>
#include <warn/pop>
#include <iostream>

#include <discretedata/dataset.h>
#include <discretedata/bufferchannel.h>
#include <discretedata/analyticchannel.h>
#include <discretedata/connectivity.h>
#include <discretedata/elementiterator.h>
#include <discretedata/connectioniterator.h>
#include <discretedata/structuredgrid.h>

namespace inviwo
{
namespace kth
{

TEST(AccessingData, Connectivity)
{
    DataSet data; // Assume there is data.
    data.Grid = std::make_shared<StructuredGrid>(GridPrimitive::Volume, std::vector<ind>({4,5,6}));
    std::shared_ptr<Connectivity> grid = data.Grid;

    auto w = grid->test();
    auto x = grid->all(GridPrimitive::Volume);
    auto y = x.begin();
    auto z = *y;

    for (ElementIterator cell : grid->all(GridPrimitive::Volume))
    {
        auto c = cell.getIndex();
        auto a = cell.connection(GridPrimitive::Vertex);
        auto b = a.begin();
        // Now, we basically have a GridPrimitive/index object.
        for (ConnectionIterator vert : cell.connection(GridPrimitive::Vertex))
        {
            //// Iterate over all vertices of the respective cell.
            //// Basically a fromGridPrimitive/toGridPrimitive/fromIndex/toIndex object.
            //// Do something with them.
            //float* pos   = vert.getPosition<float>();
            //float* orPos = grid.getPosition<float>(vert);

            // Get data on the element directly from DataSet.
            // Takes GridPrimitive of vert for channel query.
            // TODO: Maybe channel query should be really fast then?
            //      The bottleneck is probably the Channel query and cast.
 //           double* velo = data.getValue<double>("Position", vert);
        }
    }
}

//TEST(AccessingData, DataChannelCurrent)
//{
//    DataSet data; // Assume there is data.
//
//    std::shared_ptr<Channel>              velocity
//        = data.getChannel("Velocity");   // Get as Channel.
//
//    ivwAssert(velocity.get(), "Velocity not present in data.");
//
//    // ~~~~~~~~~~~~~~~ DataChannel ~~~~~~~~~~~~~~~ \\
//
//    std::shared_ptr<DataChannel<float>>   velocityData
//        = data.getChannel<float>("Velocity");   // Get as DataChannel of float.
//
//    ivwAssert(velocityData.get(), "Velocity is not float as expected.");
//
//    // ~~~~~~~~~~~~~~~ BufferChannel ~~~~~~~~~~~~~~~ \\
//
//    std::shared_ptr<BufferChannel<float>> velocityBuffer
//        = data.getAsBuffer<float>("Velocity");  // Get or convert to BufferChannel.
//
//    // Assume elements are 3 large, have to specify at compile time.
//    ivwAssert(velocityBuffer->getNumComponents() == 3, "Expected 3 floats.");
//
//    // We could add a templated function that checks the size internally
//    // and returns a VecNN directly.
//    VecNN<float, 3>& someValue = velocityBuffer->get<3>(7);
//    const Vec3f& someValue = velocityBuffer->operator[](7);
//    const Vec3f& someValue = velocityBuffer[7];
//
//    // ...or cast ourselves without in-built check.
//    VecNN<float, 3>* moreValue = std::reinterpret_cast<Vec3f*>(velocityBuffer->get(7));
//
//    // BTW: DataChannel looks like this:
//    VecNN<float, 3>  mostValue;
//    velocityData->fill<3>(&mostValue, 7);
//
//    // ... or this:
//    VecNN<float, 3>  mostValue;
//    velocityData->fill(&mostValue, 7);
//}


//TEST(AccessingData, DataChannel_IfTypeWasEnum)
//{
//    DataSet data; // Assume there is data.
//
//    std::shared_ptr<Channel>              velocity
//        = data.getChannel("Velocity");   // Get as Channel.
//
//    // If no type is known but a type information exists, we have to write for all types explicitely.
//    switch(velocity.getType())
//    {
//        // Could also reinterpret_cast each time.
//        case Type::float:
//            auto velocityFloat = data.getChannel<float>("Velocity");
//            velocityFloat->doStuff<float,3,4>();
//            break;
//        case Type::int:
//            auto velocityFloat = data.getChannel<int>("Velocity");
//            velocityFloat->doIntStuff();
//            break;
//        default:
//    }
//
//    // Cannto write this outside, since type is not known.
//    // VecNN<float, 3> someValue = velocityBuffer[7];
//}

} // namespace kth
} // namespace
