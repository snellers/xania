#include "DescriptorList.hpp"
#include "Mud.hpp"

void DescriptorList::reap_closed() {
    // In C++20 we get map::erase_if. For now, we copy paste from cppreference.
    for (auto it = descriptors_.begin(), last = descriptors_.end(); it != last;) {
        if (it->second.is_closed())
            it = descriptors_.erase(it);
        else
            ++it;
    }
}

Descriptor *DescriptorList::create(uint32_t channel_id, Mud &mud) {
    if (find_by_channel(channel_id))
        return nullptr;
    return &descriptors_
                .emplace(std::piecewise_construct, std::forward_as_tuple(channel_id),
                         std::forward_as_tuple(channel_id, mud))
                .first->second;
}

Descriptor *DescriptorList::find_by_channel(uint32_t channel_id) {
    if (auto it = descriptors_.find(channel_id); it != descriptors_.end())
        return &it->second;
    return nullptr;
}
