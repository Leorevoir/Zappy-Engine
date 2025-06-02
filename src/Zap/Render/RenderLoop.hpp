/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderLoop.hpp
*/

#pragma once

#include <Zap/Render/RenderWindow.hpp>
#include <Zap/Types.hpp>

namespace zap::render {

class Loop
{
    public:
        explicit Loop(const f64 frame_rate) noexcept;

        void start(abstract::Window &window);
        void shutdown(void);

    private:
        bool _is_running;
        f64 _frame_time;

        void run(abstract::Window &window);
};

}// namespace zap::render
