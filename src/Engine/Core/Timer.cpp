/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Timer.cpp
*/

#include "Timer.hpp"

/**
* public
*/

/**
* @brief Timer::initialize
* @details initialize the timer
* @info called by core::Application
 */
void zap::core::Timer::initialize() noexcept
{
    if (!_initialized) {
        _lastFrameTime = glfwGetTime();
        _lastFpsUpdate = _lastFrameTime;
        _initialized = true;
    }
}

/**
* @brief Timer::update
* @details update the delta-time and fps
* @info called by core::Application
* @return void
*/
void zap::core::Timer::update() noexcept
{
    if (!_initialized) {
        initialize();
    }

    const f64 currentTime = getTotalTime();

    _deltaTime = (currentTime - _lastFrameTime) * _timeScale;
    _lastFrameTime = currentTime;
    ++_frameCount;
    if (currentTime - _lastFpsUpdate >= _fpsUpdateInterval) {
        _fps = static_cast<f64>(_frameCount) / (currentTime - _lastFpsUpdate);
        _frameCount = 0;
        _lastFpsUpdate = currentTime;
    }
}

/**
 * public getters
 */

zap::f64 zap::core::Timer::getDeltaTime() noexcept
{
    return _deltaTime;
}

zap::f64 zap::core::Timer::getFPS() noexcept
{
    return _fps;
}

zap::f64 zap::core::Timer::getTimeScale() noexcept
{
    return _timeScale;
}

zap::f64 zap::core::Timer::getTotalTime() noexcept
{
    return glfwGetTime();
}

/**
 * public setters
 */

void zap::core::Timer::setTimeScale(const zap::u32 scale) noexcept
{
    if (scale > 0) {
        _timeScale = scale;
    } else {
        _timeScale = 1.0;
    }
}

/**
* private
*/

zap::f64 zap::core::Timer::_lastFrameTime = 0.0;
zap::f64 zap::core::Timer::_deltaTime = 0.0;
zap::f64 zap::core::Timer::_timeScale = 1.0;
zap::f64 zap::core::Timer::_fpsUpdateInterval = 0.5;
zap::f64 zap::core::Timer::_lastFpsUpdate = 0.0;
zap::u32 zap::core::Timer::_frameCount = 0;
zap::f64 zap::core::Timer::_fps = 0.0;
bool zap::core::Timer::_initialized = false;
