/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Model.hpp
*/

#pragma once

#include <Zap/ECS/Entity/Component.hpp>
#include <Zap/Types.hpp>

#include <memory>
#include <vector>

namespace zap::ecs {

struct ModelData {
        std::vector<f32> _vertices;
        std::vector<u32> _indices;
        std::vector<f32> _normals;
        std::vector<f32> _tex_coords;
        f32 _furthest_point;
};

class Model : public Component
{
    public:
        u32 _vao;
        u32 _vertex_count;

        Model(u32 vao_id, const std::vector<u32> &vbos, u32 vertex_count, u32 num_attrib_arrays);
        ~Model();

        void bind() const;
        void unbind() const;
        void draw() const;

        using ModelPtr = std::shared_ptr<Model>;

        static ModelPtr load(const std::string &file_path);
        static ModelPtr load(const ModelData &model_data);
        static ModelPtr load2D(const std::vector<f32> &vertices);
        static ModelPtr load3D(const std::vector<f32> &vertices);

    private:
        std::vector<u32> _vbos;
        u32 _num_attrib_arrays;

        u32 create_vao();
        void unbind_vao();
        void bind_indices(const std::vector<i32> &indices);
        void store_data(u32 attribute_number, i32 coordinate_size, const std::vector<f32> &data);
};

}// namespace zap::ecs
