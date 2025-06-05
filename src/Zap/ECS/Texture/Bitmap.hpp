/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Bitmap.hpp
*/

#pragma once

#include <Zap/Macro.hpp>
#include <Zap/Types.hpp>

#include <string>
#include <vector>

namespace zap::ecs {

#define ZAP_ECS_BITMAP_FORCE_ALPHA 4

class Bitmap
{
    public:
        explicit Bitmap(const std::string &filename);
        ~Bitmap();

        bool is_alpha() const;
        Bitmap multiply_alpha();

        Bitmap flip_x();
        Bitmap flip_y();

        void set_pixel(const Vec2i &pixel, const ColorU8 &color);

        const Vec2i &getSize() const;
        const std::vector<u8> &get_pixels() const;
        const ColorU8 get_pixel(const Vec2i &position) const;

    private:
        void _load_bitmap(const std::string &filename);

        Vec2i _size;
        i32 _num_channels = 0;
        std::vector<u8> _pixels;
};

}// namespace zap::ecs
