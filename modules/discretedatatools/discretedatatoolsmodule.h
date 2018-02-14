/*********************************************************************
 *  Author  : Tino Weinkauf
 *  Init    : Sunday, October 01, 2017 - 05:17:04
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedatatools/discretedatatoolsmoduledefine.h>
#include <inviwo/core/common/inviwomodule.h>

namespace inviwo
{

class IVW_MODULE_DISCRETEDATATOOLS_API DiscreteDataToolsModule : public InviwoModule
{
public:
    DiscreteDataToolsModule(InviwoApplication* app);
    virtual ~DiscreteDataToolsModule() = default;
};

} // namespace
