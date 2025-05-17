#include "KeyEvent.hpp"

/**
 * public
 */

/**
 * KeyEvent
 */

zap::event::KeyEvent::KeyEvent(const int keycode) noexcept : _keycode(keycode)
{
    /* __ctor__ */
}

int zap::event::KeyEvent::getKeyCode() const noexcept
{
    return _keycode;
}

/**
 * KeyPressedEvent
 */

zap::event::EventType zap::event::KeyPressedEvent::getType() const noexcept
{
    return EventType::KeyPressed;
}

/**
 * KeyReleasedEvent
 */

zap::event::EventType zap::event::KeyReleasedEvent::getType() const noexcept
{
    return EventType::KeyReleased;
}
