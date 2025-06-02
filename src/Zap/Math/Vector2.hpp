/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Vector2.hpp
*/

#pragma once

#include <ostream>
#include <type_traits>

namespace math {

// clang-format off
/**
 * @brief Vector2
 * @details Define a Vector of two elements of type T {x, y}
 */
template<typename T>
struct Vector2 {
    T _x;
    T _y;

    /**
     * @brief __ctor__
     * @details construct a Vector2<T> with any arithmetic types (T1, T2)
     * no explicit because we want to instanciate like this example: {1780, 720}
     */
    template<typename T1, typename T2, typename = std::enable_if_t<
        std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>>>
    Vector2(const T1 x, const T2 y) : _x(static_cast<T>(x)), _y(static_cast<T>(y))
    {
        /* __ctor__ */
    }

    constexpr explicit Vector2() = default;
};
// clang-format on
/**
 * @brief operator `<<` (iostream | ostream)
 * @details this operator is declared outside Vector2 to avoid `friend` keyword.
 * it allows you to std::cout << "vector: " << my_vector2 << std::endl;
 * the vector is shown as: `{x, y}`
 * @return the result (vector)
 */
template<typename T>
static inline std::ostream &operator<<(std::ostream &os, const Vector2<T> &self)
{
    os << "{" << self._x << ", " << self._y << "}";
    return os;
}

}// namespace math
