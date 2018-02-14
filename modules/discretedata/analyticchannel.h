/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Thursday, November 23, 2017 - 17:23:45
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/util/assertion.h>

#include "datachannel.h"

namespace inviwo
{
/** \class DataAnalytic
    \brief Data channel by function evaluated at each (linear) index.

    Realization of DataChannel.

    Data is stored implicitly by a function f:index -> vec<T>,
    where the destination memory is pre-allocated.
    Indices are linear.

    @author Anke Friederici and Tino Weinkauf
*/
template<typename T>
class AnalyticChannel : public DataChannel<T>
{ 
// Types
public:
    typedef typename  std::function<void(T*, ind)> Function;

// Construction / Deconstruction
public:
    /** \brief Direct construction
    *
    *   @param dataFunction Data generator, mapping of linear index to T*
    *   @param numElements Total number of indexed positions
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    AnalyticChannel(Function dataFunction, ind numElements, ind numComponents, const std::string& name, GridPrimitive definedOn = GridPrimitive::Vertex)
        : DataChannel<T>(numComponents, name, definedOn)
        , NumElements(numElements)
        , DataFunction(dataFunction) {}

    virtual ~AnalyticChannel() = default;

// Methods
public:
    ind getNumElements() const override { return NumElements; }

    /** \brief Indexed point access, constant
    *   @param dest Position to write to, expect write of NumComponents many T
    *   @param index Linear point index
    */
    void fill(T* dest, ind index) const override;

// Attributes
public:
    ind NumElements;
    Function DataFunction;
};

/*--------------------------------------------------------------*
*  Implementations                                              *
*--------------------------------------------------------------*/

template<typename T>
void AnalyticChannel<T>::fill(T* const dest, const ind index) const
{
    ivwAssert(
        index >= 0 && index < NumElements,
        "Index out of bounds: " << index);

    DataFunction(dest, index);
}

/*--------------------------------------------------------------*
*  Exported Types                                               *
*--------------------------------------------------------------*/

typedef AnalyticChannel<float>      AnalyticFloat;
typedef AnalyticChannel<double>     AnalyticDouble;
typedef AnalyticChannel<char>       AnalyticChar;
typedef AnalyticChannel<short>      AnalyticShort;
typedef AnalyticChannel<int>        AnalyticInt;
typedef AnalyticChannel<long>       AnalyticLong;
typedef AnalyticChannel<long long>  AnalyticLongLong;

typedef AnalyticChannel<unsigned char>       AnalyticUChar;
typedef AnalyticChannel<unsigned short>      AnalyticUShort;
typedef AnalyticChannel<unsigned int>        AnalyticUInt;
typedef AnalyticChannel<unsigned long>       AnalyticULong;
typedef AnalyticChannel<unsigned long long>  AnalyticULongLong;

} // namespace
