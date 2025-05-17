#pragma once

namespace zap::event {

// clang-format off
enum class EventType {
    KeyPressed,
    KeyReleased,
    MouseMoved,
    MouseScrolled,
    MouseButtonPressed,
    MouseButtonReleased,
    WindowResized
};
// clang-format on

/**
* @class IEvent
* @brief base event interface
* @pattern observer
*/
class IEvent
{
    public:
        virtual ~IEvent() = default;
        virtual EventType getType() const = 0;
};

}// namespace zap::event
