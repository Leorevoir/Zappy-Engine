/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** WindowContext.hpp
*/

#pragma once

#include <Zap/Render/RenderWindow.hpp>

// clang-format off
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// clang-format on

namespace zap::window {

class Context final : public render::abstract::Window
{
    public:
        explicit Context(const char *title, const Vec2u &size);
        ~Context() override;

        void startup(void) override;

        bool shouldClose(void) const override;
        void render(void) override;
        void destroy(void) override;

        Vec2u getSize(void) const override;
        void setSize(const Vec2u &size) override;

    private:
        GLFWwindow *_handle = nullptr;

        void create(const char *title, const Vec2u &size);
};

}// namespace zap::window
