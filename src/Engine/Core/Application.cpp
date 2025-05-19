/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.cpp
*/

#include "Application.hpp"

#include "Engine/Core/Timer.hpp"
#include "Engine/Event/EventManager.hpp"
#include "Engine/Event/KeyEvent.hpp"
#include "Engine/Render/Renderer.hpp"
#include "Engine/Window/Window.hpp"

#include "Error.hpp"
#include "Macro.hpp"

#include <iostream>
#include <thread>

/**
* public
*/

/**
* @brief Application::getInstance
* @details get instance of the Application (singleton)
* @return Application & (ref to the instance)
*/
zap::core::Application &zap::core::Application::getInstance() noexcept
{
    static Application instance;

    return instance;
}

/**
* @brief Application::run
* @details main entry-point, run the application
* @return void
*/
void zap::core::Application::run()
{
    Window window(ZAP_DEFAULT_WIDOW_SIZE);
    Timer::initialize();
    EventManager::init(window.getHandle());
    Renderer::initialize(window.getHandle());

    EventManager::subscribe(EventType::KeyPressed, [&](const IEvent &e) {
        const KeyPressedEvent &keyEvent = static_cast<const KeyPressedEvent &>(e);

        if (keyEvent.getKeyCode() == GLFW_KEY_ESCAPE) {
            window.close();
        }
    });

    while (!window.shouldClose()) {
        EventManager::pollEvents();
        Timer::update();
        Renderer::render();
        window.swapBuffer();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));// <<~60 FPS
    }
}

/**
* private
*/

/**
 * @brief __ctor__
 * @details private __ctor__
 * @return [this]
 */
zap::core::Application::Application()
{
    _init();
}

/**
* @brief __dtor__
* @details private __dtor__
* @return [~this]
*/
zap::core::Application::~Application()
{
    _destroy();
}

/**
* @brief Application::_init
* @details initialize GLFW context & ressources
* @return void
*/
void zap::core::Application::_init()
{
    if (glfwInit() == GLFW_FALSE) {
        throw exception::Error("core::Application::_init()", "Failed to initialize GLFW");
    }
}

/**
* @brief Application::_destroy
* @details destroy GLFW context & ressources
* @return void
*/
void zap::core::Application::_destroy() noexcept
{
    glfwTerminate();
}
