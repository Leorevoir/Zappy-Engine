/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.hpp
*/

#pragma once

#include "Engine/Render/Mesh.hpp"
#include "Engine/Render/Texture.hpp"
#include "Engine/Shader/Shader.hpp"
#include "GLEngineTypes.hpp"
#include "NonCopyable.hpp"

#include <memory>

namespace zap {

using ShaderPtr = std::unique_ptr<Shader>;
using MeshPtr = std::unique_ptr<Mesh>;
using TexturePtr = std::unique_ptr<Texture>;

/**
* @class Renderer
* @brief base renderer class, used to render everything you see
* @pattern singleton
*/
class Renderer : public abstract::NonCopyable
{
    public:
        static void initialize(WindowPtr window);
        static void render() noexcept;
        static void shutdown() noexcept;

    private:
        static WindowPtr _window;
        static ShaderPtr _shader;
        static MeshPtr _mesh;
        static TexturePtr _texture;

        static u32 VBO;
        static u32 VAO;
        static u32 EBO;
};
}// namespace zap
