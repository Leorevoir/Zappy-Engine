/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Window.hpp
*/

#pragma once

#include "GLEngineTypes.hpp"

#include "Engine/Math/Vector2.hpp"

namespace zap {

/**
* @class Window
* @brief
* @pattern
*/
class Window final
{
    public:
        explicit Window(const math::Vector2<int> &size, const char *title = "Engine");
        constexpr explicit Window() = default;
        ~Window();

        [[nodiscard]] WindowPtr getHandle() noexcept;
        [[nodiscard]] bool shouldClose() const noexcept;

        void create(const math::Vector2<int> &size, const char *title = "Engine");
        void destroy() noexcept;
        void close() const noexcept;
        void swapBuffer() const noexcept;

    private:
        WindowPtr _handle = nullptr;
};
}// namespace zap
