/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Filename.hpp
*/

#pragma once

#include <string>

namespace zap::Filename {

[[nodiscard]] std::string getPath(const std::string &name);
[[nodiscard]] bool exists(const std::string &path);
[[nodiscard]] std::string getCurrentDir();

}// namespace zap::Filename
