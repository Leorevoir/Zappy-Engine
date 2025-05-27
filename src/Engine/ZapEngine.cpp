/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** ZapEngine.cpp
*/

#include <Engine/Event/EventManager.hpp>
#include <Engine/Event/KeyEvent.hpp>
#include <Engine/Render/Renderer.hpp>
#include <Engine/System/Timer.hpp>
#include <Engine/System/Window.hpp>
#include <Engine/ZapEngine.hpp>

#include <Parser/Jsonc.hpp>
#include <Parser/JsoncObject.hpp>
#include <Parser/JsoncTypes.hpp>

#include <Error.hpp>
#include <Macro.hpp>

#include <memory>
#include <utility>

static bool is_initialized = false;
static zap::parser::JsonValue _jsonc = zap::parser::JsonValue();

/**
 * public
 */

/**
* @brief Engine::initialize
* @details initialize the Engine
* @return void
*/
void zap::Engine::initialize(const char *RESTRICT jsonc_config)
{
    if (is_initialized) {
        return;
    }
    static zap::Engine __attribute__((unused)) instance(jsonc_config);
}

static std::unique_ptr<zap::Window> _window = nullptr;

/**
 * @brief Engine::getWindow
 * @details get the reference of the window instance
 * @return Window &
 */
zap::Window &zap::Engine::getWindow() noexcept
{
    return *_window.get();
}

/**
* private
*/

/**
 * @brief __ctor__
 * @details private __ctor__
 * @return [this]
 */
zap::Engine::Engine(const char *RESTRICT jsonc_config)
{
    _jsonc = parser::Jsonc(jsonc_config);
    _init();
}

/**
* @brief __dtor__
* @details private __dtor__
* @return [~this]
*/
zap::Engine::~Engine() noexcept
{
    _destroy();
}

static void _initialize_ptr()
{
    const auto w = zap::parser::getObject(_jsonc, "window");

    if (w.find("size") == w.end()) {
        throw zap::exception::Error("Engine::_initialize_ptr()", "Key 'size' not found in JSON object");
    }
    _window = std::make_unique<zap::Window>(zap::parser::getVector2<zap::i32>(w.at("size"), "width", "height"));
}

static void _initialize_singleton()
{
    zap::Timer::initialize();
    zap::Renderer::initialize(_window->getHandle());
    zap::EventManager::initialize(_window->getHandle());
}

static void _initialize_default_event()
{
    zap::EventManager::subscribe(zap::EventType::KeyPressed, [&](const zap::IEvent &e) {
        const zap::KeyPressedEvent &keyEvent = static_cast<const zap::KeyPressedEvent &>(e);

        if (keyEvent.getKeyCode() == GLFW_KEY_ESCAPE) {
            _window->close();
        }
    });
}

/**
* @brief Engine::_init
* @details initialize GLFW context & ressources
* @return void
*/
void zap::Engine::_init()
{
    if (glfwInit() == GLFW_FALSE) {
        throw exception::Error("core::Application::_init()", "Failed to initialize GLFW");
    }
    _initialize_ptr();
    _initialize_singleton();
    _initialize_default_event();
    is_initialized = true;
}

static void _release_ptr()
{
    _window.reset();
}

/**
* @brief Engine::_destroy
* @details destroy GLFW context & ressources
* @return void
*/
void zap::Engine::_destroy()
{
    Renderer::shutdown();

    _release_ptr();
    glfwTerminate();
}
