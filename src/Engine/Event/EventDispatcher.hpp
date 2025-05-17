#pragma once

#include "IEvent.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

namespace zap::event {

class EventDispatcher final
{
    public:
        using Callback = std::function<void(const IEvent &)>;
        using CallbackMap = std::unordered_map<EventType, std::vector<Callback>>;

        void dispatch(const IEvent &event) const noexcept;
        void subscribe(const EventType type, Callback handler) noexcept;

    private:
        CallbackMap _callbacks;
};

}// namespace zap::event
