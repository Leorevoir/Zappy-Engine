/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Quaternion.hpp
*/

#pragma once

#include <Zap/Types.hpp>

namespace math {

struct Quaternion {

        f64 _x;
        f64 _y;
        f64 _z;
        f64 _w;

        explicit Quaternion(const f64 x, const f64 y, const f64 z, const f64 w);
        explicit Quaternion(const Vec3f &axis, const f64 angle);
        //TODO: rotation matrix

        [[nodiscard]] f32 length() const;
        [[nodiscard]] f32 dot(const Quaternion &other) const;
        [[nodiscard]] Quaternion inverse() const;
        [[nodiscard]] Quaternion conjugate() const;
        [[nodiscard]] Quaternion normalize() const;

        [[nodiscard]] Vec3f forward() const;
        [[nodiscard]] Vec3f up() const;
        [[nodiscard]] Vec3f right() const;
        [[nodiscard]] Vec3f backward() const;
        [[nodiscard]] Vec3f left() const;

        [[nodiscard]] Quaternion operator*(const Quaternion &other) const;
        [[nodiscard]] Quaternion operator*(const Vec3f &vector) const;
        [[nodiscard]] Quaternion operator+(const Quaternion &other) const;
        [[nodiscard]] Quaternion operator-(const Quaternion &other) const;
        [[nodiscard]] bool operator==(const Quaternion &other) const;
        [[nodiscard]] bool operator!=(const Quaternion &other) const;
};

}// namespace math
