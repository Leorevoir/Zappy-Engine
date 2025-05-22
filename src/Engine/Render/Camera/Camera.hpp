#pragma once

#include "CameraBase.hpp"

namespace zap {

// clang-format off

class Camera final : public abstract::CameraBase
{
    public:
        explicit Camera(const glm::vec3 &pos    =   glm::vec3(0.0f, 0.0f, 0.0f),
                        const glm::vec3 &up     =   glm::vec3(0.0f, 1.0f, 0.0f),
                        const zap::f32  yaw     =   YAW,
                        const zap::f32  pitch   =   PITCH) noexcept;

        ~Camera() override = default;

        void keyPressed(const Direction direction, const f32 dt) noexcept override;
        void mouseMoved(const f32 x, const f32 y, const GLboolean constrainPitch) noexcept override;
        void mouseScroll(const f32 y) noexcept override;

        [[nodiscard]] glm::mat4 getViewMatrix() const noexcept;

    private:
        void _update_camera_vectors() noexcept;
};

// clang-format on
}// namespace zap
