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

#include <memory>

int main(void)
{

    try {

        if (glfwInit() == GLFW_FALSE) {
            throw zap::exception::Error("window::Context::create", "failed to initialize GLFW");
        }

        std::unique_ptr<zap::window::Context> window = std::make_unique<zap::window::Context>("kurwa zappierdole", Vec2u{800, 600});
        std::unique_ptr<zap::render::Loop> loop = std::make_unique<zap::render::Loop>(60);

        loop->start(*window);
        loop->shutdown();

        glfwTerminate();

    } catch (const zap::exception::Error &e) {
        zap::logger::error(e);
        return ERROR;
    }

    return SUCCESS;
}
