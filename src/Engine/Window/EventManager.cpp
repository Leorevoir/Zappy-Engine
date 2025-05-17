#include "EventManager.hpp"
#include "Error.hpp"

/**
 * public
 */

/**
* @brief
* @details
* @return
*/
void zap::EventManager::init(zap::WindowPtr window)
{
    if ((_window = window) == nullptr) {
        throw exception::Error("EventManager::init", "cannot initialize EventManager with a NULL WindowPtr");
    }
}

/**
* @brief
* @details
* @return
*/
void zap::EventManager::pollEvents() noexcept
{
    glfwPollEvents();
}

/**
* @brief
* @details
* @return
*/
bool zap::EventManager::isKeyPressed(const int key) noexcept
{
    if (!_window) {
        return false;
    }
    return glfwGetKey(_window, key) == GLFW_PRESS;
}

/**
* @brief
* @details
* @return
*/
bool zap::EventManager::isButtonPressed(const int button) noexcept
{
    if (!_window) {
        return false;
    }
    return glfwGetMouseButton(_window, button) == GLFW_PRESS;
}

/**
* @brief
* @details
* @return
*/
const math::Vector2<double> zap::EventManager::getCursorPosition() noexcept
{
    math::Vector2<double> vec2;

    if (_window) {
        return vec2;
    }
    glfwGetCursorPos(_window, &vec2._x, &vec2._y);
    return vec2;
}

/**
* private
*/

zap::WindowPtr zap::EventManager::_window = nullptr;
