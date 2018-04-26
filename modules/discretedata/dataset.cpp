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

void DataChannelMap::addChannel(SharedConstChannel sharedChannel)
{
        ChannelSet.insert
            ( std::make_pair
                ( std::make_pair
                    ( sharedChannel->getName()
                    , sharedChannel->getGridPrimitiveType())
                , sharedChannel ));
}

bool DataChannelMap::removeChannel(SharedConstChannel channel)
{
    return ChannelSet.erase(std::make_pair(channel->getName(), channel->getGridPrimitiveType()));
}

SharedConstChannel DataChannelMap::getFirstChannel() const
{
    auto it = ChannelSet.begin();

    if (it == ChannelSet.end()) return SharedConstChannel();

    return it->second;
}

SharedConstChannel DataChannelMap::getChannel(const std::string& name, const GridPrimitive definedOn) const
{
    auto it = ChannelSet.find(std::make_pair(name, definedOn));

    if (it == ChannelSet.end()) return SharedConstChannel();

    return it->second;
}

} // namespace
