/*********************************************************************
 *  Author  : Anke Friederici
 *  Init    : Tuesday, January 30, 2018 - 10:17:44
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

/** \class ElementIterator
*   Iterates over one GridPrimitive type in a Connectivity.
*/
class IVW_MODULE_DISCRETEDATA_API ElementIterator
{
friend ElementIterator operator+(ind, ElementIterator&);
friend ElementIterator operator-(ind, ElementIterator&);

public:
    ElementIterator(const Connectivity* parent, GridPrimitive dimension, ind index = 0)
        : Parent(parent)
        , Index(index)
        , Dimension(dimension) {}

    ElementIterator()
        : Parent(nullptr)
        , Index(-1)
        , Dimension(GridPrimitive(-1)) {}

    ~ElementIterator() = default;

    /** Dereference to 'get data' */
    ElementIterator operator*() const;

    //*** Bidirectional Iteration ***\\

    /** Walk forward */
    ElementIterator& operator++() { Index++; return *this; }

    /** Walk backward */
    ElementIterator& operator--() { Index--; return *this; }

    /** Compare */
    bool operator==(ElementIterator& other)
    {
        return other.Parent == Parent // Compare pointers.
            && other.Dimension == Dimension
            && other.Index == Index;
    }

    /** Compare */
    bool operator!=(ElementIterator& other) { return !(other == *this); }

    //*** Random Access Iteration ***\\

    /** Increment randomly */
    ElementIterator operator+(ind offset)
        { return ElementIterator(Parent, Dimension, Index + offset); }

    /** Increment randomly */
    ElementIterator& operator+=(ind offset) { Index += offset; return *this; }

    /** Decrement randomly */
    ElementIterator operator-(ind offset)
        { return ElementIterator(Parent, Dimension, Index - offset); }

    /** Decrement randomly */
    ElementIterator& operator-=(ind offset) { Index -= offset; return *this; }

    /** GridPrimitive type the iterator walks through */
    GridPrimitive getType() const { return Dimension; }

    /** The current index. Equivalent to dereferencing. */
    ind getIndex() const { return Index; }

    /** Iterate over connected GridPrimitives (neighbors etc) */
    ConnectionRange connection(GridPrimitive toType) const;

    // Members
protected:
    /** Index to the current element */
    ind Index;

    /** Pointer to Connectivity iterated through - Does not delete */
    const Connectivity* Parent;

    /** GridPrimitive type iterated over (0D vertices etc) */
    const GridPrimitive Dimension;
};

struct IVW_MODULE_DISCRETEDATA_API ElementRange
{
    ElementRange(GridPrimitive dim, const Connectivity* parent) : Dimension(dim), Parent(parent) {}

    ElementIterator begin() { return ElementIterator(Parent, Dimension, 0); }
    ElementIterator end() { return ElementIterator(Parent, Dimension, Parent->getNumElements(Dimension)); }

    GridPrimitive Dimension;
    const Connectivity* Parent;
};

} // namespace