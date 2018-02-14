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


namespace inviwo
{

typedef signed long long ind;

/** Mapping structure name to respective dimension.
*   Assign channels to any dimensions this way.
*   If these do not suffice, cast the respective short.
*/
enum GridPrimitive : char
{
    Vertex = 0,
    Edge = 1,
    Face = 2,
    Volume = 3,
    HyperVolume = 4
};

template<typename T>
class ChannelIterator;

/** \class Channel
    \brief An untyped scalar or vector component of a data set.

    General version of a DataChannel for use in general containers
    (see DataSet).

    @author Anke Friederici and Tino Weinkauf
*/
class IVW_MODULE_DISCRETEDATA_API Channel : public MetaDataOwner
{
// Construction / Deconstruction
public:
    /** \brief Direct construction
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    Channel(ind numComponents, const std::string& name, DataFormatId dataFormat, GridPrimitive definedOn = GridPrimitive::Vertex);

    virtual ~Channel() = default;

// Methods
public:
    /** Returns the "Name" meta data */
    const std::string getName() const;

    /** Sets the "Name" meta data */
    void setName(const std::string&);

    /** Returns the "GridPrimitiveType" meta data */
    GridPrimitive getGridPrimitiveType() const;

    /** Returns the "DataFormatId" meta data */
    DataFormatId getDataFormatId() const;

    /** Sets the "DataFromatId" meta data
    */
    void setDataFormatId(DataFormatId);

private:
    /** Sets the "GridPrimitiveType" meta data
    *   Should be constant, only DataSet is allowed to write.
    */
    void setGridPrimitiveType(GridPrimitive);


// Attributes
public:
    virtual ind getNumElements() const = 0;
    ind getNumComponents() const { return NumComponents; }

protected:
    ind NumComponents;
};

/** \class DataChannel
    \brief A single scalar or vector component of a data set.

    The type is arbitrary but is expected to support
    the basic arithmetic operations.
    The number of elements per data point is defined at runtime
    to allow dll export.
    Handling of data vectors is via data pointers.

    Several realizations extend this pure virtual class
    that differ in data storage/generation.
    Direct indexing is virtual, avoid where possible.

    @author Anke Friederici and Tino Weinkauf
*/
template<typename T>
class DataChannel : public Channel
{

    friend class DataSet;

// Construction / Deconstruction
public:
    /** \brief Direct construction
    *   @param numComponents Size of vector at each position
    *   @param name Name associated with the channel
    *   @param definedOn GridPrimitive the data is defined on, default: 0D vertices
    */
    DataChannel(ind numComponents, const std::string& name, GridPrimitive definedOn = GridPrimitive::Vertex);
    //    : Channel(numComponents, name, definedOn) {}

    virtual ~DataChannel() = default;

// Methods
public:
    /** \brief Indexed point access, copy data
    *   Thread safe.
    *   @param dest Position to write to, expect T[NumComponents]
    *   @param index Linear point index
    */
    virtual void fill(T* dest, ind index) const = 0;

    /** \brief Indexed point access, copy data
    *   Thread safe.
    *   @param dest Position to write to, expect T[NumComponents]
    *   @param index Linear point index
    */
    void operator()(T* dest, ind index) const { fill(dest, index); }

    ChannelIterator<T> begin();

    ChannelIterator<T> end();

    // TODO: const iterator
    // TODO: operators + - * / ==> much later
    // TODO: fast computations (getAsBuffer, applyFunction etc)

    T* max();
    T* max() const;


};

} // namespace

// Circumvent circular reference.
#include "channeliterator.h"

#include "datachannel.inl"


