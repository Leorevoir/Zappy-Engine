/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.hpp
*/

#pragma once

#include "Engine/Window/Window.hpp"
#include "NonCopyable.hpp"
#include <memory>

namespace zap::core {

/**
* @class Application
* @brief TODO
* @details TODO
* @pattern Singleton
*/
class Application final : public abstract::NonCopyable
{
    public:
        static Application &getInstance() noexcept;

        void run();

    private:
        explicit Application();
        ~Application();

        void _init();
        void _destroy() noexcept;

        std::unique_ptr<Window> _window;
};
}// namespace zap::core
