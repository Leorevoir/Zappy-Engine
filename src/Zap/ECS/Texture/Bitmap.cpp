/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Bitmap.cpp
*/

#include <Zap/ECS/Texture/Bitmap.hpp>
#include <Zap/Logger.hpp>
#include <Zap/Utils.hpp>

/**
* public
*/

zap::ecs::Bitmap::Bitmap(const std::string &path)
{
    _load_bitmap(path);
}

bool zap::ecs::Bitmap::is_alpha() const
{
    return _num_channels == ZAP_ECS_BITMAP_FORCE_ALPHA;
}

zap::ecs::Bitmap zap::ecs::Bitmap::multiply_alpha()
{
    if (_num_channels != 4) {
        return *this;
    }

    for (i32 y = 0; y < _size._y; ++y) {
        for (i32 x = 0; x < _size._x; ++x) {

            // const i32 offset = (x + y * _size._x) * _num_channels;
            const i32 offset = ((_size._x - x - 1) + y * _size._x) * _num_channels;
            const f32 alpha = static_cast<f32>(_pixels[static_cast<u32>(offset + 3)]) / 255.0f;

            for (i32 c = 0; c < 3; ++c) {

                const i32 original = _pixels[static_cast<u32>(offset + c)];
                const i32 scaled = static_cast<int>(static_cast<f32>(original) * alpha);
                _pixels[static_cast<u32>(offset + c)] = static_cast<u8>(scaled);
            }
        }
    }

    return *this;
}

//TODO: template this function to avoid code duplication
zap::ecs::Bitmap zap::ecs::Bitmap::flip_x()
{
    std::vector<u8> pixels = _pixels;

    for (i32 y = 0; y < _size._y; ++y) {
        for (i32 x = 0; x < _size._x; ++x) {

            const i32 src_offset = (x + y * _size._x) * _num_channels;
            const i32 dst_offset = ((_size._x - x - 1) + y * _size._x) * _num_channels;

            for (i32 c = 0; c < _num_channels; ++c) {
                pixels[static_cast<u32>(dst_offset + c)] = _pixels[static_cast<u32>(src_offset + c)];
            }
        }
    }

    _pixels = pixels;
    return *this;
}

//TODO: template this function to avoid code duplication
zap::ecs::Bitmap zap::ecs::Bitmap::flip_y()
{
    std::vector<u8> pixels = _pixels;

    for (i32 y = 0; y < _size._y; ++y) {
        for (i32 x = 0; x < _size._x; ++x) {

            const i32 src_offset = (x + y * _size._x) * _num_channels;
            const i32 dst_offset = (x + (_size._y - y - 1) * _size._x) * _num_channels;

            for (i32 c = 0; c < _num_channels; ++c) {
                pixels[static_cast<u32>(dst_offset + c)] = _pixels[static_cast<u32>(src_offset + c)];
            }
        }
    }
    _pixels = pixels;
    return *this;
}

/**
 * setters
 */

void zap::ecs::Bitmap::set_pixel(const Vec2i &pixel, const ColorU8 &color)
{
    if (pixel._x < 0 || pixel._y < 0 || pixel._x >= _size._x || pixel._y >= _size._y) {
        logger::debug("Bitmap::set_pixel: pixel out of bounds for: ", pixel, " in bitmap of size: ", _size);
        return;
    }

    const i32 offset = (pixel._x + pixel._y * _size._x) * _num_channels;

    _pixels[static_cast<u32>(offset)] = color.r;
    _pixels[static_cast<u32>(offset + 1)] = color.g;
    _pixels[static_cast<u32>(offset + 2)] = color.b;
    _pixels[static_cast<u32>(offset + 3)] = color.a;
}

/**
 * getters
 */

const Vec2i &zap::ecs::Bitmap::getSize() const
{
    return _size;
}

const std::vector<u8> &zap::ecs::Bitmap::get_pixels() const
{
    return _pixels;
}

const ColorU8 zap::ecs::Bitmap::get_pixel(const Vec2i &position) const
{
    const u32 offset = static_cast<u32>((position._x + position._y * _size._x) * _num_channels);

    const u8 r = _pixels[offset];
    const u8 g = _pixels[offset + 1];
    const u8 b = _pixels[offset + 2];
    const u8 a = (_num_channels == 4) ? _pixels[offset + 3] : 255;

    return ColorU8(r, g, b, a);
}

/**
* private
*/

void zap::ecs::Bitmap::_load_bitmap(const std::string &filename)
{
    u8 *data = zap::utils::load_image(filename, _size, _num_channels);
    const i32 data_size = _size._x * _size._y * _num_channels;

    _pixels.assign(data, data + data_size);
    zap::utils::free_image(data);
}
