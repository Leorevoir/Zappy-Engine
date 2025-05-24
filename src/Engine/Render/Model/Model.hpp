/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Model.hpp
*/

#pragma once

#include <Error.hpp>
#include <GLEngineTypes.hpp>

// clang-format off
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wsign-conversion"
    #pragma clang diagnostic ignored "-Warray-bounds"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-conversion"
    #pragma GCC diagnostic ignored "-Warray-bounds"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif
// clang-format on

#include <Engine/Render/Model/Mesh.hpp>
#include <Engine/Shader/Shader.hpp>

#include <vector>

namespace zap {

class Model final
{
    public:
        std::vector<Texture> _textures;
        std::vector<Mesh> _meshes;

        explicit Model(const std::string &path);

        void draw(Shader &shader);

    private:
        void _initialize(const std::string &path);
        void _traverse_node_hierarchy(const aiNode *node, const aiScene *scene);
        [[nodiscard]] const Mesh _convert_mesh_data(const aiMesh *mesh, const aiScene *scene) noexcept;
        [[nodiscard]] const std::vector<Texture> _load_material_textures(const aiMaterial *mat, const aiTextureType type, const std::string type_name);

        std::string _directory;
};

}// namespace zap
