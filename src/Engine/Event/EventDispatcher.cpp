#include "EventDispatcher.hpp"

/**
* public
*/

void zap::event::EventDispatcher::subscribe(const EventType type, Callback handler) noexcept
{
    _callbacks[type].push_back(handler);
}

void zap::event::EventDispatcher::dispatch(const IEvent &event) const noexcept
{
    const auto it = _callbacks.find(event.getType());

    if (it != _callbacks.end()) {
        for (const auto &handler : it->second) {
            handler(event);
        }
    }
}
