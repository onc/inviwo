/*********************************************************************
*  Author  : Anke Friederici & Tino Weinkauf
*  Init    : Thursday, November 30, 2017 - 11:24:31
*
*  Project : KTH Inviwo Modules
*
*  License : Follows the Inviwo BSD license model
*********************************************************************
*/

#include "discretedata/connectionmap.h"

namespace inviwo
{

void ConnectionMap::setMap
        ( const std::shared_ptr<DataChannel<ind>> map
        , const std::shared_ptr<DataChannel<ind>> prefixSum
        , const ind numMappedTo)
{
    // Check that the maps fit to each other.
    ivwAssert
        ( map->getNumComponents() == 1 && prefixSum->getNumComponents() == 1
        , "Both channels should be scalar.");
    ind lastIdx = -1;
    prefixSum->fill(&lastIdx, prefixSum->getNumElements() - 1);
    ivwAssert
        ( map->getNumElements() == lastIdx
        , "Sizes of map and prefix sums don't agree.");

    // Set values.
    Map = map;
    PrefixSums = prefixSum;

    // Set sizes.
    NumElementsFrom = PrefixSums->getNumElements() - 1;
    if (numMappedTo == -1)
        NumElementsTo = numMappedTo;
 //   else
 //       NumElementsTo = map-> TODO: Write a method to  compute minima/maxima (and store them as meta data?)
}


void ConnectionMap::setMap
        ( const std::vector<std::vector<ind>>& connectivity
        , ind numMappedTo)
{
    // Store information in vector first
    std::vector<ind> map;
    std::vector<ind> sums;
    sums.push_back(0);

    for (const std::vector<ind>& connection : connectivity)
    {
        // Append all indices to large map.
        map.insert(map.end(), connection.begin(), connection.end());

        // Add size to prefix sums.
        sums.push_back(sums.back() + connection.size());
    }

    // Now, the numbers should agree.
    ivwAssert(map.size() == sums.back(), "Sizes don't agree.");

    // Converte to BufferChannel<ind>.
    std::string mapName = "Connection Map " + FromDimension + '-' + ToDimension;
    std::string sumName = "Prefix Sums "    + FromDimension + '-' + ToDimension;
    Map         = std::make_shared<BufferChannel<ind>>(map,  1, mapName, FromDimension);
    PrefixSums  = std::make_shared<BufferChannel<ind>>(sums, 1, sumName, FromDimension);

    // Set sizes.
    NumElementsFrom = PrefixSums->getNumElements() - 1;
    if (numMappedTo == -1)
        NumElementsTo = numMappedTo;
//    else
//        NumElementsTo = map->TODO: Write a method to  compute minima / maxima(and store them as meta data ? )
}

} // namespace