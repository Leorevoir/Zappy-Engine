/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Timer.hpp
*/

#pragma once

#include "GLEngineTypes.hpp"
#include "NonCopyable.hpp"

namespace zap::core {

/**
* @class Timer
* @brief time-clock-related class
* @pattern singleton
*/
class Timer : public abstract::NonCopyable
{
    public:
        static void initialize() noexcept;
        static void update() noexcept;

        [[nodiscard]] static f64 getFPS() noexcept;
        [[nodiscard]] static f64 getDeltaTime() noexcept;
        [[nodiscard]] static f64 getTimeScale() noexcept;
        [[nodiscard]] static f64 getTotalTime() noexcept;

        static void setTimeScale(const u32 scale) noexcept;

    private:
        static f64 _lastFrameTime;
        static f64 _deltaTime;
        static f64 _timeScale;

        static f64 _fpsUpdateInterval;
        static f64 _lastFpsUpdate;
        static u32 _frameCount;
        static f64 _fps;
        static bool _initialized;
};
}// namespace zap::core
