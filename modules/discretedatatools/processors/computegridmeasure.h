/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Wednesday, February 21, 2018 - 15:07:31
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <modules/discretedatatools/discretedatatoolsmoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/properties/optionproperty.h>
#include <discretedatatools/ports/datasetport.h>

namespace inviwo
{

/** \class ComputeGridMeasure
    \brief Compute the edge length, face area, volume etc. of a dataset grid
    
    Choose a grid element to compute the size of.
    The data will be appended as ChannelBuffer in the dataset.

    @author Anke Friederici & Tino Weinkauf
*/
class IVW_MODULE_DISCRETEDATATOOLS_API ComputeGridMeasure : public Processor
{ 
//Friends
//Types
public:

//Construction / Deconstruction
public:
    ComputeGridMeasure();
    virtual ~ComputeGridMeasure() = default;

//Methods
public:
    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    ///Our main computation function
    virtual void process() override;
    void updatePrimitiveOptions();

//Ports
public:
    DataSetInport dataInport;
    DataSetOutport dataOutport;

//Properties
public:
    OptionPropertyInt dimensionToMeasure;
//Attributes
private:

};

} // namespace
