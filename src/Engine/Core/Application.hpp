/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.hpp
*/

#pragma once

#include "NonCopyable.hpp"

namespace zap::core {

/**
* @class Application
* @brief TODO
* @details TODO
* @pattern Singleton
*/
class Application final : public NonCopyable
{
    public:
        static Application &getInstance() noexcept;

        void run();

    private:
        explicit Application();
        ~Application();

        void _init();
        void _destroy() noexcept;
};
}// namespace zap::core
