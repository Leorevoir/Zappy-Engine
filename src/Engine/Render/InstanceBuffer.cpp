/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** InstanceBuffer.cpp
*/

#include "InstanceBuffer.hpp"

/**
* public
*/

zap::InstanceBuffer::InstanceBuffer(const std::vector<glm::mat4> &transforms) noexcept
{
    glGenBuffers(1, &_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), transforms.data(), GL_STATIC_DRAW);
}

zap::InstanceBuffer::~InstanceBuffer()
{
    glDeleteBuffers(1, &_bufferID);
}

void zap::InstanceBuffer::bindToVAO(zap::u32 vao) const noexcept
{
    glBindVertexArray(vao);

    for (u32 i = 0; i < 4; ++i) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4) * i));
        glVertexAttribDivisor(3 + i, 1);
    }

    glBindVertexArray(0);
}
