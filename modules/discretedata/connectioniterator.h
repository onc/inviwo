/*********************************************************************
*  Author  : Anke Friederici and Tino Weinkauf
*  Init    : Friday, December 15, 2017 - 16:42:19
*
*  Project : KTH Inviwo Modules
*
*  License : Follows the Inviwo BSD license model
*********************************************************************
*/

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>

#include "connectionmap.h"
#include "connectivity.h"

namespace inviwo
{

class ConnectionRange;

/** \class ConnectionIterator
*   Iterates over one GridPrimitive type in a Connectivity.
*/
class IVW_MODULE_DISCRETEDATA_API ConnectionIterator
{
friend ConnectionIterator operator+(ind, ConnectionIterator&);
friend ConnectionIterator operator-(ind, ConnectionIterator&);

public:
    ConnectionIterator(const Connectivity* parent, GridPrimitive dimension, std::shared_ptr<const std::vector<ind>> neighborhood, ind index = 0)
        : Parent(parent)
        , ToIndex(index)
        , ToDimension(dimension)
        , Connection(neighborhood) {}

    ConnectionIterator()
        : Parent(nullptr)
        , ToIndex(-1)
        , ToDimension(GridPrimitive(-1))
        , Connection() {}

    ~ConnectionIterator() = default;

    /** Dereference to 'get data' */
    ConnectionIterator operator*() const;

    //*** Bidirectional Iteration ***\\

    /** Walk forward */
    ConnectionIterator& operator++() { ToIndex++; return *this; }

    /** Walk backward */
    ConnectionIterator& operator--() { ToIndex--; return *this; }

    /** Compare. Has false positives with iterators started from different elements but suffices for iteration */
    bool operator==(ConnectionIterator& other)
    {
        return other.Parent == Parent // Compare pointers.
            && other.ToDimension == ToDimension
            && other.ToIndex == ToIndex;
    }

    /** Compare */
    bool operator!=(ConnectionIterator& other) { return !(other == *this); }

    //*** Random Access Iteration ***\\

    /** Increment randomly */
    ConnectionIterator operator+(ind offset)
        { return ConnectionIterator(Parent, ToDimension, Connection, ToIndex + offset); }

    /** Increment randomly */
    ConnectionIterator& operator+=(ind offset) { ToIndex += offset; return *this; }

    /** Decrement randomly */
    ConnectionIterator operator-(ind offset)
        { return ConnectionIterator(Parent, ToDimension, Connection, ToIndex - offset); }

    /** Decrement randomly */
    ConnectionIterator& operator-=(ind offset) { ToIndex -= offset; return *this; }

    /** GridPrimitive type the iterator walks through */
    GridPrimitive getType() const { return ToDimension; }

    /** The current index. Equivalent to dereferencing. */
    ind getIndex() const { return Connection->at(ToIndex); }

    /** Iterate over connected GridPrimitives (neighbors etc) */
    ConnectionRange connection(GridPrimitive type) const;

    // Members
protected:
    /** Index to the current element */
    ind ToIndex;

    ///** Iterte through the connections of this element */
    //const ind FromIndex;

    /** Pointer to Connectivity iterated through - Does not delete */
    const Connectivity* Parent;

    /** List of neighborhood indices */
    std::shared_ptr<const std::vector<ind>> Connection;

    /** GridPrimitive type iterated over (0D vertices etc) */
    const GridPrimitive ToDimension;

    ///** GridPrimitive type of parent element */
    //const GridPrimitive FromDimension;
};

struct ConnectionRange
{
    ConnectionRange(ind fromIndex, GridPrimitive fromDim, GridPrimitive toDim, const Connectivity* parent);

    ConnectionIterator begin() { return ConnectionIterator(Parent, ToDimension, Connections, 0); }
    ConnectionIterator end()   { return ConnectionIterator(Parent, ToDimension, Connections, Connections->size()); }

    GridPrimitive ToDimension;
    std::shared_ptr<const std::vector<ind>> Connections;
    const Connectivity* Parent;
};

} // namespace



