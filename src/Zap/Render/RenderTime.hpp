/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** RenderTime.hpp
*/

#pragma once

#include <Zap/Types.hpp>
#include <chrono>

namespace zap::render::Time {

/**
* @brief macros because C++ types are too verbose
*/

using SteadyClock = std::chrono::steady_clock;
using TimePoint = SteadyClock::time_point;
using Duration = std::chrono::duration<f64>;

/**
* @brief get the current time point
*/
static inline TimePoint now()
{
    return SteadyClock::now();
}

/**
* @brief get the time since the given time point
*/
static inline f64 timeSince(const TimePoint &start)
{
    return Duration(now() - start).count();
}

/**
* @class Clock
* @brief simple clock class to handle frame timing
*/
class Clock final
{
    public:
        explicit Clock(f64 frameTime);
        ~Clock() = default;

        bool tick();//INFO: true -> shouldRender

    private:
        f64 _frame_time;
        f64 _unprocessed_time;
        TimePoint _last_time;
};

}// namespace zap::render::Time
