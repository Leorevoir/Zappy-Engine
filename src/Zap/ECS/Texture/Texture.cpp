/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Texture.cpp
*/

#include <Zap/ECS/Texture/Bitmap.hpp>
#include <Zap/ECS/Texture/Texture.hpp>

#include <Zap/Logger.hpp>

// clang-format off
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
// clang-format on

#include <memory>

/**
* public
*/

zap::ecs::Texture::Texture(u32 id, const std::string &name) : _id(id), _name(name)
{
    /* __ctor__ */
}

zap::ecs::Texture::~Texture()
{
    glDeleteTextures(1, &this->_id);
}

void zap::ecs::Texture::bind(i32 sampler_slot) const
{
    if (sampler_slot < 0 || sampler_slot >= 32) {
        logger::debug("invalid sampler slot, must be between 0 and 31!");
        return;
    }
    glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(sampler_slot));
    glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(this->_id));
}

/**
* static
*/

zap::ecs::Texture::TexturePtr zap::ecs::Texture::load(const std::string &path)
{
    (void) path;
    return nullptr;
    // auto bitmap = std::make_unique<zap::Bitmap>(path);
}
