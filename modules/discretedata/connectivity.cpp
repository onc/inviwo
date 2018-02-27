/*********************************************************************
 *  Author  : Tino Weinkauf and Anke Friederici
 *  Init    : Thursday, November 30, 2017 - 12:24:27
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedata/discretedatamoduledefine.h>
#include <inviwo/core/common/inviwo.h>

#include "discretedata/connectivity.h"
#include "discretedata/elementiterator.h"

namespace inviwo
{

ind Connectivity::getNumElements(GridPrimitive elementType) const
{
    ivwAssert(NumGridPrimitives.size() == (ind)GridDimension + 1, "GridPrimitive count vector has the wrong size: " + std::to_string(NumGridPrimitives.size()) + " != " + std::to_string((ind)GridDimension + 1));
    ivwAssert(NumGridPrimitives[elementType] != -1, "No size stored.");
    return NumGridPrimitives[elementType];
}

ElementRange Connectivity::all(GridPrimitive dim) const
{
    return ElementRange(dim, this);
}

double inviwo::Connectivity::getPrimitiveMeasure(ElementIterator& element) const
{
    return getPrimitiveMeasure(element.getType(), element.getIndex());
}

} // namespace
