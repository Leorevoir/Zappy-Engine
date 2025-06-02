/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Filename.cpp
*/

#include <Zap/Filename.hpp>
#include <filesystem>

std::string zap::Filename::getPath(const std::string &name)
{
    const std::filesystem::path relative = "assets/models/" + name + ".obj";
    const std::filesystem::path absolute = std::filesystem::absolute(relative);

    return absolute.string();
}

bool zap::Filename::exists(const std::string &path)
{
    return std::filesystem::exists(path);
}

std::string zap::Filename::getCurrentDir()
{
    return std::filesystem::current_path().string();
}
