/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** ObjLoader.cpp
*/

#include "Zap/Logger.hpp"
#include <Zap/Filename.hpp>
#include <Zap/ObjLoader.hpp>

zap::ecs::ModelData zap::obj::load(const std::string &filename)
{
    std::vector<Vertex> vertices;
    std::vector<Vec2f> textures;
    std::vector<Vec3f> normals;
    std::vector<u32> indices;
    std::vector<std::string> lines = zap::Filename::getLines(filename);

    logger::debug("loading obj file: ", filename);
    for (const auto &l : lines) {
        logger::debug("line: ", l);
    }

    //////////////////////////////:

    return ecs::ModelData{{}, indices, {}, {}, 0.0f};
}
