#include "Model.hpp"

#include "Error.hpp"

/**
* public
*/

zap::Model::Model(const std::string &path)
{
    _initialize(path);
}

void zap::Model::draw(Shader &shader)
{
    for (u32 i = 0; i < _meshes.size(); ++i) {
        _meshes[i].draw(shader);
    }
}

/**
* private
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

void zap::Model::_traverse_node_hierarchy(aiNode *node, const aiScene *scene)
{
    for (u32 i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        _meshes.push_back(_convert_mesh_data(mesh, scene));
    }

    for (u32 i = 0; i < node->mNumChildren; ++i) {
        _traverse_node_hierarchy(node->mChildren[i], scene);
    }
}

zap::Mesh zap::Model::_convert_mesh_data(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Texture> textures;
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    // walk through each of the mesh's vertices
    for (u32 i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        glm::vec3
            vector;// we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex._position = vector;
        // normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex._normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0])// does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex._coords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex._tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex._bitangent = vector;
        } else
            vertex._coords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (u32 i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (u32 j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = _load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = _load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = _load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = _load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

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
            break;
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return texture_id;
}

std::vector<zap::Texture> zap::Model::_load_material_textures(aiMaterial *mat, const aiTextureType type, const std::string type_name)
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
