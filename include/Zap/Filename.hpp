/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Filename.hpp
*/

#pragma once

#include <string>
#include <vector>

namespace zap::Filename {

[[nodiscard]] std::string getPath(const std::string &name);
[[nodiscard]] bool exists(const std::string &path);
[[nodiscard]] std::string getCurrentDir();
[[nodiscard]] std::vector<std::string> getLines(const std::string &path);

}// namespace zap::Filename
