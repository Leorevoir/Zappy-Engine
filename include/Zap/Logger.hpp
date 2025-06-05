/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Logger.hpp
*/

#pragma once

#include <Zap/Error.hpp>

#ifdef DEBUG
    #include <iostream>
    #include <sstream>
#endif

namespace zap::logger {

constexpr const char *GRAY = "\033[38;5;8m";
constexpr const char *RED_BOLD = "\033[1;31m";
constexpr const char *YELLOW = "\033[1;33m";
constexpr const char *GREEN = "\033[1;32m";
constexpr const char *BLUE = "\033[1;34m";
constexpr const char *RESET = "\033[0m";

void error(const zap::exception::Error &e);

template<typename... Args>
void debug(__attribute_maybe_unused__ Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << BLUE << "[DEBUG] " << RESET << oss.str() << std::endl;
#endif
}

template<typename... Args>
void task_start(Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << YELLOW << "[TASK START] " << RESET << oss.str() << std::endl;
#endif
}

template<typename... Args>
void task_done(Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << GREEN << "[TASK DONE] " << RESET << oss.str() << std::endl;
#endif
}

}// namespace zap::logger
