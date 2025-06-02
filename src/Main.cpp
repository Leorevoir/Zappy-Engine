/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.cpp
*/

#include <Zap/Error.hpp>
#include <Zap/Logger.hpp>
#include <Zap/Macro.hpp>

#include <Zap/Render/RenderLoop.hpp>
#include <Zap/Window/Context.hpp>

// clang-format off
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// clang-format on

#include <memory>

int main(void)
{
    glfwInit();

    try {
        std::unique_ptr<zap::window::Context> window = std::make_unique<zap::window::Context>("Zappy", Vec2u{800, 600});
        std::unique_ptr<zap::render::Loop> loop = std::make_unique<zap::render::Loop>(60);

        loop->start(*window);
        loop->shutdown();
        window.reset();
        loop.reset();
        glfwTerminate();

    } catch (const zap::exception::Error &e) {
        zap::logger::error(e);
        return ERROR;
    }
    return SUCCESS;
}
