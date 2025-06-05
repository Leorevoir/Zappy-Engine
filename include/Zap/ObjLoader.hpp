/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** ObjLoader.hpp
*/

#pragma once

#include <Zap/ECS/Model/Model.hpp>
#include <Zap/Macro.hpp>
#include <Zap/Types.hpp>

namespace zap::obj {

struct Vertex {
        Vec3f _position;
        i32 _normal_index = ZAP_INVALID_INDEX;
        i32 _texture_index = ZAP_INVALID_INDEX;
        u64 _index;
        f32 _length;

        explicit inline Vertex(const Vec3f &position, u64 index)
        {
            _index = index;
            _length = static_cast<f32>(position.length());
        }

        inline bool is_valid() const
        {
            return _normal_index != ZAP_INVALID_INDEX && _texture_index != ZAP_INVALID_INDEX;
        }

        inline bool operator==(const Vertex &other) const
        {
            return _texture_index == other._texture_index && _normal_index == other._normal_index;
        }
};

ecs::ModelData load(const std::string &filename);

}// namespace zap::obj
