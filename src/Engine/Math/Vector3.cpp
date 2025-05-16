/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Vector3.cpp
*/

#include "Vector3.hpp"

/**
 * @brief operator `<<` (iostream | ostream)
 * @details this operator is declared outside Vector3 to avoid `friend` keyword.
 * it allows you to std::cout << "vector: " << my_vector3 << std::endl;
 * the vector is shown as: `{x, y, z}`
 * @return the result (vector)
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const math::Vector3<T> &self)
{
    os << "{" << self._x << ", " << self._y << ", " << self._z << "}";
    return os;
}
