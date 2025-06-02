/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Error.cpp
*/

#include <Zap/Error.hpp>

/*
 * public
 */

/**
 * @brief Error::where
 * @details where the Error was raised
 * @return const char *
 */
const char *zap::exception::Error::where() const noexcept
{
    return _where.c_str();
}

/**
 * @brief Error::what
 * @details why the Error was raised
 * @return const char *
 */
const char *zap::exception::Error::what() const noexcept
{
    return _what.c_str();
}
