#include "Mesh.hpp"

#include <glad/gl.h>

/**
* public
*/

zap::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, std::vector<Texture> textures)
{
    _vertices = vertices;
    _indices = indices;
    _textures = textures;

    _initialize();
}

void zap::Mesh::draw(zap::Shader &shader)
{
    u32 diffuse = 1;
    u32 specular = 1;
    u32 normal = 1;
    u32 height = 1;

    for (u32 i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        const std::string name = _textures[i]._type;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuse++);
        } else if (name == "texture_specular") {
            number = std::to_string(specular++);
        } else if (name == "texture_normal") {
            number = std::to_string(normal++);
        } else if (name == "texture_height") {
            number = std::to_string(height++);
        }

        glUniform1i(glGetUniformLocation(shader.getProgram(), (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]._id);
    }

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<u32>(_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

/**
* private
*/

void zap::Mesh::_initialize()
{
    glGenVertexArrays(1, &_VAO);

    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, _normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, _coords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, _tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, _bitangent));

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void *) offsetof(Vertex, _bone_ids));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, _weights));
    glBindVertexArray(0);
}
