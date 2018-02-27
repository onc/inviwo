/*********************************************************************
 *  Author  : Tino Weinkauf
 *  Init    : Sunday, October 01, 2017 - 05:17:04
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <discretedatatools/discretedatatoolsmodule.h>
#include <discretedatatools/processors/datasetfrombase.h>
#include <discretedatatools/processors/computegridmeasure.h>
//#include <discretedatatools/processors/meshfromdataset.h>
#include <discretedatatools/processors/volumefromdataset.h>

namespace inviwo
{

DiscreteDataToolsModule::DiscreteDataToolsModule(InviwoApplication* app) : InviwoModule(app, "discretedatatools")
{
    // Add a directory to the search path of the Shadermanager
    // ShaderManager::getPtr()->addShaderSearchPath(getPath(ModulePath::GLSL));

    // Register objects that can be shared with the rest of inviwo here:
    
    // Processors
    registerProcessor<DataSetFromVolume>();
    registerProcessor<ComputeGridMeasure>();
    registerProcessor<VolumeFromDataSet>();
    
    // Properties

    // Ports
    registerPort<DataSetOutport>();
    registerPort<DataSetInport>();

}

} // namespace
