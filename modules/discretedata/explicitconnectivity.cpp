/*********************************************************************
 *  Author  : Anke Friederici
 *  Init    : Monday, January 29, 2018 - 16:52:46
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>

#include "discretedata/explicitconnectivity.h"

namespace inviwo
{

std::shared_ptr<const ConnectionMap> ExplicitConnectivity::getMap(GridPrimitive from, GridPrimitive to) const
{
    // Find map with these dimensions, if any.
    auto it = Connections.find(std::make_pair(from, to));

    // Return value if found.
    if (it != Connections.end())
        return it->second;

    return nullptr;
}

std::shared_ptr<const ConnectionMap> ExplicitConnectivity::getOrCreateMap(GridPrimitive from, GridPrimitive to) const
{
    auto map = getMap(from, to);

    // If it does not exist yet, create it.
    // Type-specific, virtual call.
    if (!map)
    {
        auto newMap = createMap(from, to);
        map = addMap(newMap);
    }
    
    return map;
}

std::shared_ptr<const ConnectionMap> ExplicitConnectivity::addMap(std::shared_ptr<const ConnectionMap> newMap) const
{
    // Check whether inside already.
    std::shared_ptr<const ConnectionMap> map = getMap(newMap->FromDimension, newMap->ToDimension);
    if (map)
    {
        ivwAssert
            ( NumGridPrimitives[newMap->FromDimension] > 0 && NumGridPrimitives[newMap->ToDimension] > 0
            , "Map is already saved but sizes were not stored.");

        // Return if inside. Do not set new map.        
        return map; 
    }

    // Create map.
    auto result = Connections.emplace
        ( std::make_pair(newMap->FromDimension, newMap->ToDimension)
        , map);

    ivwAssert(result.second, "Map should not be inside, check earlier is wrong or outdated.");

    // Save number of elements.
    ind numFrom = newMap->PrefixSums->getNumElements() - 1;
//    ind numTo   = TODO

    // Should be equivalent to variable map.
    return (result.first)->second;
}

std::vector<ind> ExplicitConnectivity::getConnections(ind index, GridPrimitive from, GridPrimitive to) const
{
    auto map = getOrCreateMap(from, to);

    ind begin, end;
    map->PrefixSums->fill(&begin, index);
    map->PrefixSums->fill(&end, index + 1);
    std::vector<ind> neighbors(end - begin, -1);

    for (ind neigh = begin; neigh < end; neigh++)
        map->Map->fill(&neighbors[neigh - begin], neigh);

    return neighbors;
}

} // namespace
