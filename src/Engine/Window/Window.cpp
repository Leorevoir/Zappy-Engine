/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Window.cpp
*/

#include "Window.hpp"
#include "Error.hpp"
#include "Macro.hpp"

/**
* public
*/

/**
* @brief __ctor__
*/
zap::Window::Window(const math::Vector2<int> &size, const char *title)
{
    create(size, title);
}

/**
 * @brief __dtor__
 */
zap::Window::~Window()
{
    destroy();
}

extern "C" {
static void c_set_glfw_window_hints(const char UNUSED *title)
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

static void c_framebuffer_size_callback(GLFWwindow UNUSED *window, int width, int height)
{
    glViewport(ZAP_GLINT_VIEWPORT, ZAP_GLINT_VIEWPORT, width, height);
}
}

/**
* @brief Window::create
* @details create a new window context. if the old one is still active, destroy it
* @return void
*/
void zap::Window::create(const math::Vector2<int> &size, const char *title)
{
    destroy();
    c_set_glfw_window_hints(title);
    if ((_handle = glfwCreateWindow(size._x, size._y, title, nullptr, nullptr)) == nullptr) {
        throw exception::Error("Window::create", "failed to create GLFW window handle");
    }
    glfwMakeContextCurrent(_handle);
    glfwSetFramebufferSizeCallback(_handle, c_framebuffer_size_callback);
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw exception::Error("Window::create", "failed to initialize Glad");
    }
    glViewport(ZAP_GLINT_VIEWPORT, ZAP_GLINT_VIEWPORT, size._x, size._y);
}

/**
 * @brief Window::destroy
 * @details destroy the context handle pointer
 * @return void
 */
void zap::Window::destroy() noexcept
{
    if (_handle) {
        glfwDestroyWindow(_handle);
    }
    _handle = nullptr;
}

/**
 * @brief Window::getHandle
 * @details get the context window handle pointer
 * @return WindowPtr
 */
zap::WindowPtr zap::Window::getHandle() noexcept
{
    return _handle;
}

/**
 * @brief Window::swapBuffer
 * @details display the window
 * @return void
 */
void zap::Window::swapBuffer() const noexcept
{
    glfwSwapBuffers(_handle);
}

/**
* @brief Window::shouldClose
* @details return true if the window shouldClose else false
* @return bool true <|> false
*/
bool zap::Window::shouldClose() const noexcept
{
    return glfwWindowShouldClose(_handle);
}

/**
* @brief Window::close
* @details set the window shouldClose to true
* @return void
*/
void zap::Window::close() const noexcept
{
    glfwSetWindowShouldClose(_handle, GL_TRUE);
}
