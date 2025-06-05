/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Utils.hpp
*/

#pragma once

#include <Zap/Macro.hpp>
#include <Zap/Types.hpp>

namespace zap::utils {

u8 *load_image(const std::string &filename, Vec2i &out_size, i32 &out_num_channels, const i32 desired_channels = 4);
void free_image(u8 *RESTRICT data);

}// namespace zap::utils
