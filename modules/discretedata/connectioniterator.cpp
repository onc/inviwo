/*********************************************************************
*  Author  : Anke Friederici and Tino Weinkauf
*  Init    : Friday, December 15, 2017 - 16:42:19
*
*  Project : KTH Inviwo Modules
*
*  License : Follows the Inviwo BSD license model
*********************************************************************
*/

#include "discretedata/connectioniterator.h"

namespace inviwo
{

ConnectionRange::ConnectionRange(ind fromIndex, GridPrimitive fromDim, GridPrimitive toDim, const Connectivity* parent)
    : ToDimension(toDim)
    , Parent(parent)
{
    Connections = std::make_shared<const std::vector<ind>>(Parent->getConnections(fromIndex, fromDim, toDim));
}

/** Increment randomly */
ConnectionIterator operator+(ind offset, ConnectionIterator& iter)
{
    return ConnectionIterator(iter.Parent, iter.ToDimension, iter.Connection, iter.ToIndex + offset);
}

/** Decrement randomly */
ConnectionIterator operator-(ind offset, ConnectionIterator& iter)
{
    return ConnectionIterator(iter.Parent, iter.ToDimension, iter.Connection, iter.ToIndex - offset);
}

ConnectionIterator inviwo::ConnectionIterator::operator*() const
{
    ivwAssert(Parent, "No channel to iterate is set.");
    
    return *this;
}

ConnectionRange ConnectionIterator::connection(GridPrimitive toType) const
{
    return ConnectionRange(this->getIndex(), ToDimension, toType, Parent);
}

} // namespace