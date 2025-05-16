/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Vector2.cpp
*/

#include "Vector2.hpp"

/**
 * @brief operator `<<` (iostream | ostream)
 * @details this operator is declared outside Vector2 to avoid `friend` keyword.
 * it allows you to std::cout << "vector: " << my_vector2 << std::endl;
 * the vector is shown as: `{x, y}`
 * @return the result (vector)
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const math::Vector2<T> &self)
{
    os << "{" << self._x << ", " << self._y << "}";
    return os;
}
