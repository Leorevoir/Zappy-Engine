/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Vector3.hpp
*/

#pragma once

#include <ostream>
#include <type_traits>

namespace math {

struct Quaternion;

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
     * no explicit because we want to instanciate like this example: {1, 2, 3}
     */
    template<typename T1, typename T2, typename T3, typename = std::enable_if_t<
    std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2> && std::is_arithmetic_v<T3>>>
    Vector3(const T1 x, const T2 y, const T3 z) : _x(static_cast<T>(x)), _y(static_cast<T>(y)), _z(static_cast<T>(z))
    {
        /* __ctor__ */
    }

    constexpr explicit Vector3() = default;

    Vector3<T> normalize();
    [[nodiscard]] Vector3<T> normalized() const;

    [[nodiscard]] T length() const;
    [[nodiscard]] T max() const;
    [[nodiscard]] T dot(const Vector3<T> &other) const;
    [[nodiscard]] Vector3<T> cross(const Vector3<T> &other) const;

    [[nodiscard]] Vector3<T> rotate(const Vector3<T> &axis, float angle) const;
    [[nodiscard]] Vector3<T> rotate(const Quaternion &rotation) const;
    [[nodiscard]] Vector3<T> reflect(const Quaternion &quaternion) const;
    [[nodiscard]] Vector3<T> lerp(const Vector3<T> &other, T t) const;

    [[nodiscard]] Vector3<T> operator+(const Vector3<T> &other) const;
    [[nodiscard]] Vector3<T> operator-(const Vector3<T> &other) const;
    [[nodiscard]] Vector3<T> operator*(const Vector3<T> &other) const;
    [[nodiscard]] Vector3<T> operator/(const Vector3<T> &other) const;

    [[nodiscard]] Vector3<T> operator+(const T scalar) const;
    [[nodiscard]] Vector3<T> operator-(const T scalar) const;
    [[nodiscard]] Vector3<T> operator*(const T scalar) const;
    [[nodiscard]] Vector3<T> operator/(const T scalar) const;

    [[nodiscard]] bool operator==(const Vector3<T> &other) const;
    [[nodiscard]] bool operator!=(const Vector3<T> &other) const;

    [[nodiscard]] Vector3<T> absolute() const;
    [[nodiscard]] Vector3<T> set() const;
    [[nodiscard]] Vector3<T> floor() const;
    [[nodiscard]] Vector3<T> ceil() const;

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
static inline std::ostream &operator<<(std::ostream &os, const Vector3<T> &self)
{
    os << "{" << self._x << ", " << self._y << ", " << self._z << "}";
    return os;
}

template class Vector3<float>;
template class Vector3<double>;

}// namespace math
