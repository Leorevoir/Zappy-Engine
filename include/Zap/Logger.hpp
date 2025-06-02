/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Logger.hpp
*/

#pragma once

#include <Zap/Error.hpp>

#define DEBUG

#ifdef DEBUG
    #include <iostream>
#else
#endif

namespace zap::logger {

constexpr const char *GRAY = "\033[38;5;8m";
constexpr const char *RED_BOLD = "\033[1;31m";
constexpr const char *YELLOW = "\033[1;33m";
constexpr const char *RESET = "\033[0m";

void error(const zap::exception::Error &e);

/**
 * @brief logger::debug
 * @details log clearly all the debug logs if DEBUG pre-processor is defined.
 * takes an <Args> va_list
 *
 * INFO:
 *  logger::debug("hey this file: ", filename, " is loaded !");
 *
 * @return void
 */
template<typename... Args>
void debug(__attribute_maybe_unused__ Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << YELLOW << "[DEBUG] " << RESET << oss.str() << std::endl;
#else
#endif
}

}// namespace zap::logger
