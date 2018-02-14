/*********************************************************************
*  Author  : Anke Friederici and Tino Weinkauf
*  Init    : Thursday, December 14, 2017 - 13:12:35
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include "discretedata/simplexconnectivity.h"
#include "discretedata/explicitconnectivity.h"

namespace inviwo
{

std::shared_ptr<const ConnectionMap> SimplexConnectivity::createMap
    ( GridPrimitive from
    , GridPrimitive to)
{
    ivwAssert(this->getMap(GridDimension, GridPrimitive::Vertex), "Base map is not given.");

//    TODO
    return std::shared_ptr<const ConnectionMap>();
}

} // namespace
