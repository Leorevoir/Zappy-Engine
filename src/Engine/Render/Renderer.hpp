/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.hpp
*/

#pragma once

#include "GLEngineTypes.hpp"
#include "NonCopyable.hpp"

namespace zap {

/**
* @class Renderer
* @brief base renderer class, used to render everything you see
* @pattern singleton
*/
class Renderer : public NonCopyable
{
    public:
        static void initialize(WindowPtr window) noexcept;
        static void render() noexcept;
        static void shutdown() noexcept;

    private:
        static WindowPtr _window;
};
}// namespace zap
