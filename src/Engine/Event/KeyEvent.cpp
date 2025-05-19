/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** KeyEvent.cpp
*/

#include "KeyEvent.hpp"

/**
 * public
 */

/**
 * KeyEvent
 */

zap::KeyEvent::KeyEvent(const int keycode) noexcept : _keycode(keycode)
{
    /* __ctor__ */
}

int zap::KeyEvent::getKeyCode() const noexcept
{
    return _keycode;
}

/**
 * KeyPressedEvent
 */

zap::EventType zap::KeyPressedEvent::getType() const noexcept
{
    return EventType::KeyPressed;
}

/**
 * KeyReleasedEvent
 */

zap::EventType zap::KeyReleasedEvent::getType() const noexcept
{
    return EventType::KeyReleased;
}
