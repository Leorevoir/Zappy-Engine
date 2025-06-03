/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Filename.cpp
*/

#include <Zap/Error.hpp>
#include <Zap/Filename.hpp>

#include <filesystem>
#include <fstream>

std::string zap::Filename::getPath(const std::string &name)
{
    const std::filesystem::path absolute = std::filesystem::absolute(name);

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

std::vector<std::string> zap::Filename::getLines(const std::string &path)
{
    if (!exists(path)) {
        throw exception::Error("zap::Filename::getLines", "file: ", path, " does not exist!");
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        throw exception::Error("zap::Filename::getLines", "cannot open file: ", path);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(std::move(line));
    }

    return lines;
}
