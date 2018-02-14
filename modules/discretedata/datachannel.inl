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
#include <inviwo/core/metadata/metadata.h>

namespace inviwo
{

template<typename T>
DataChannel<T>::DataChannel(ind numComponents, const std::string& name, GridPrimitive definedOn)
    : Channel(numComponents, name, DataFormatId::NotSpecialized, definedOn)
{
    // Switch all types.
    if (std::is_same<T, f16>::value) setDataFormatId(DataFormatId::Float16);
    if (std::is_same<T, glm::f32>::value) setDataFormatId(DataFormatId::Float32);
    if (std::is_same<T, glm::f64>::value) setDataFormatId(DataFormatId::Float64);

    // Integers
    if (std::is_same<T, glm::i8>::value) setDataFormatId(DataFormatId::Int8);
    if (std::is_same<T, glm::i16>::value) setDataFormatId(DataFormatId::Int16);
    if (std::is_same<T, glm::i32>::value) setDataFormatId(DataFormatId::Int32);
    if (std::is_same<T, glm::i64>::value) setDataFormatId(DataFormatId::Int64);

    // Unsigned Integers
    if (std::is_same<T, glm::u8>::value) setDataFormatId(DataFormatId::UInt8);
    if (std::is_same<T, glm::u16>::value) setDataFormatId(DataFormatId::UInt16);
    if (std::is_same<T, glm::u32>::value) setDataFormatId(DataFormatId::UInt32);
    if (std::is_same<T, glm::u64>::value) setDataFormatId(DataFormatId::UInt64);
}

template<typename T>
ChannelIterator<T> DataChannel<T>::begin()
{
    return ChannelIterator<T>(this, 0);
}

template<typename T>
ChannelIterator<T> DataChannel<T>::end()
{
        return ChannelIterator<T>(this, getNumElements());
}

} // namespace
