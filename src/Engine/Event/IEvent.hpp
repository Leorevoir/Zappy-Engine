/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IEvent.hpp
*/

#pragma once

namespace zap {

// clang-format off
enum class EventType {
    KeyPressed,
    KeyReleased,
    KeyHeld,
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
* @pattern Interface
*/
class IEvent
{
    public:
        virtual ~IEvent() = default;
        virtual EventType getType() const = 0;
};

}// namespace zap
