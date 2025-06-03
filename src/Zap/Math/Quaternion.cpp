/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Quaternion.cpp
*/

#include <Zap/Macro.hpp>
#include <Zap/Math/Quaternion.hpp>

#include <cmath>

/**
* public
*/

math::Quaternion::Quaternion(const f64 x, const f64 y, const f64 z, const f64 w) : _x(x), _y(y), _z(z), _w(w)
{
    /* __ctor__ */
}

math::Quaternion::Quaternion(const Vec3f &axis, const f64 angle)
{
    _x = axis._x;
    _y = axis._y;
    _z = axis._z;
    _w = angle;
}

f32 math::Quaternion::length() const
{
    return static_cast<f32>(std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w));
}

f32 math::Quaternion::dot(const Quaternion &other) const
{
    return static_cast<f32>(_x * other._x + _y * other._y + _z * other._z + _w * other._w);
}

math::Quaternion math::Quaternion::inverse() const
{
    if (std::fabs(this->length()) < ZAP_EPSILON_F32) {
        return *this;
    }
    return this->conjugate().normalize();
}

math::Quaternion math::Quaternion::conjugate() const
{
    return Quaternion(-_x, -_y, -_z, _w);
}

math::Quaternion math::Quaternion::normalize() const
{
    const f64 len = static_cast<f64>(this->length());

    if (std::fabs(len) < ZAP_EPSILON) {
        return *this;
    }
    return Quaternion(_x / len, _y / len, _z / len, _w / len);
}

Vec3f math::Quaternion::forward() const
{
    return Vec3f(0.0, 0.0, 1.0).rotate(*this);
}

Vec3f math::Quaternion::up() const
{
    return Vec3f(0.0, 1.0, 0.0).rotate(*this);
}

Vec3f math::Quaternion::right() const
{
    return Vec3f(1.0, 0.0, 0.0).rotate(*this);
}

Vec3f math::Quaternion::backward() const
{
    return Vec3f(0.0, 0.0, -1.0).rotate(*this);
}

Vec3f math::Quaternion::left() const
{
    return Vec3f(1.0, 0.0, 0.0).rotate(*this);
}

/**
* operator overloads
*/
// clang-format off

math::Quaternion math::Quaternion::operator*(const Quaternion &other) const
{
    return Quaternion(
        _w * other._x + _x * other._w + _y * other._z - _z * other._y,
        _w * other._y - _x * other._z + _y * other._w + _z * other._x,
        _w * other._z + _x * other._y - _y * other._x + _z * other._w,
        _w * other._w - _x * other._x - _y * other._y - _z * other._z);
}

math::Quaternion math::Quaternion::operator*(const Vec3f &vector) const
{
    // NOTE: idk maybe this is not the best way to do it
    // Quaternion q(vector._x, vector._y, vector._z, 0.0);
    //
    // return (*this * q) * this->inverse();
    return Quaternion(
        -_x *vector._x - _y *vector._y - _z *vector._z,
        _w *vector._x + _y *vector._z - _z *vector._y,
        _w *vector._y + _z *vector._x - _x *vector._z,
        _w *vector._z + _x *vector._y - _y *vector._x
    );
}

math::Quaternion math::Quaternion::operator+(const Quaternion &other) const
{
    return Quaternion(_x + other._x, _y + other._y, _z + other._z, _w + other._w);
}

math::Quaternion math::Quaternion::operator-(const Quaternion &other) const
{
    return Quaternion(_x - other._x, _y - other._y, _z - other._z, _w - other._w);
}

bool math::Quaternion::operator==(const Quaternion &other) const
{
    return std::fabs(_x - other._x) < ZAP_EPSILON &&
           std::fabs(_y - other._y) < ZAP_EPSILON &&
           std::fabs(_z - other._z) < ZAP_EPSILON &&
           std::fabs(_w - other._w) < ZAP_EPSILON;
}

bool math::Quaternion::operator!=(const Quaternion &other) const
{
    return !(*this == other);
}

// clang-format on
