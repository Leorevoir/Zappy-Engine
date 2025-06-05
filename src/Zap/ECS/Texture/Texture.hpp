/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Texture.hpp
*/

#pragma once

#include <Zap/Types.hpp>

#include <memory>
#include <string>

namespace zap::ecs {

//TODO: make it a composite interface and create 2D texture 3D texture
class Texture
{
    public:
        explicit Texture(u32 id, const std::string &name);
        ~Texture();

        void bind(i32 sampler_slot) const;

        using TexturePtr = std::shared_ptr<Texture>;

        static TexturePtr load(const std::string &path);

    private:
        u32 _id = 0;
        std::string _name;
};

}// namespace zap::ecs
