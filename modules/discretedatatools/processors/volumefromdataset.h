/*********************************************************************
 *  Author  : Tino Weinkauf
 *  Init    : Monday, February 26, 2018 - 15:00:01
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
#include <inviwo/core/ports/volumeport.h>
//#include <inviwo/core/ports/meshport.h>
//#include <inviwo/core/properties/boolcompositeproperty.h>
//#include <inviwo/core/properties/boolproperty.h>
//#include <inviwo/core/properties/buttonproperty.h>
//#include <inviwo/core/properties/compositeproperty.h>
//#include <inviwo/core/properties/fileproperty.h>
//#include <inviwo/core/properties/minmaxproperty.h>
//#include <inviwo/core/properties/optionproperty.h>
//#include <inviwo/core/properties/ordinalproperty.h>
//#include <inviwo/core/properties/stringproperty.h>
//#include <inviwo/core/properties/transferfunctionproperty.h>

#include <modules/discretedatatools/ports/datasetport.h>

namespace inviwo
{

/** \docpage{org.inviwo.VolumeFromDataSet, Volume From Data Set}
    ![](org.inviwo.VolumeFromDataSet.png?classIdentifier=org.inviwo.VolumeFromDataSet)

    Converts a DataSet into a Volume.
    
    ### Inports
      * __InDataSet__ Input DataSet to be converted.
    
    ### Outports
      * __OutVolume__ Converted volume.
*/


/** \class VolumeFromDataSet
    \brief Converts a DataSet to a Volume
    
    Requires a Structured Grid in the data set.
    Fails if that is not given.

    @author Tino Weinkauf
*/
class IVW_MODULE_DISCRETEDATATOOLS_API VolumeFromDataSet : public Processor
{ 
//Friends
//Types
public:

//Construction / Deconstruction
public:
    VolumeFromDataSet();
    virtual ~VolumeFromDataSet() = default;

//Methods
public:
    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    ///Our main computation function
    virtual void process() override;

//Ports
public:
    ///Input dataset
    DataSetInport portInDataSet;

    ///Output volume
    VolumeOutport portOutVolume;

//Properties
public:

//Attributes
private:

};

} // namespace
