/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Model.cpp
*/

#include <Zap/ECS/Model/Model.hpp>
#include <Zap/ObjLoader.hpp>

// clang-format off
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// clang-format on

/**
* public
*/

zap::ecs::Model::Model(u32 vao_id, const std::vector<u32> &vbos, u32 vertex_count, u32 num_attrib_arrays)
    : _vao(vao_id), _vertex_count(vertex_count), _vbos(vbos), _num_attrib_arrays(num_attrib_arrays)
{
    /* __ctor__ */
}

zap::ecs::Model::~Model()
{
    glDeleteVertexArrays(1, &_vao);
    for (size_t i = 0; i < _vbos.size(); ++i) {
        glDeleteBuffers(1, &_vbos[i]);
    }
}

void zap::ecs::Model::bind() const
{
    glBindVertexArray(_vao);
    for (u32 i = 0; i < _num_attrib_arrays; ++i) {
        glEnableVertexAttribArray(i);
    }
}

void zap::ecs::Model::unbind() const
{
    for (u32 i = 0; i < _num_attrib_arrays; ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

void zap::ecs::Model::draw() const
{
    bind();

    VoidPtr offset = nullptr;

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_vertex_count), GL_UNSIGNED_INT, offset);
    unbind();
}

/**
 * static
 */

zap::ecs::Model::ModelPtr zap::ecs::Model::load(const std::string &file_path)
{
    return load(obj::load(file_path));
}

static u32 _create_vao()
{
    u32 vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

static u32 _bind_indicies_buffer(const std::vector<u32> &indices)
{
    u32 vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(u32)), indices.data(), GL_STATIC_DRAW);
    return vbo;
}

static u32 _store_data_in_attrib_list(u32 attrib_num, GLsizei coordinate_size, const std::vector<f32> &data)
{
    u32 vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(data.size() * sizeof(f32)), data.data(), GL_STATIC_DRAW);

    VoidPtr offset = nullptr;

    glVertexAttribPointer(attrib_num, coordinate_size, GL_FLOAT, GL_FALSE, 0, offset);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

static inline void _unbind_vao()
{
    glBindVertexArray(0);
}

zap::ecs::Model::ModelPtr zap::ecs::Model::load(const ModelData &data)
{
    u32 vao = _create_vao();
    std::vector<u32> vbos;

    vbos.push_back(_bind_indicies_buffer(data._indices));
    vbos.push_back(_store_data_in_attrib_list(0, 3, data._vertices));
    vbos.push_back(_store_data_in_attrib_list(1, 2, data._tex_coords));
    vbos.push_back(_store_data_in_attrib_list(2, 3, data._normals));
    _unbind_vao();

    const u32 num_attrib_arrays = static_cast<u32>(vbos.size() - 1);

    return std::make_shared<Model>(vao, vbos, static_cast<u32>(data._indices.size()), num_attrib_arrays);
}

/**
* private
*/
