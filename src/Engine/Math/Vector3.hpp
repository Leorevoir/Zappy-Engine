/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Vector3.hpp
*/

#pragma once

#include <ostream>
#include <type_traits>

namespace math {

// clang-format off
/**
 * @brief Vector3
 * @details Define a Vector of two elements of type T {x, y}
 */
template<typename T>
struct Vector3 {
    T _x;
    T _y;
    T _z;

    /**
     * @brief __ctor__
     * @details construct a Vector3<T> with any arithmetic types (T1, T2, T3)
     */
    template<typename T1, typename T2, typename T3, typename = std::enable_if_t<
    std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2> && std::is_arithmetic_v<T3>>>
    explicit Vector3(const T1 x, const T2 y, const T3 z) : _x(static_cast<T>(x)), _y(static_cast<T>(y)), _z(static_cast<T>(z))
    {
        /* __ctor__ */
    }

    constexpr explicit Vector3() = default;
};
// clang-format on
/**
 * @brief operator `<<` (iostream | ostream)
 * @details this operator is declared outside Vector3 to avoid `friend` keyword.
 * it allows you to std::cout << "vector: " << my_vector3 << std::endl;
 * the vector is shown as: `{x, y}`
 * @return the result (vector)
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &self);

}// namespace math
