/*********************************************************************
*  Author  : Anke Friederici
*  Init    : Wednesday, January 24, 2018 - 14:15:43
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <discretedatatools/discretedatatoolsmoduledefine.h>
#include <discretedatatools/ports/datasetport.h>

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/ports/volumeport.h>
#include <inviwo/core/datastructures/volume/volumeram.h>

namespace inviwo
{

class IVW_MODULE_DISCRETEDATATOOLS_API DataSetFromVolume : public Processor
{ 

public:
    DataSetFromVolume();
    virtual ~DataSetFromVolume() = default;

    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    virtual void process() override;

private:
    /// Data to be processed
    VolumeInport portInData;

    /// DataSet to add to, not necessary
    DataSetInport portInDataSet;

    /// DataSet output
    DataSetOutport portOutData;

    /// Name given to inout data in DataSet
    StringProperty channelName;
};


} // namespace inviwo
