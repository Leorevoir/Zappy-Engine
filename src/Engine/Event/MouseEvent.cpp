/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** MouseEvent.cpp
*/

#include "MouseEvent.hpp"

/**
* MouseEvent
*/

zap::MouseEvent::MouseEvent(const math::Vector2<double> &position) noexcept : _position(position)
{
    /* __ctor__ */
}

const math::Vector2<double> zap::MouseEvent::getPosition() const noexcept
{
    return _position;
}

/**
* MouseMovedEvent
*/

zap::EventType zap::MouseMovedEvent::getType() const noexcept
{
    return EventType::MouseMoved;
}

/**
* MouseScrolledEvent
*/

zap::EventType zap::MouseScrolledEvent::getType() const noexcept
{
    return EventType::MouseScrolled;
}

/**
* MouseButtonEvent
*/

zap::MouseButtonEvent::MouseButtonEvent(int button) noexcept : _button(button)
{
    /* __ctor__ */
}

int zap::MouseButtonEvent::getButton() const noexcept
{
    return _button;
}

/**
* MouseButtonPressedEvent
*/

zap::EventType zap::MouseButtonPressedEvent::getType() const noexcept
{
    return EventType::MouseButtonPressed;
}

/**
 * MouseButtonReleasedEvent
*/

zap::EventType zap::MouseButtonReleasedEvent::getType() const noexcept
{
    return EventType::MouseButtonReleased;
}
