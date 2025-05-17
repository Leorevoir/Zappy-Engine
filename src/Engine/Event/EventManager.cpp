#include "EventManager.hpp"
#include "Engine/Event/KeyEvent.hpp"
#include "Error.hpp"

/**
 * public
 */

/**
* @brief
* @details
* @return
*/
void zap::event::EventManager::init(WindowPtr window)
{
    if ((_window = window) == nullptr) {
        throw exception::Error("EventManager::init", "cannot initialize EventManager with a NULL WindowPtr");
    }
    glfwSetKeyCallback(_window, keyCallback);
}

/**
* @brief
* @details
* @return
*/
void zap::event::EventManager::pollEvents() noexcept
{
    glfwPollEvents();
}

/**
 *
 *
 */
void zap::event::EventManager::subscribe(const EventType type, EventDispatcher::Callback handler) noexcept
{
    _dispatcher.subscribe(type, handler);
}

/**
* private
*/

zap::WindowPtr zap::event::EventManager::_window = nullptr;
zap::event::EventDispatcher zap::event::EventManager::_dispatcher;

void zap::event::EventManager::keyCallback(WindowPtr UNUSED win, const int key, const int UNUSED scancode, const int action, const int UNUSED mods) noexcept
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
