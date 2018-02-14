/*********************************************************************
 *  Author  : Anke Friederici & Tino Weinkauf
 *  Init    : Thursday, November 23, 2017 - 17:24:39
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include "dataset.h"
#include "bufferchannel.h"

namespace inviwo
{

SharedChannel DataChannelMap::addChannel(Channel* const channel)
{
    SharedChannel sharedChannel(channel);
    addChannel(sharedChannel);

    return sharedChannel;
}

void DataChannelMap::addChannel(SharedChannel sharedChannel)
{
        ChannelSet.insert
            ( std::make_pair
                ( std::make_pair
                    ( sharedChannel->getName()
                    , sharedChannel->getGridPrimitiveType())
                , sharedChannel ));
}

bool DataChannelMap::removeChannel(SharedChannel channel)
{
    return ChannelSet.erase(std::make_pair(channel->getName(), channel->getGridPrimitiveType()));
}

SharedConstChannel DataChannelMap::getFirstChannel() const
{
    auto it = ChannelSet.begin();

    if (it == ChannelSet.end()) return SharedConstChannel();

    return std::const_pointer_cast<const Channel, Channel>(it->second);
}

SharedChannel DataChannelMap::getChannel(const std::string& name, const GridPrimitive definedOn)
{
    auto it = ChannelSet.find(std::make_pair(name, definedOn));
    
    if (it == ChannelSet.end())
        return SharedChannel();
    return it->second;
}

SharedConstChannel DataChannelMap::getChannel(const std::string& name, const GridPrimitive definedOn) const
{
    auto it = ChannelSet.find(std::make_pair(name, definedOn));

    if (it == ChannelSet.end()) return SharedConstChannel();

    return std::const_pointer_cast<const Channel, Channel>(it->second);
}

} // namespace
