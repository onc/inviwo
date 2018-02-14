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

#include "discretedata/dataset.h"
#include "discretedata/bufferchannel.h"
#include "discretedata/analyticchannel.h"
#include "discretedata/connectivity.h"
#include "discretedata/elementiterator.h"
#include "discretedata/connectioniterator.h"
#include "discretedata/structuredgrid.h"

namespace inviwo
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

} // namespace
