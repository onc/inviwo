/*********************************************************************************
*
* Inviwo - Interactive Visualization Workshop
*
* Copyright (c) 2012-2018 Inviwo Foundation
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*********************************************************************************/

#pragma once

#include "datachannel.h"
#include "bufferchannel.h"

namespace inviwo {
namespace dd {

template<typename T, ind N>
T* BufferGetter<T, N>::get(ind index) {
    std::array<T, N>& data = dynamic_cast<BufferChannel<T, N>&>(*Parent).get<std::array<T, N>>(index);
    return reinterpret_cast<T*>(&data);
}

template<typename T, ind N>
const T* BufferGetter<T, N>::get(ind index) const {
    std::array<T, N>& data = dynamic_cast<BufferChannel<T, N>&>(*Parent).get<std::array<T, N>>(index);
    return reinterpret_cast<T*>(&data);
}

template<typename T, ind N>
ChannelGetter<T, N>* BufferGetter<T, N>::New() const  {
    return new BufferGetter<T, N>(dynamic_cast<BufferChannel<T, N>*>(Parent));
}

template<typename T, ind N>
T* CachedGetter<T, N>::get(ind index) {
    ivwAssert(Parent, "No channel to iterate is set.");

    // No buffer, evaluate analytics.
    // Is the data up to date?
    if (DataIndex != index) {
        delete Data;
        Data = new std::array<T,N>();
        // Note: we could use the old memory again, but numCOmponents might change (improbable).
        // Also, we want segfaults when old data is accessed.

        Parent->fill(*Data, index);
        DataIndex = index;
    }

    // Always return data.
    // If the iterator is changed and dereferenced, the pointer becomes invalid.
    return reinterpret_cast<T*>(Data);
}

template<typename T, ind N>
const T* CachedGetter<T, N>::get(ind index) const {
    ivwAssert(Parent, "No channel to iterate is set.");

    // No buffer, evaluate analytics.
    // Is the data up to date?
    if (DataIndex != index) {
        delete Data;
        Data = new std::array<T,N>();
        // Note: we could use the old memory again, but numCOmponents might change (improbable).
        // Also, we want segfaults when old data is accessed.

        Parent->fill(Data, index);
        DataIndex = index;
    }

    // Always return data.
    // If the iterator is changed and dereferenced, the pointer becomes invalid.
    return reinterpret_cast<T*>(Data);
}


}  // namespace
}