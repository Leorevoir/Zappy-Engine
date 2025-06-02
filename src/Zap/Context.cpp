/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Context.cpp
*/

//INFO: context first because it includes GLFW & GLAD headers
#include <Zap/Window/Context.hpp>

#include <Zap/Context.hpp>
#include <Zap/Macro.hpp>
#include <Zap/Render/RenderLoop.hpp>

void zap::context::run(const char *title, ecs::Engine &game)
{
    run(title, game, Vec2u(ZAP_DEFAULT_WIDOW_SIZE), ZAP_DEFAULT_FRAMERATE);
}

void zap::context::run(const char *title, ecs::Engine &game, const Vec2u windowSize)
{
    run(title, game, windowSize, ZAP_DEFAULT_FRAMERATE);
}

void zap::context::run(const char *title, ecs::Engine &game, const Vec2u windowSize, f64 frame_rate)
{
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    auto render = std::make_unique<zap::render::Loop>(frame_rate, dynamic_cast<zap::render::Engine &>(game));
    auto window = std::make_unique<zap::window::Context>(title, windowSize);

    render->start(*window);
    (void) game;
    glfwTerminate();
}
