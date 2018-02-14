/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedatatools/discretedatatoolsmoduledefine.h>
#include <discretedata/dataset.h>
#include <inviwo/core/ports/datainport.h>
#include <inviwo/core/ports/dataoutport.h>

namespace inviwo 
{
    using DataSetInport  = DataInport <DataSet>;
	using DataSetOutport = DataOutport<DataSet>;
}