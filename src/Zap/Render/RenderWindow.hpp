/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderWindow.hpp
*/

#pragma once

#include <Zap/Types.hpp>

namespace zap::render::abstract {

class Window
{
    public:
        virtual ~Window() = default;

        virtual void startup(void) = 0;
        virtual bool shouldClose(void) const = 0;
        virtual void render(void) = 0;
        virtual void destroy(void) = 0;

        virtual Vec2u getSize(void) const = 0;
        virtual void setSize(const Vec2u &size) = 0;
};

}// namespace zap::render::abstract
