/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** ShaderBase.cpp
*/

#include "ShaderBase.hpp"

/**
* public
*/

void zap::abstract::ShaderBase::setBool(const char *RESTRICT name, const bool value) const noexcept
{
    glUniform1i(glGetUniformLocation(_program, name), static_cast<i32>(value));
}

void zap::abstract::ShaderBase::setInt(const char *RESTRICT name, const i32 value) const noexcept
{
    glUniform1i(glGetUniformLocation(_program, name), value);
}

void zap::abstract::ShaderBase::setFloat(const char *RESTRICT name, const f32 value) const noexcept
{
    glUniform1f(glGetUniformLocation(_program, name), value);
}

void zap::abstract::ShaderBase::setVec2(const char *RESTRICT name, const glm::vec2 &value) const noexcept
{
    glUniform2fv(glGetUniformLocation(_program, name), 1, &value[0]);
}

void zap::abstract::ShaderBase::setVec3(const char *RESTRICT name, const glm::vec3 &value) const noexcept
{
    glUniform3fv(glGetUniformLocation(_program, name), 1, &value[0]);
}

void zap::abstract::ShaderBase::setVec4(const char *RESTRICT name, const glm::vec4 &value) const noexcept
{
    glUniform4fv(glGetUniformLocation(_program, name), 1, &value[0]);
}

void zap::abstract::ShaderBase::setMat2(const char *RESTRICT name, const glm::mat2 &value) const noexcept
{
    glUniformMatrix2fv(glGetUniformLocation(_program, name), 1, GL_FALSE, &value[0][0]);
}

void zap::abstract::ShaderBase::setMat3(const char *RESTRICT name, const glm::mat3 &value) const noexcept
{
    glUniformMatrix3fv(glGetUniformLocation(_program, name), 1, GL_FALSE, &value[0][0]);
}

void zap::abstract::ShaderBase::setMat4(const char *RESTRICT name, const glm::mat4 &value) const noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, GL_FALSE, &value[0][0]);
}

zap::u32 zap::abstract::ShaderBase::getProgram() const noexcept
{
    return _program;
}
