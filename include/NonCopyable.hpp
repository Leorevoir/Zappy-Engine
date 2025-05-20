/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** NonCopyable.hpp
*/

#pragma once

namespace zap::abstract {

/**
* @class NonCopyable
* @brief utility class taht makes any derived class non-copyable
*/
class NonCopyable
{
    protected:
        constexpr explicit NonCopyable() = default;
        ~NonCopyable() = default;

    private:
        constexpr explicit NonCopyable(NonCopyable &&) = delete;
        constexpr explicit NonCopyable(const NonCopyable &) = delete;

        constexpr NonCopyable &operator=(NonCopyable &&) = delete;
        constexpr NonCopyable &operator=(const NonCopyable &) = delete;
};
}// namespace zap::abstract
