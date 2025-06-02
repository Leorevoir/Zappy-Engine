/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** WindowContext.cpp
*/

#include <Zap/Error.hpp>
#include <Zap/Macro.hpp>

#include <Zap/Window/Context.hpp>

/**
* public
*/

/**
 * @brief __ctor__
 */
zap::window::Context::Context(const char *title, const Vec2u &size)
{
    create(title, size);
}

/**
 * @brief __dtor__
 */
zap::window::Context::~Context()
{
    destroy();
}

static void _set_glfw_window_hints(const char UNUSED *title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ZAP_OPENGL_CONTEXT_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ZAP_OPENGL_CONTEXT_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    //TODO: antialiasing

#if defined(__linux__)
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, title);
    glfwWindowHintString(GLFW_X11_CLASS_NAME, title);
    glfwWindowHintString(GLFW_X11_INSTANCE_NAME, title);
#endif

#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void zap::window::Context::startup(void)
{
    if (_handle == nullptr) {
        throw exception::Error("window::Context::startup", "GLFW window handle is null");
    }
    glfwMakeContextCurrent(_handle);
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw exception::Error("window::Context::startup", "failed to initialize GLAD");
    }
}

void zap::window::Context::render(void)
{
    if (_handle == nullptr) {
        throw exception::Error("window::Context::render", "GLFW window handle is null");
    }
    glfwSwapBuffers(_handle);
    glfwPollEvents();
}

void zap::window::Context::destroy(void)
{
    if (_handle == nullptr) {
        return;
    }
    glfwDestroyWindow(_handle);
    _handle = nullptr;
}

/**
 * getters/setters
 */

Vec2u zap::window::Context::getSize(void) const
{
    if (_handle == nullptr) {
        throw exception::Error("window::Context::getSize", "GLFW window handle is null");
    }

    int width = 0;
    int height = 0;

    glfwGetWindowSize(_handle, &width, &height);
    return Vec2u(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

void zap::window::Context::setSize(const Vec2u &size)
{
    if (_handle == nullptr) {
        throw exception::Error("window::Context::setSize", "GLFW window handle is null");
    }
    glfwSetWindowSize(_handle, static_cast<int>(size._x), static_cast<int>(size._y));
}

bool zap::window::Context::shouldClose(void) const
{
    if (_handle == nullptr) {
        throw exception::Error("window::Context::shouldClose", "GLFW window handle is null");
    }
    return glfwWindowShouldClose(_handle);
}

/**
* private
*/

void zap::window::Context::create(const char *title, const Vec2u &size)
{
    destroy();
    _set_glfw_window_hints(title);
    if ((_handle = glfwCreateWindow(static_cast<int>(size._x), static_cast<int>(size._y), title, nullptr, nullptr)) == nullptr) {
        throw exception::Error("window::Context::create", "failed to create GLFW context");
    }
}
