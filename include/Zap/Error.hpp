/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Error.hpp
*/

#pragma once

#include <exception>
#include <sstream>
#include <string>
#include <utility>

/**
 * @brief generic Error class
 * @details throw exception::Error("zap::Core", "failed to open ", <path>, " because: ", dlerror());
 * @return void
 */
namespace zap::exception {
class Error final : public std::exception
{
    public:
        /**
         * @brief Error constructor template
         * @details takes (what) (where) and (...) it works like va_list
         * @return Error
         */
        template<typename... Args>
        constexpr explicit Error(std::string where, Args &&...args) : _where(std::move(where)), _what(concatStrings(std::forward<Args>(args)...))
        {
            /* empty */
        }

        [[nodiscard]] const char *what() const noexcept override;
        [[nodiscard]] const char *where() const noexcept;

    private:
        const std::string _where;
        const std::string _what;

        /**
         * @brief Error::concatStrings
         * @details concat strings in va_list ...
         * @return std::string
         */
        template<typename... Args>
        static std::string concatStrings(Args &&...args)
        {
            std::ostringstream oss;

            (oss << ... << args);
            return oss.str();
        }
};
}// namespace zap::exception
