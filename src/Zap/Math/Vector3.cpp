/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Vector3.cpp
*/

#include <Zap/Math/Vector3.hpp>

#include <Zap/Math/Quaternion.hpp>

#include <cmath>

/**
* public
*/

template<typename T>
T math::Vector3<T>::length() const
{
    return static_cast<T>(std::sqrt(_x * _x + _y * _y + _z * _z));
}

template<typename T>
T math::Vector3<T>::max() const
{
    return std::max(std::max(_x, _y), _z);
}

template<typename T>
T math::Vector3<T>::dot(const Vector3<T> &other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

template<typename T>
math::Vector3<T> math::Vector3<T>::cross(const Vector3<T> &other) const
{
    return Vector3<T>(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::normalize()
{
    const T length = this->length();

    _x /= length;
    _y /= length;
    _z /= length;
    return *this;
}

template<typename T>
math::Vector3<T> math::Vector3<T>::normalized() const
{
    const T length = this->length();

    return Vector3<T>(_x / length, _y / length, _z / length);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::rotate(const Vector3<T> &axis, T angle) const
{
    const Vector3<T> norm_axis = axis.normalized();

    const T half_angle = angle * 0.5;
    const T half_sin = std::sin(half_angle);
    const T half_cos = std::cos(half_angle);

    const Quaternion q(norm_axis._x * half_sin, norm_axis._y * half_sin, norm_axis._z * half_sin, half_cos);

    /**
    * @details represent this vector as a pure quaternion
    */
    const Quaternion p(_x, _y, _z, 0.0f);

    /**
    * @details rotate: q * p * q⁻¹
    */
    const Quaternion rotated = q * p * q.inverse();

    return Vector3<T>(rotated._x, rotated._y, rotated._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::rotate(const Quaternion &rotation) const
{
    /**
    * @details represent this vector as a pure quaternion
    */
    const Quaternion p(_x, _y, _z, 0.0f);

    /**
    * @details rotate: v' = q * v * q⁻¹
    */
    const Quaternion rotated = rotation * p * rotation.inverse();

    return Vector3<T>(rotated._x, rotated._y, rotated._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::reflect(const Quaternion &q) const
{
    // NOTE: not so sure bc not the standard reflection formula
    // const Vector3<T> n = normal.normalized();
    // const f32 dot_product = this->dot(n);
    //
    // return *this - n * (2 * dot_product);

    const Quaternion p(_x, _y, _z, 0.0f);
    const Quaternion reflect = (q * p) * q;
    const Quaternion result = reflect.normalize();

    return Vector3<T>(result._x, result._y, result._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::lerp(const Vector3<T> &other, T t) const
{
    return ((other - *this) * t) + *this;
}

/**
* operator overloads
*/

template<typename T>
math::Vector3<T> math::Vector3<T>::operator+(const Vector3<T> &other) const
{
    return Vector3<T>(_x + other._x, _y + other._y, _z + other._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator-(const Vector3<T> &other) const
{
    return Vector3<T>(_x - other._x, _y - other._y, _z - other._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator*(const Vector3<T> &other) const
{
    return Vector3<T>(_x * other._x, _y * other._y, _z * other._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator/(const Vector3<T> &other) const
{
    return Vector3<T>(_x / other._x, _y / other._y, _z / other._z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator+(const T scalar) const
{
    return Vector3<T>(_x + scalar, _y + scalar, _z + scalar);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator-(const T scalar) const
{
    return Vector3<T>(_x - scalar, _y - scalar, _z - scalar);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator*(const T scalar) const
{
    return Vector3<T>(_x * scalar, _y * scalar, _z * scalar);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::operator/(const T scalar) const
{
    return Vector3<T>(_x / scalar, _y / scalar, _z / scalar);
}

template<typename T>
bool math::Vector3<T>::operator==(const Vector3<T> &other) const
{
    return _x == other._x && _y == other._y && _z == other._z;
}

template<typename T>
bool math::Vector3<T>::operator!=(const Vector3<T> &other) const
{
    return !(*this == other);
}

/**
* absolute <|> set <|> floor <|> ceil
*/

template<typename T>
math::Vector3<T> math::Vector3<T>::absolute() const
{
    return Vector3<T>(std::abs(_x), std::abs(_y), std::abs(_z));
}

template<typename T>
math::Vector3<T> math::Vector3<T>::set() const
{
    return Vector3<T>(_x, _y, _z);
}

template<typename T>
math::Vector3<T> math::Vector3<T>::floor() const
{
    return Vector3<T>(std::floor(_x), std::floor(_y), std::floor(_z));
}

template<typename T>
math::Vector3<T> math::Vector3<T>::ceil() const
{
    return Vector3<T>(std::ceil(_x), std::ceil(_y), std::ceil(_z));
}
