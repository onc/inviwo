/*********************************************************************
 *  Author  : Tino Weinkauf and Anke Friederici
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

TEST(DataSet, ChannelInsertRemoveEdit)
{

    // ************************************************* \\
    // Testing Handling of Data Sets                     \\
    // ************************************************* \\
    // - Create several channels
    // - Add and remove them
    // - Rename them
    DataSet set;

    auto monomeVert   = std::make_shared<AnalyticChannel<float>>([](float* a, ind idx) { a[0] = 0; a[1] = idx; a[2] = idx * idx; }, 100, 3, "Monome", GridPrimitive::Vertex);
    auto monomeFace   = std::make_shared<AnalyticChannel<float>>([](float* a, ind idx) { a[0] = 0; a[1] = idx; a[2] = idx * idx; }, 100, 3, "Monome", GridPrimitive::Face);
    auto identityVert = std::make_shared<AnalyticChannel<float>>([](float* a, ind idx) { a[0] = idx; a[1] = idx; a[2] = idx; }, 100, 3, "Identity", GridPrimitive::Vertex);

    set.Channels.addChannel(monomeVert);
    set.Channels.addChannel(monomeFace);
    set.Channels.addChannel(identityVert);

    //auto mV_comp = set.getChannel("Monome", GridPrimitive::Vertex);
    //EXPECT_EQ(mV_comp.get(), mV.get());
    // TODO: 
    // - Convert to buffer
    // - Assign to other GridPrimitives
    // - Check size with connectivity

    
}

} // namespace
