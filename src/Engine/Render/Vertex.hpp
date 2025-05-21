#pragma once

#define ZAP_MAX_BONE_INFLUENCE 4

#include "GLEngineTypes.hpp"

#include <glm/glm.hpp>

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
