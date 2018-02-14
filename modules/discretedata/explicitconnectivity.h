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

#include "discretedata/connectionmap.h"
#include "discretedata/datachannel.h"
#include "discretedata/util.h"

namespace inviwo
{

/** \class ExplicitConnectivity
    \brief Connectivity that stores connections in channels.

    @author Anke Friederici
*/
class IVW_MODULE_DISCRETEDATA_API ExplicitConnectivity : public Connectivity
{ 
// Construction / Deconstruction
public:
    ExplicitConnectivity(GridPrimitive gridDimension) : Connectivity(gridDimension) {}
    virtual ~ExplicitConnectivity() = default;

// Methods
public:
    /** \brief Return map between the selected dimensions if existing
    *   @param from Dimension of GridPrimitives indexing
    *   @param to Dimension of GridPrimitives indexed
    *   @return Map from->to if saved, nullptr elsewise
    */
    std::shared_ptr<const ConnectionMap> getMap(GridPrimitive from, GridPrimitive to) const;

    /** \brief Add a map, check and set number of elements
    *   If the map is already given, ignore this operation and return old value.
    *   @param map Map to be added
    *   @return Shared pointer as saved
    */
    std::shared_ptr<const ConnectionMap> addMap(std::shared_ptr<const ConnectionMap> map) const;

    /** \brief Return map between the selected dimensions, create if missing
    *   @param from Dimension of GridPrimitives indexing
    *   @param to Dimension of GridPrimitives indexed
    *   @return Map from->to
    */
    std::shared_ptr<const ConnectionMap> getOrCreateMap(GridPrimitive from, GridPrimitive to) const;

    virtual std::vector<ind> getConnections(ind index, GridPrimitive from, GridPrimitive to) const override;

protected:
    /** \brief Create a map between the selected dimensions
    /*  Implementation specific to respective grid (or rather, GridPrimitive) type.
    *   @param from Dimension of GridPrimitives indexing
    *   @param to Dimension of GridPrimitives indexed
    *   @return Map from->to, newly created
    */
    virtual std::shared_ptr<const ConnectionMap> createMap(GridPrimitive from, GridPrimitive to) const = 0;

// Attributes
protected:
    /** Maps between GridPrimitive dimensions */
    mutable std::unordered_map
        < std::pair<GridPrimitive, GridPrimitive>   // Hash by in and out GridPrimitive type
        , std::shared_ptr<const ConnectionMap>    // Save shared ConnectionMap between these dimensions
        , PairHash<GridPrimitive, GridPrimitive>>   // Hashing for std::pair is not in the SDL, see util.h
            Connections;
};

} // namespace
