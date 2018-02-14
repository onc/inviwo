/*********************************************************************
*  Author  : Anke Friederici & Tino Weinkauf
*  Init    : Thursday, November 23, 2017 - 17:21:20
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

#include "datachannel.h"

namespace inviwo
{

Channel::Channel(ind numComponents, const std::string& name, DataFormatId format, GridPrimitive prim)
    : NumComponents(numComponents)
{
    // Create and set name.
    StringMetaData* nameData = createMetaData<StringMetaData>("Name");
    *nameData = name;

    // Create and set format identifier.
    IntMetaData* formatData = createMetaData<IntMetaData>("DataFormatId");
    *formatData = (int)format;

    // Create and set GridPrimitive type.
    IntMetaData* dimData = createMetaData<IntMetaData>("GridPrimitiveType");
    *dimData = (int)prim;
}

const std::string Channel::getName() const
{
    return getMetaData<StringMetaData>("Name")->get();
}

void Channel::setName(const std::string& name)
{
    setMetaData<StringMetaData>("Name", name);
}

GridPrimitive Channel::getGridPrimitiveType() const
{
    return (GridPrimitive)getMetaData<IntMetaData>("GridPrimitiveType")->get();
}

DataFormatId Channel::getDataFormatId() const
{
    return (DataFormatId)getMetaData<IntMetaData>("DataFormatId")->get();
}

void Channel::setGridPrimitiveType(GridPrimitive prim)
{
    setMetaData<IntMetaData>("GridPrimitiveType", prim);
}

void Channel::setDataFormatId(DataFormatId format)
{
    setMetaData<IntMetaData>("DataFormatId", (int)format);
}

} // namespace
