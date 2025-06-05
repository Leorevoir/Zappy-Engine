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

static const std::vector<std::string> _split_by_space(const std::string &line)
{
    std::istringstream stream(line);
    std::string word;
    std::vector<std::string> result;

    while (stream >> word) {
        result.push_back(word);
    }
    return result;
}

static const Vec3f _create_vec3f(const std::vector<std::string> &words, const u64 l)
{
    if (words.size() != 4) {
        throw zap::exception::Error("zap::obj::load", "invalid vertex line: (L.", l, ") ");
    }
    return Vec3f{std::stod(words[1]), std::stod(words[2]), std::stod(words[3])};
}

static const Vec2f _create_vec2f(const std::vector<std::string> &words, const u64 l)
{
    if (words.size() != 3) {
        throw zap::exception::Error("zap::obj::load", "invalid texture line: (L.", l, ") ");
    }
    return Vec2f{std::stod(words[1]), std::stod(words[2])};
}

zap::ecs::ModelData zap::obj::load(const std::string &filename)
{
    logger::debug("loading obj file: ", filename);

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
            const Vec3f vec3 = _create_vec3f(_split_by_space(l), line_number);
            vertices.push_back(Vertex{vec3, vertices.size()});
        }

        /** @brief `vt ` for texture coordinates */
        if (l.starts_with("vt ")) {
            const Vec2f vec2 = _create_vec2f(_split_by_space(l), line_number);
            textures.push_back(vec2);
        }

        /** @brief `vn ` for vertex normals */
        if (l.starts_with("vn ")) {
            const Vec3f vec3 = _create_vec3f(_split_by_space(l), line_number);
            normals.push_back(vec3);
        }

        /** @brief `f ` for faces */
        // if (l.starts_with("f ")) {
        //     break;
        // }
    }

    return ecs::ModelData{{}, indices, {}, {}, 0.0f};
}
