/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** InstanceBuffer.hpp
*/

#pragma once

#include "GLEngineTypes.hpp"

#include <glm/mat4x4.hpp>

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
