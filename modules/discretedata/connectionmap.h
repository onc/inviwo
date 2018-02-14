/*********************************************************************
*  Author  : Anke Friederici & Tino Weinkauf
*  Init    : Thursday, November 30, 2017 - 11:24:31
*
*  Project : KTH Inviwo Modules
*
*  License : Follows the Inviwo BSD license model
*********************************************************************
*/

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/metadata/metadataowner.h>

#include "discretedata/datachannel.h"

namespace inviwo
{

/** \class ConnectionMap
    \brief Maps GridPrimitives of one dimension to those of another dimension.

    A full connectivity is defined by mapping each dimension to each other
    (e.g. triangles to vertices, triangles to edges, edges to vertices, and all inverse).
    All maps can be generated from a map of highest dimension to lowest
    (e.g. triangles to vertices).

    @author Anke Friederici and Tino Weinkauf
*/
class IVW_MODULE_DISCRETEDATA_API ConnectionMap
{
    friend class ExplicitConnectivity;
public:
    ConnectionMap(GridPrimitive from, GridPrimitive to)
        : FromDimension(from)
        , ToDimension(to) {}

    /** \brief Create from indices and the prefix sums
    /*  @param map Indices from FromDimension to ToDimension
    /*  @param prefixSum Starting indices per element. Last element is the additional number of total elements in map.
    /*  @param numMappedTo The number of elements the map maps to. Computed if not given
    */
    void setMap(std::shared_ptr<DataChannel<ind>> map, std::shared_ptr<DataChannel<ind>> prefixSum, ind numMappedTo = -1);

    /** \brief Create map from a list of connection indices per element
    /*  @param connectivity Each outer vector is one FromDimension mapping to any number of ToDimension indices
    /*  @param numMappedTo The number of elements the map maps to. Computed if not given
    */
    void setMap(const std::vector<std::vector<ind>>& connectivity, ind numMappedTo = -1);

    // TODO: access

    /** Number of elements mapped from */
    ind getNumElementsFrom() { return NumElementsFrom; }

    /** Number of elements mapped to */
    ind getNumElementsTo()   { return NumElementsTo; }

protected:
    /** Map from FromDimension GridPrimitives to ToDimension GridPrimitives */
    std::shared_ptr<DataChannel<ind>> Map;

    /** Channel containing the spacing between two FromDimension elements
    *   Add one element (numElements) to make iteration easier.
    */
    std::shared_ptr<DataChannel<ind>> PrefixSums;

    /** Connectivity this map belongs to for iteration */
    std::shared_ptr<ExplicitConnectivity> Grid;

    /** Number of elements that are mapped from / to */
    ind NumElementsFrom, NumElementsTo;

public:
    /** Each channel element is a GridPrimitive in this dimension */
    const GridPrimitive FromDimension;

    /** Each channel value is a GridPrimitive in this dimension */
    const GridPrimitive ToDimension;
};

} // namespace
