/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Vertex.hpp
*/

#pragma once

#define ZAP_MAX_BONE_INFLUENCE 4

#include "GLEngineTypes.hpp"

// clang-format off
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#include <glm/glm.hpp>

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

namespace zap {

struct Vertex {
        glm::vec3 _position;
        glm::vec3 _normal;
        glm::vec2 _coords;
        glm::vec3 _tangent;
        glm::vec3 _bitangent;
        zap::i32 _bone_ids[ZAP_MAX_BONE_INFLUENCE];
        zap::f32 _weights[ZAP_MAX_BONE_INFLUENCE];
};

}// namespace zap
