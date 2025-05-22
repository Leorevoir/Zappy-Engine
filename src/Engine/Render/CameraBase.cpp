#include "CameraBase.hpp"

#include <Engine/Event/EventManager.hpp>
#include <Engine/Event/KeyEvent.hpp>
#include <Engine/Event/MouseEvent.hpp>

#include <Engine/Core/Timer.hpp>

#include <iostream>

/**
* protected
*/

void zap::abstract::CameraBase::_create_camera_events() noexcept
{
    EventManager::subscribe(EventType::KeyHeld, [&](const IEvent &e) {
        const KeyHeldEvent &keyEvent = static_cast<const KeyHeldEvent &>(e);

        std::cout << "delta time: " << core::Timer::getDeltaTime() << std::endl;
        switch (keyEvent.getKeyCode()) {
            case GLFW_KEY_W:
                keyPressed(Direction::FORWARD, static_cast<f32>(core::Timer::getDeltaTime()));
                break;
            case GLFW_KEY_S:
                keyPressed(Direction::BACKWARD, static_cast<f32>(core::Timer::getDeltaTime()));
                break;
            case GLFW_KEY_A:
                keyPressed(Direction::LEFT, static_cast<f32>(core::Timer::getDeltaTime()));
                break;
            case GLFW_KEY_D:
                keyPressed(Direction::RIGHT, static_cast<f32>(core::Timer::getDeltaTime()));
                break;
            default:
                break;
        }
    });

    EventManager::subscribe(EventType::MouseMoved, [&](const IEvent &e) {
        const MouseMovedEvent &mouseEvent = static_cast<const MouseMovedEvent &>(e);
        const math::Vector2<double> &pos = mouseEvent.getPosition();

        static bool is_first = true;

        static f32 last_x = 0.0f;
        static f32 last_y = 0.0f;

        const f32 xpos = static_cast<float>(pos._x);
        const f32 ypos = static_cast<float>(pos._y);

        if (is_first) {
            last_x = xpos;
            last_y = ypos;
            is_first = false;
        }

        const f32 xoffset = xpos - last_x;
        const f32 yoffset = last_y - ypos;

        last_x = xpos;
        last_y = ypos;

        mouseMoved(xoffset, yoffset);
    });

    EventManager::subscribe(EventType::MouseScrolled, [&](const IEvent &e) {
        const MouseScrolledEvent &mouseEvent = static_cast<const MouseScrolledEvent &>(e);
        const math::Vector2<double> &pos = mouseEvent.getPosition();

        mouseScroll(static_cast<f32>(pos._y));
    });
}
