/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderTime.cpp
*/

// #include <Zap/Logger.hpp>
#include <Zap/Render/RenderTime.hpp>
/**
 * public
 */

zap::render::Time::Clock::Clock(f64 frame_time) : _frame_time(frame_time), _unprocessed_time(0.0), _last_time(now())
{
    /* __ctor__ */
}

/**
 * @brief should render or not
 */
bool zap::render::Time::Clock::tick()
{
    const auto current_time = now();
    const f64 passed_time = Duration(current_time - _last_time).count();

    _last_time = current_time;
    _unprocessed_time += passed_time;

    if (_unprocessed_time >= _frame_time) {
        _unprocessed_time -= _frame_time;
        // logger::debug("frame: ", _frame_time, "s");
        return true;
    }

    return false;
}

/**
* private
*/
