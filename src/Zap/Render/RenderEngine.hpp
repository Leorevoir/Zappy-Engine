/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderEngine.hpp
*/

#pragma once

#include <Zap/Render/RenderWindow.hpp>

namespace zap::render {

class Engine
{
    public:
        virtual ~Engine() = default;

        virtual void start(abstract::Window &window) = 0;
        virtual void render(void) = 0;
        virtual void flush(void) = 0;
};

}// namespace zap::render
