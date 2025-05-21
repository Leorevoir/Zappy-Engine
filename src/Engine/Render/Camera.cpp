#include "Camera.hpp"

// clang-format off
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <glm/ext/matrix_transform.hpp>
#if defined(__clang__)
    #pragma clang diagnostic push
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

/**
* public
*/

zap::Camera::Camera(const glm::vec3 &pos, const glm::vec3 &up, const zap::f32 yaw, const zap::f32 pitch) noexcept
{
    _movement_speed = SPEED;
    _mouse_sensitivity = SENSITIVITY;
    _zoom = ZOOM;
    _position = pos;
    _world_up = up;
    _yaw = yaw;
    _pitch = pitch;
    _update_camera_vectors();
}

void zap::Camera::keyPressed(const Direction direction, const f32 dt) noexcept
{
    const f32 velocity = _movement_speed * dt;

    switch (direction) {
        case FORWARD:
            _position += _front * velocity;
            break;
        case BACKWARD:
            _position -= _front * velocity;
            break;
        case LEFT:
            _position -= _right * velocity;
            break;
        case RIGHT:
            _position += _right * velocity;
            break;
        default:
            break;
    }
}

void zap::Camera::mouseMoved(const f32 xoffset, const f32 y, const GLboolean constraint_pitch) noexcept
{
    const f32 xoff = xoffset * _mouse_sensitivity;
    const f32 yoff = y * _mouse_sensitivity;

    _yaw += xoff;
    _pitch += yoff;

    if (constraint_pitch) {
        if (_pitch > 89.0f) {
            _pitch = 89.0f;
        }
        if (_pitch < -89.0f) {
            _pitch = -89.0f;
        }
    }
    _update_camera_vectors();
}

void zap::Camera::mouseScroll(const zap::f32 y) noexcept
{
    _zoom -= y;

    if (_zoom < 1.0f) {
        _zoom = 1.0f;
    }
    if (_zoom > 45.0f) {
        _zoom = 45.0f;
    }
}

glm::mat4 zap::Camera::getViewMatrix() const noexcept
{
    return glm::lookAt(_position, _position + _front, _up);
}

/**
* private
*/

void zap::Camera::_update_camera_vectors() noexcept
{
    // clang-format off
    const glm::vec3 front(
        std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)),
        std::sin(glm::radians(_pitch)),
        std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch))
    );
    // clang-format on

    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _world_up));
    _up = glm::normalize(glm::cross(_right, _front));
}
