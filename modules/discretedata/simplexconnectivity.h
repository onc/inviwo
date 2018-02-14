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

#include "discretedata/explicitconnectivity.h"

namespace inviwo
{

/** \class RegularConnectivity
    \brief A regular rectlinear grid in nD

    @author Tino Weinkauf and Anke Friederici
*/
class IVW_MODULE_DISCRETEDATA_API SimplexConnectivity : public ExplicitConnectivity
{ 
// Construction / Deconstruction
public:
    SimplexConnectivity(GridPrimitive gridDimension)
        : ExplicitConnectivity(gridDimension) {}
    virtual ~SimplexConnectivity() = default;

// Methods
public:
    /** \brief Create a map between the selected dimensions
    /*  Should work for each dimension.
    *   @param from Dimension of GridPrimitives indexing
    *   @param to Dimension of GridPrimitives indexed
    *   @return Map from->to, newly created
    */
    virtual std::shared_ptr<const ConnectionMap> createMap(GridPrimitive from, GridPrimitive to);
};

} // namespace
