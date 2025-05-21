/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** KeyEvent.hpp
*/

#pragma once

#include "IEvent.hpp"

namespace zap {

/**
* @class KeyEvent
* @brief Base class for key events.
* @pattern
*/
class KeyEvent : public IEvent
{
    public:
        explicit KeyEvent(int keycode) noexcept;

        [[nodiscard]] int getKeyCode() const noexcept;

    protected:
        int _keycode;
};

/**
* @class KeyPressedEvent
* @brief event triggered when a key is pressed.
* @pattern 
*/
class KeyPressedEvent : public KeyEvent
{
    public:
        using KeyEvent::KeyEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

/**
* @class KeyReleasedEvent
* @brief event triggered when a key is released.
* @pattern 
*/
class KeyReleasedEvent : public KeyEvent
{
    public:
        using KeyEvent::KeyEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

/**
* @class KeyHeldEvent
* @brief event triggered when a key is held down.
* @pattern
*/
class KeyHeldEvent : public KeyEvent
{
    public:
        using KeyEvent::KeyEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

}// namespace zap
