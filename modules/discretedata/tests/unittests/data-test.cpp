/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
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

#include "discretedata/dataset.h"
#include "discretedata/bufferchannel.h"
#include "discretedata/analyticchannel.h"

namespace inviwo
{
namespace kth
{
    typedef BufferChannel<float>      BufferFloat;
TEST(CreatingCopyingIndexing, DataChannels)
{
    // Testing tests.
    EXPECT_EQ(42, -~41);

    // ************************************************* \\
    // Testing Indexing in Analytic/Buffer               \\
    // ************************************************* \\
    // - Create channels with (1, 0.1*idx, 0.01*idx^2)
    // - Compare results in analytic and buffer channel
    // - Copy, assign BufferChannel and test again

    DataSet dataset;
    size_t numElements = 10;
    void (*base)(float*,size_t) =
        [](float* dest, size_t idx)
        {
            dest[0] = 1.0f;
            dest[1] = 0.1f * idx;
            dest[2] = dest[1] * dest[1];
        };

    // Setting up a buffer to test against an analytic channel.
    std::vector<float> data;
    for (int dIdx = 0; dIdx < numElements; ++dIdx)
    {
        data.push_back(1);
        data.push_back(0.1f * dIdx);
        data.push_back(0.01f * dIdx * dIdx);
    }
    BufferChannel<float>* testBuffer = new BufferFloat(data, 3, "MonomialBuffer", GridPrimitive::Vertex);
    IntMetaData* yearTest = testBuffer->createMetaData<IntMetaData>("YearCreated");
    yearTest->set(2017);

    // Set up the same channel as analytic channel.
    AnalyticFloat* testAnalytic = new AnalyticFloat(base, numElements, 3, "MonomialAnalytical", GridPrimitive::Vertex);

    // Copy buffer.
    BufferFloat* copyBuffer = new BufferFloat(*testBuffer);
    copyBuffer->setName("MonomialBufferCopy");
    BufferFloat* sharedBuffer(testBuffer);

    // Add to DataSet
    dataset.Channels.addChannel(testBuffer);
    dataset.Channels.addChannel(testAnalytic);
    dataset.Channels.addChannel(copyBuffer);

    //  Test access
    auto setBuffer = dataset.Channels.getChannel("MonomialBufferCopy");

    EXPECT_EQ(setBuffer->getMetaData<IntMetaData>("YearCreated")->get(), 2017);

    // Check equality of indexing and filling.

    // Setup for fill function.
    float* bufferData   = new float[3 * numElements];
    float* analyticData = new float[3 * numElements];

    // For one element: compare channels and fill data.
    {
    int dIdx = 3;

        testBuffer->fill(bufferData + 3*dIdx, dIdx);

        testAnalytic->fill(analyticData + 3*dIdx, dIdx);

        // Check equality in a dimension.
        {
        int dim = 1;

            EXPECT_EQ(testBuffer->get(dIdx)[dim], copyBuffer->get(dIdx)[dim]);
            EXPECT_EQ(testBuffer->get(dIdx)[dim], bufferData  [dIdx*3 + dim]);
            EXPECT_EQ(testBuffer->get(dIdx)[dim], analyticData[dIdx*3 + dim]);
        }
    }

    // The other data should be deleted when the dataset deconstructs.
}

} // namespace kth
} // namespace
