/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Thursday, November 23, 2017 - 17:23:30
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>

#include "datachannel.h"

namespace inviwo
{

/** \class DataBuffer
    \brief Data channel as array data

    Data block with a size of
    NumDataPoints * NumComponents.
    The buffer is not constant, copy to change.

    @author Anke Friederici and Tino Weinkauf
*/
template<typename T>
class BufferChannel : public DataChannel<T>
{

    friend class DataSet;

//Construction / Deconstruction
public:

    /** \brief Direct construction, empty data
    *   @param numElements Total number of indexed positions
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    BufferChannel(ind numElements, ind numComponents, const std::string& name, GridPrimitive definedOn = GridPrimitive::Vertex)
        : DataChannel<T>(numComponents, name, definedOn)
        , Buffer(numElements * numComponents) {}

    /** \brief Direct construction
    *   @param data Raw data, copy values
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    BufferChannel(std::vector<T>& data, ind numComponents, const std::string& name, GridPrimitive definedOn = GridPrimitive::Vertex)
        : DataChannel<T>(numComponents, name, definedOn)
        , Buffer(data)
        { ivwAssert(data.size() % numComponents == 0, "Data size not multiple of numComponents."); }

    /** \brief Direct construction
    *   @param data Raw data, move values
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    BufferChannel(std::vector<T>&& data, ind numComponents, const std::string& name, GridPrimitive definedOn = GridPrimitive::Vertex)
        : DataChannel<T>(numComponents, name, definedOn)
        , Buffer(std::move(data))
    {
        ivwAssert(data.size() % numComponents == 0, "Data size not multiple of numComponents.");
    }


    /** \brief Direct construction
    *   @param data Pointer to data, copy numElements * numComponents
    *   @param numElements Total number of indexed positions
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    BufferChannel(T* data, ind numElements, ind numComponents, const std::string& name, GridPrimitive definedOn = GridPrimitive::Vertex)
        : DataChannel<T>(numComponents, name, definedOn)
        , Buffer(data, data + numElements * numComponents) {}

protected:
    ///** \brief Make other channel type explicit and editable.
    //*   Protected to avoid unwanted copy of data from buffer to buffer.
    //*   @param channel 
    //*/
    //BufferChannel(const Channel& channel)
    //    : DataChannel<T>(numComponents, name, definedOn)
    //    , Buffer(data, data + numElements * numComponents) {}

// Methods
public:

    virtual ind getNumElements() const override;

    /** \brief Indexed point access, constant
    *   @param index Linear point index
    *   @return Pointer to data, size T[NumComponents]
    */
    const T* operator[] (ind index) const { return get(index); }

    /** \brief Indexed point access, mutable
    *   @param index Linear point index
    *   @return Pointer to data, size T[NumComponents]
    */
    T* operator[] (ind index) { return get(index); }

    /** \brief Indexed point access, mutable, same as []
    *   NOT THREAD SAFE, use fill instead.
    *   @param index Linear point index
    *   @return Pointer to data, NumComponents many T
    */
    T* get(ind index);

    /** \brief Indexed point access, constant, same as []
    *   @param index Linear point index
    *   @return Pointer to data, NumComponents many T
    */
    const T* get(ind index) const;

    /** \brief Indexed point access, constant
    *   @param dest Position to write to, expect write of NumComponents many T
    *   @param index Linear point index
    */
    void fill(T* dest, ind index) const override;

// Attributes
protected:
    /** \brief Vector containing the buffer data
    *   Resizeable only by DataSet. Handle with care:
    *   Resize invalidates pointers to memory, but iterators remain valid.
    */
    std::vector<T> Buffer;
};



/*--------------------------------------------------------------*
*  Implementations - Index Access                               *
*--------------------------------------------------------------*/

template<typename T>
ind BufferChannel<T>::getNumElements() const
{
    ivwAssert(
        Buffer.size() % NumComponents == 0,
        "Buffer size not multiple of component size");

    return Buffer.size() / NumComponents;
}


template<typename T>
T* BufferChannel<T>::get(const ind index)
{
    ivwAssert(
        index >= 0 && index < getNumElements(),
        "Index out of bounds: " << index);

    return Buffer.data() + index * NumComponents;
}


template<typename T>
const T* BufferChannel<T>::get(const ind index) const
{
    ivwAssert(
        index >= 0 && index < getNumElements(),
        "Index out of bounds: " << index);

        return Buffer.data() + index * NumComponents;
}


template<typename T>
void BufferChannel<T>::fill(T* const dest, const ind index) const
{
    ivwAssert(
        index >= 0 && index < getNumElements(),
        "Index out of bounds: " << index);

    memcpy(
        dest,
        Buffer.data() + (index * NumComponents),
        sizeof(T) * NumComponents);
}

/*--------------------------------------------------------------*
*  Exported Types                                               *
*--------------------------------------------------------------*/

//typedef BufferChannel<float>      BufferFloat;
//typedef BufferChannel<double>     BufferDouble;
//typedef BufferChannel<char>       BufferChar;
//typedef BufferChannel<short>      BufferShort;
//typedef BufferChannel<int>        BufferInt;
//typedef BufferChannel<long>       BufferLong;
//typedef BufferChannel<long long>  BufferLongLong;
//
//typedef BufferChannel<unsigned char>       BufferUChar;
//typedef BufferChannel<unsigned short>      BufferUShort;
//typedef BufferChannel<unsigned int>        BufferUInt;
//typedef BufferChannel<unsigned long>       BufferULong;
//typedef BufferChannel<unsigned long long>  BufferULongLong;

} // namespace
