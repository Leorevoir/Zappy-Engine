/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Context.cpp
*/

//INFO: context first because it includes GLFW & GLAD headers
#include "Zap/Error.hpp"
#include "Zap/Logger.hpp"
#include <Zap/Window/Context.hpp>

#include <Zap/Context.hpp>
#include <Zap/Macro.hpp>
#include <Zap/Render/RenderLoop.hpp>

i32 zap::context::run(const char *title, ecs::Engine &game)
{
    return run(title, game, Vec2u(ZAP_DEFAULT_WIDOW_SIZE), ZAP_DEFAULT_FRAMERATE);
}

i32 zap::context::run(const char *title, ecs::Engine &game, const Vec2u windowSize)
{
    return run(title, game, windowSize, ZAP_DEFAULT_FRAMERATE);
}

i32 zap::context::run(const char *title, ecs::Engine &game, const Vec2u windowSize, f64 frame_rate)
{
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    const auto cleanup = [&]() { glfwTerminate(); };

    try {
        auto render = std::make_unique<zap::render::Loop>(frame_rate, dynamic_cast<zap::render::Engine &>(game));
        auto window = std::make_unique<zap::window::Context>(title, windowSize);

        render->start(*window);

        render.reset();
        window.reset();

        cleanup();
    } catch (zap::exception::Error &e) {
        cleanup();
        zap::logger::error(e);
        return ERROR;
    }
    return SUCCESS;
}
