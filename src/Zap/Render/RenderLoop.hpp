/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderLoop.hpp
*/

#pragma once

#include <Zap/Render/RenderEngine.hpp>
#include <Zap/Render/RenderWindow.hpp>
#include <Zap/Types.hpp>

namespace zap::render {

class Loop
{
    public:
        explicit Loop(const f64 frame_rate, render::Engine &engine) noexcept;
        ~Loop() noexcept;

        void start(abstract::Window &window);

    private:
        render::Engine &_engine;
        bool _is_running;
        f64 _frame_time;

        void _run(abstract::Window &window);
        void _destroy() noexcept;
};

}// namespace zap::render
