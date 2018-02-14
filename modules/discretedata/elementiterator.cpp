/*********************************************************************
*  Author  : Anke Friederici
*  Init    : Tuesday, January 30, 2018 - 10:17:44
*
*  Project : KTH Inviwo Modules
*
*  License : Follows the Inviwo BSD license model
*********************************************************************
*/

#include <discretedata/elementiterator.h>
#include <discretedata/connectioniterator.h>

namespace inviwo
{

/** Increment randomly */
ElementIterator operator+(ind offset, ElementIterator& iter)
{
    return ElementIterator(iter.Parent, iter.Dimension, iter.Index + offset);
}

/** Decrement randomly */
ElementIterator operator-(ind offset, ElementIterator& iter)
{
    return ElementIterator(iter.Parent, iter.Dimension, iter.Index - offset);
}

ElementIterator ElementIterator::operator*() const
{
    ivwAssert(Parent, "No channel to iterate is set.");

    return *this;
}

ConnectionRange ElementIterator::connection(GridPrimitive toType) const
{
    return ConnectionRange(this->getIndex(), Dimension, toType, Parent);
}

} // namespace