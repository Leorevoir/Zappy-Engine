/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.hpp
*/

#pragma once

#include <Engine/Render/Camera/Camera.hpp>
#include <Engine/Render/Model/Model.hpp>
#include <Engine/Shader/Shader.hpp>
#include <NonCopyable.hpp>

#include <memory>

namespace zap {

using ShaderPtr = std::shared_ptr<Shader>;
using ModelPtr = std::shared_ptr<Model>;
using CameraPtr = std::unique_ptr<Camera>;

/**
* @class Renderer
* @brief base renderer class, used to render everything you see
* @pattern singleton
*/
class Renderer : public abstract::NonCopyable
{
    public:
        static void initialize(WindowPtr window);
        static void render() noexcept;
        static void shutdown() noexcept;

    private:
        static void _register_moved_event(GLFWwindow *window, double xposIn, double yposIn);
        static void _register_scroll_event(GLFWwindow *window, double xoffset, double yoffset);
        static void _register_key_event(GLFWwindow *window, int key, int scancode, int action, int mods);

        static WindowPtr _window;
        static CameraPtr _camera;
        static ShaderPtr _planet_shader;
        static ShaderPtr _asteroid_shader;
        static ModelPtr _asteroid_model;
        static ModelPtr _planet_model;
};
}// namespace zap
