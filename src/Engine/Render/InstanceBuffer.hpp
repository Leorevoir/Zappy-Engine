/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** InstanceBuffer.hpp
*/

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

#include <glm/mat4x4.hpp>

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

#include <vector>

namespace zap {

class InstanceBuffer final
{
    public:
        explicit InstanceBuffer(const std::vector<glm::mat4> &transforms) noexcept;
        ~InstanceBuffer();

        void bindToVAO(u32 vao) const noexcept;

    private:
        u32 _bufferID;
};
}// namespace zap
