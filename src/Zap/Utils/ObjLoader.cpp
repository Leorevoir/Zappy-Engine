/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** ObjLoader.cpp
*/

#include <Zap/Error.hpp>
#include <Zap/Logger.hpp>

#include <Zap/Filename.hpp>
#include <Zap/ObjLoader.hpp>

static const std::vector<std::string> _split_by(const std::string &line, const char delimiter)
{
    std::vector<std::string> result;
    std::string current;

    for (auto it = line.begin(); it != line.end(); ++it) {
        if (*it == delimiter) {
            result.push_back(current);
            current.clear();
            continue;
        }
        current += *it;
    }

    result.push_back(current);
    return result;
}

static const Vec3f _create_vec3f(const std::vector<std::string> &words, const u64 l)
{
    if (words.size() != 4) {
        throw zap::exception::Error("zap::obj::load", "invalid vertex line: (L.", l, ")");
    }
    return Vec3f{std::stod(words[1]), std::stod(words[2]), std::stod(words[3])};
}

static const Vec2f _create_vec2f(const std::vector<std::string> &words, const u64 l)
{
    if (words.size() != 3) {
        throw zap::exception::Error("zap::obj::load", "invalid texture line: (L.", l, ")");
    }
    return Vec2f{std::stod(words[1]), std::stod(words[2])};
}

static void _already_processed_vertex(zap::obj::Vertex *previous, const i32 texture_index, const i32 normal_index, std::vector<u32> &indices,
    std::vector<zap::obj::Vertex> &vertices)
{
    if (*previous == Vec2i{texture_index, normal_index}) {
        indices.push_back(static_cast<u32>(previous->_index));
    }
    if (previous->_duplicate) {
        _already_processed_vertex(previous->_duplicate, texture_index, normal_index, indices, vertices);
    } else {
        std::unique_ptr<zap::obj::Vertex> duplicate = std::make_unique<zap::obj::Vertex>(previous->_position, vertices.size());

        duplicate->_texture_index = texture_index;
        duplicate->_normal_index = normal_index;
        previous->_duplicate = duplicate.get();
        indices.push_back(static_cast<u32>(duplicate->_index));
        vertices.push_back(*previous);
    }
}

static void _process_vertex(const std::vector<std::string> &vertex, std::vector<zap::obj::Vertex> &vertices, std::vector<u32> &indices, const u64 l)
{
    const u64 index = std::stoul(vertex.front()) - 1;

    if (vertices.size() < index) {
        throw zap::exception::Error("zap::obj::load", "invalid face line: (L.", l, ")");
    }

    zap::obj::Vertex vert = vertices[index];
    const i32 texture_index = std::stoi(vertex[1]) - 1;
    const i32 normal_index = std::stoi(vertex[2]) - 1;

    if (vert.is_valid()) {
        _already_processed_vertex(&vert, texture_index, normal_index, indices, vertices);
        return;
    }

    vert._texture_index = texture_index;
    vert._normal_index = normal_index;
    indices.push_back(static_cast<u32>(index));
}

static void _remove_unused_vertices(std::vector<zap::obj::Vertex> &vertices)
{
    for (auto &vert : vertices) {
        if (vert.is_valid()) {
            continue;
        }
        vert._texture_index = 0;
        vert._normal_index = 0;
    }
}

static f32 _convert_data_to_arrays(std::vector<zap::obj::Vertex> &vertices, std::vector<Vec2f> &textures, std::vector<Vec3f> &normals, std::vector<f32> &vertices_array,
    std::vector<f32> &textures_array, std::vector<f32> &normals_array)
{
    f64 furthest_point = 0;

    for (u64 i = 0; i < vertices.size(); ++i) {
        zap::obj::Vertex &vert = vertices[i];

        if (vert._length > furthest_point) {
            furthest_point = vert._length;
        }

        const Vec3f32 position = static_cast<Vec3f32>(vert._position);
        const Vec3f32 normal_vec3 = static_cast<Vec3f32>(normals[static_cast<size_t>(vert._normal_index)]);
        const Vec2f texture_coord = textures[static_cast<size_t>(vert._texture_index)];

        vertices_array[i * 3] = position._x;
        vertices_array[i * 3 + 1] = position._y;
        vertices_array[i * 3 + 2] = position._z;
        textures_array[i * 2] = static_cast<f32>(texture_coord._x);
        textures_array[i * 2 + 1] = static_cast<f32>(1.0 - texture_coord._y);
        normals_array[i * 3] = normal_vec3._x;
        normals_array[i * 3 + 1] = normal_vec3._y;
        normals_array[i * 3 + 2] = normal_vec3._z;
    }

    return static_cast<f32>(furthest_point);
}

zap::ecs::ModelData zap::obj::load(const std::string &filename)
{
    logger::task_start("loading obj file: ", filename);

    std::vector<Vertex> vertices;
    std::vector<Vec2f> textures;
    std::vector<Vec3f> normals;
    std::vector<u32> indices;
    std::vector<std::string> lines = zap::Filename::getLines(filename);
    u64 line_number = 0;

    for (const auto &l : lines) {
        ++line_number;

        /** @brief obj files support `#` comments */
        if (l.empty() || l.starts_with('#')) {
            continue;
        }

        /** @brief `v ` for vertex positions */
        if (l.starts_with("v ")) {
            const Vec3f vec3 = _create_vec3f(_split_by(l, ' '), line_number);
            vertices.push_back(Vertex{vec3, vertices.size()});
        }

        /** @brief `vt ` for texture coorinates */
        if (l.starts_with("vt ")) {
            const Vec2f vec2 = _create_vec2f(_split_by(l, ' '), line_number);
            textures.push_back(vec2);
        }

        /** @brief `vn ` for vertex normals */
        if (l.starts_with("vn ")) {
            const Vec3f vec3 = _create_vec3f(_split_by(l, ' '), line_number);
            normals.push_back(vec3);
        }

        /** @brief `f ` for faces */
        if (l.starts_with("f ")) {
            const auto split = _split_by(l, ' ');
            const auto vert1 = _split_by(split[1], '/');
            const auto vert2 = _split_by(split[2], '/');
            const auto vert3 = _split_by(split[3], '/');

            _process_vertex(vert1, vertices, indices, line_number);
            _process_vertex(vert2, vertices, indices, line_number);
            _process_vertex(vert3, vertices, indices, line_number);
        }
    }
    logger::task_done("loaded obj file: ", filename);

    logger::task_start("removing unused vertices");
    _remove_unused_vertices(vertices);
    logger::task_done("removed unused vertices");

    logger::task_start("convert to ecs::ModelData");
    std::vector<f32> vertices_array(vertices.size() * 3, 0.0f);
    std::vector<f32> textures_array(vertices.size() * 2, 0.0f);
    std::vector<f32> normals_array(vertices.size() * 3, 0.0f);

    const f32 furthest_point = _convert_data_to_arrays(vertices, textures, normals, vertices_array, textures_array, normals_array);
    logger::task_done("converted to ecs::ModelData");

    return zap::ecs::ModelData{vertices_array, indices, normals_array, textures_array, furthest_point};
}
