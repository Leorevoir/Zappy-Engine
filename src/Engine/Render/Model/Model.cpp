/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Model.cpp
*/

#include <Engine/Render/Model/Model.hpp>

#include <Error.hpp>

/**
* public
*/

zap::Model::Model(const std::string &path)
{
    _initialize(path);
}

/**
* @brief Mode::draw
* @details draws the model using the given shader.
* @param shader the shader to use for drawing.
* @return void
*/
void zap::Model::draw(Shader &shader)
{
    for (u32 i = 0; i < _meshes.size(); ++i) {
        _meshes[i].draw(shader);
    }
}

/**
* private
*/

/**
* @brief Model::_initialize
* @details loads the model from the given path and initializes the meshes and textures.
* @param path the path to the model file.
* @return void
*/
void zap::Model::_initialize(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw exception::Error("zap::Model::_initialize", "Error loading model ", path, " Assimp log: ", importer.GetErrorString());
    }

    _directory = path.substr(0, path.find_last_of('/'));
    _traverse_node_hierarchy(scene->mRootNode, scene);
}

/**
* @brief Model::_traverse_node_hierarchy
* @details traverses the node hierarchy of the model and loads the meshes.
* @param node the current node.
* @param scene the scene containing the model data.
* @return void
*/
void zap::Model::_traverse_node_hierarchy(const aiNode *node, const aiScene *scene)
{
    for (u32 i = 0; i < node->mNumMeshes; ++i) {
        const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        _meshes.push_back(_convert_mesh_data(mesh, scene));
    }

    for (u32 i = 0; i < node->mNumChildren; ++i) {
        _traverse_node_hierarchy(node->mChildren[i], scene);
    }
}

/**
* @brief Model::_create_vertex
* @details creates a vertex from the given mesh and index.
* @param mesh the mesh containing the vertex data.
* @param i the index of the vertex in the mesh.
* @return the created vertex.
*/
static const zap::Vertex _create_vertex(const aiMesh *mesh, const zap::u32 i) noexcept
{
    zap::Vertex vertex;

    vertex._position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
    if (mesh->HasNormals()) {
        vertex._normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
    }
    if (mesh->mTextureCoords[0]) {
        vertex._coords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        vertex._tangent = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
        vertex._bitangent = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
        return vertex;
    }
    vertex._coords = {0.0f, 0.0f};
    return vertex;
}

/**
* @brief Model::_retrieve_indices
* @details retrieves the indices from the given mesh and stores them in the provided vector.
* @param mesh the mesh containing the index data.
* @param indices the vector to store the indices.
* @return void
*/
static void _retrieve_indices(const aiMesh *mesh, std::vector<zap::u32> &indices) noexcept
{
    for (zap::u32 i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace face = mesh->mFaces[i];

        for (zap::u32 j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

/**
* @brief Mode::_convert_mesh_data
* @details converts the mesh data from Assimp format to the internal format used by the engine.
* @param mesh the mesh to convert.
* @param scene the scene containing the model data.
* @return the converted mesh.
*/
const zap::Mesh zap::Model::_convert_mesh_data(const aiMesh *mesh, const aiScene *scene) noexcept
{
    std::vector<Texture> textures;
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    for (u32 i = 0; i < mesh->mNumVertices; ++i) {
        vertices.push_back(_create_vertex(mesh, i));
    }

    _retrieve_indices(mesh, indices);

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    const auto _lambda_load = [&](const aiTextureType type, const std::string &type_name) {
        const std::vector<Texture> maps = _load_material_textures(material, type, type_name);

        textures.insert(textures.end(), maps.begin(), maps.end());
    };

    _lambda_load(aiTextureType_DIFFUSE, "texture_diffuse");
    _lambda_load(aiTextureType_SPECULAR, "texture_specular");
    _lambda_load(aiTextureType_HEIGHT, "texture_normal");
    _lambda_load(aiTextureType_AMBIENT, "texture_height");
    return Mesh(vertices, indices, textures);
}

/**
* @brief Model::_create_texture_from_file
* @details creates a texture from the given file path and directory.
* @param path the path to the texture file.
* @param directory the directory containing the texture file.
* @return the created texture ID.
*/
static zap::u32 _create_texture_from_file(const char *RESTRICT path, const std::string &directory)
{
    const std::string filename = directory + '/' + std::string(path);

    zap::u32 texture_id;
    glGenTextures(1, &texture_id);

    zap::i32 w, h, n;
    zap::u8 *data = stbi_load(filename.c_str(), &w, &h, &n, 0);

    if (!data) {
        stbi_image_free(data);
        throw zap::exception::Error("_create_texture_from_file", "Failed to load texture at path: ", filename);
    }

    GLenum format;

    switch (n) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
            break;
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return texture_id;
}

/**
* @brief Model::_load_material_textures
* @details loads the textures from the material and stores them in the provided vector.
* @param mat the material containing the texture data.
* @param type the type of texture to load.
* @param type_name the name of the texture type.
* @return the loaded textures.
*/
const std::vector<zap::Texture> zap::Model::_load_material_textures(const aiMaterial *mat, const aiTextureType type, const std::string type_name)
{
    std::vector<Texture> textures;

    for (u32 i = 0; i < mat->GetTextureCount(type); i++) {

        aiString str;
        bool skip = false;

        mat->GetTexture(type, i, &str);

        for (u32 j = 0; j < _textures.size(); j++) {
            if (std::strcmp(_textures[j]._path.data(), str.C_Str()) == 0) {
                textures.push_back(_textures[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture texture;

            texture._id = _create_texture_from_file(str.C_Str(), _directory);
            texture._type = type_name;
            texture._path = str.C_Str();
            textures.push_back(texture);
            _textures.push_back(texture);
        }
    }
    return textures;
}
