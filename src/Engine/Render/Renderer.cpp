/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"
#include "Macro.hpp"

/**
* public
*/

/**
* @brief Renderer::initialize
* @details initialize the renderer with a window (to be rendered to)
* @return void
*/
void zap::Renderer::initialize(WindowPtr window) noexcept
{
    _window = window;
}

void zap::Renderer::shutdown() noexcept
{
    /* __dtor__ >> clear any shader <$| GPU |$> ressources */
}

extern "C" {
static void c_render_clear_context(void)
{
    glClearColor(ZAP_GL_CLEAR_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);
}
}

void zap::Renderer::render() noexcept
{
    c_render_clear_context();
}

/**
* private
*/

zap::WindowPtr zap::Renderer::_window = nullptr;
