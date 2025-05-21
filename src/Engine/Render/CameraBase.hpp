#pragma once

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
    #pragma clang diagnostic push
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

namespace zap::abstract {

class CameraBase
{
    public:
        virtual ~CameraBase() = default;

        enum Direction { FORWARD, BACKWARD, LEFT, RIGHT };

    protected:
        static constexpr f32 YAW = -90.0f;
        static constexpr f32 PITCH = 0.0f;
        static constexpr f32 SPEED = 2.5f;
        static constexpr f32 SENSITIVITY = 0.1f;
        static constexpr f32 ZOOM = 45.0f;

        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _front;
        glm::vec3 _world_up;
        glm::vec3 _position;

        f32 _yaw;
        f32 _zoom;
        f32 _pitch;
        f32 _movement_speed;
        f32 _mouse_sensitivity;
};

}// namespace zap::abstract
