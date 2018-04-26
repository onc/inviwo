/*********************************************************************
*  Author  : Anke Friederici & Tino Weinkauf
*  Init    : Thursday, November 23, 2017 - 17:24:39
*
*  Project : KTH Inviwo Modules
*
*  License : Follows the Inviwo BSD license model
*********************************************************************
*/

namespace inviwo
{

template <typename T>
std::shared_ptr<const DataChannel<T>> DataChannelMap::getFirstChannel() const
{
    SharedConstChannel channel = getFirstChannel();

    return std::dynamic_pointer_cast<const DataChannel<T>, const Channel> (channel);
}

template <typename T>
std::shared_ptr<const DataChannel<T>> DataChannelMap::getChannel(const std::string& name, GridPrimitive definedOn) const
{
    return getChannel(name.c_str(), definedOn);
}

template <typename T>
std::shared_ptr<const DataChannel<T>> DataChannelMap::getChannel(const char* name, GridPrimitive definedOn) const
{
    SharedConstChannel channel = getChannel(name, definedOn);

    return std::dynamic_pointer_cast<const DataChannel<T>, const Channel> (channel);
}

template<typename T>
std::shared_ptr<const BufferChannel<T>> DataChannelMap::getAsBuffer(const std::string& name, GridPrimitive definedOn) const
{
    SharedConstChannel channel = getChannel(name, definedOn);

    // Data is not present in this data set.
    if (!channel.get())
        return std::shared_ptr<const BufferChannel<T>>();

    // Try to cast the channel to DataChannel<T>.
    // Return empty shared_ptr if unsuccessfull.
    std::shared_ptr<const DataChannel<T>> dataChannel
        = std::dynamic_pointer_cast<const DataChannel<T>, const Channel>(channel);

    // Check for nullptr inside
    if (!dataChannel.get())
        return std::shared_ptr<const BufferChannel<T>>();

    // Try to cast the channel to buffer directly.
    // If successfull, return a shared pointer to the buffer directly.
    // (Shared pointer remains valid and shares the reference counter).
    std::shared_ptr<const BufferChannel<T>> bufferChannel
        = std::dynamic_pointer_cast<const BufferChannel<T>, const Channel>(channel);

    // Check for nullptr inside.
    if (bufferChannel.get())
        return bufferChannel;

    // Copy data over.
    BufferChannel<T>* buffer = new BufferChannel<T>(dataChannel->getNumElements(), dataChannel->getNumComponents(), name, definedOn);
    for (ind element = 0; element < dataChannel->getNumElements(); ++element)
        dataChannel->fill(buffer->get(element), element);

    buffer->copyMetaDataFrom(*dataChannel.get());

    return std::shared_ptr<const BufferChannel<T>>(buffer);
}

} // namespace
