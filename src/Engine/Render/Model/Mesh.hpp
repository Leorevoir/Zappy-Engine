/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Mesh.hpp
*/

#pragma once

#include <Engine/Render/Model/Texture.hpp>
#include <Engine/Render/Model/Vertex.hpp>

#include <Engine/Shader/Shader.hpp>

#include <vector>

namespace zap {
class Mesh final
{
    public:
        std::vector<Vertex> _vertices;
        std::vector<u32> _indices;
        std::vector<Texture> _textures;
        u32 _VAO;

        explicit Mesh(const std::vector<Vertex> vertices, const std::vector<u32> indices, const std::vector<Texture> textures);

        void draw(Shader &shader);

    private:
        void _initialize();

        u32 _VBO, _EBO;
};
}// namespace zap
