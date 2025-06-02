/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderLoop.cpp
*/

#include <Zap/Render/RenderLoop.hpp>
#include <chrono>
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

    const auto startup_time = std::chrono::steady_clock::now();
    int frames = 0;

    window.startup();
    //TODO: initialize the render engine

    f64 last_time = std::chrono::duration<f64>(std::chrono::steady_clock::now() - startup_time).count();
    f64 unprocessed_time = 0.0f;

    while (_is_running) {

        //TODO: time logic in static singleton
        bool should_render = false;
        const f64 start_time = std::chrono::duration<f64>(std::chrono::steady_clock::now() - startup_time).count();
        const f64 passed_time = start_time - last_time;//INFO: how long the previous frame took
        last_time = start_time;
        unprocessed_time += passed_time;

        while (unprocessed_time >= _frame_time) {
            should_render = true;
            unprocessed_time -= _frame_time;

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
    }
    //TODO: engine each { |e| e.shutdown }
    window.destroy();
}
