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
    std::unique_ptr<Bitmap> bitmap = std::make_unique<Bitmap>(path);

    u32 out_id;

    /** @brief generate a texture ID and bind it */
    glGenTextures(1, &out_id);
    glBindTexture(GL_TEXTURE_2D, out_id);

    /** @brief set texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /** @brief set texture filtering */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /** @brief load the texture data */
    const i32 format = bitmap->is_alpha() ? GL_RGBA : GL_RGB;
    const Vec2i size = bitmap->get_size();

    glTexImage2D(GL_TEXTURE_2D, 0, format, size._x, size._y, 0, static_cast<GLenum>(format), GL_UNSIGNED_BYTE, bitmap->get_pixels().data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

    /** @brief unbind the texture */
    glBindTexture(GL_TEXTURE_2D, 0);

    return std::make_shared<Texture>(out_id, path);
}
