/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Types.hpp
*/

#pragma once

#include <Zap/Math/Vector2.hpp>
#include <Zap/Math/Vector3.hpp>

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using f32 = float;
using f64 = double;

using Vec2f = math::Vector2<f64>;
using Vec2i = math::Vector2<i32>;
using Vec2u = math::Vector2<u32>;

using Vec3f = math::Vector3<f64>;
using Vec3i = math::Vector3<i32>;
using Vec3u = math::Vector3<u32>;

using VoidPtr = void *;
