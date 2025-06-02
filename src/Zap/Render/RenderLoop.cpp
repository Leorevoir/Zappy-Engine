/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderLoop.cpp
*/

#include <Zap/Render/RenderLoop.hpp>
#include <Zap/Render/RenderTime.hpp>

#include <thread>

/**
 * public
 */

zap::render::Loop::Loop(const f64 frame_rate) noexcept : _is_running(false), _frame_time(1.0 / frame_rate)
{
    /* __ctor__ */
}

void zap::render::Loop::start(abstract::Window &window)
{
    _is_running = false;
    this->run(window);
}

void zap::render::Loop::shutdown()
{
    if (!_is_running) {
        return;
    }
    _is_running = false;
}

/**
* private
*/

void zap::render::Loop::run(abstract::Window &window)
{
    if (_is_running) {
        return;
    }

    _is_running = true;

    // const auto startup_time = zap::render::Time::now();
    zap::render::Time::Clock timer(_frame_time);
    int frames = 0;

    window.startup();
    //TODO: initialize the render engine

    while (_is_running) {

        bool should_render = timer.tick();

        if (window.shouldClose()) {
            shutdown();
        }

        if (should_render) {
            //TODO: engine each { |e| e.render }
            window.render();
            //TODO: engine each { |e| e.flush }
            frames += 1;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    //TODO: engine each { |e| e.shutdown }
    window.destroy();
}
