/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** EventManager.cpp
*/

#include "EventManager.hpp"
#include "Engine/Event/KeyEvent.hpp"
#include "Error.hpp"

/**
 * public
 */

/**
* @brief EventManager::initialize
* @details initialize the EventManager with a window
* @param window the window to use
* @return void
*/
void zap::EventManager::initialize(WindowPtr window)
{
    if ((_window = window) == nullptr) {
        throw exception::Error("EventManager::init", "cannot initialize EventManager with a NULL WindowPtr");
    }
    glfwSetKeyCallback(_window, keyCallback);
}

/**
* @brief EventManager::pollEvents
* @details poll the events from the window
* @return void
*/
void zap::EventManager::pollEvents() noexcept
{
    glfwPollEvents();
}

/**
* @brief EventManager::subscribe
* @details subscribe a callback to an event type
* @param type the event type
* @param handler the callback to call when the event is dispatched
*/
void zap::EventManager::subscribe(const EventType type, EventDispatcher::Callback handler) noexcept
{
    _dispatcher.subscribe(type, handler);
}

/**
* private
*/

zap::WindowPtr zap::EventManager::_window = nullptr;
zap::EventDispatcher zap::EventManager::_dispatcher;

/**
* @brief EventManager::keyCallback - OpenGL entry-point
* @details callback for the key event (called by OpenGL)
* @return void
*/
void zap::EventManager::keyCallback(WindowPtr UNUSED win, const int key, const int UNUSED scancode, const int action, const int UNUSED mods) noexcept
{
    switch (action) {
        case GLFW_PRESS: {
            const KeyPressedEvent e(key);
            _dispatcher.dispatch(e);
            break;
        }
        case GLFW_RELEASE: {
            const KeyReleasedEvent e(key);
            _dispatcher.dispatch(e);
            break;
        }
        default:
            break;
    }
}
