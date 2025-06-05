/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Utils.cpp
*/

#include <stb_image.h>

#include <Zap/Logger.hpp>
#include <Zap/Utils.hpp>

#include <Zap/Error.hpp>

u8 *zap::utils::load_image(const std::string &filename, Vec2i &out_size, i32 &out_num_channels, const i32 desired_channels)
{
    u8 *data = stbi_load(filename.c_str(), &out_size._x, &out_size._y, &out_num_channels, desired_channels);

    if (!data) {
        throw exception::Error("zap::utils::load_image", "failed to load image: ", filename);
    }
    return data;
}

void zap::utils::free_image(u8 *data)
{
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    } else {
        zap::logger::debug("zap::utils::free_image", "attempted to free a null pointer");
    }
}
