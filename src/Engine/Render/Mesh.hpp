#pragma once

#include "GLEngineTypes.hpp"
#include <vector>

namespace zap {

class Mesh final
{
    public:
        explicit Mesh(const std::vector<f32> &vertices, const std::vector<u32> &indices) noexcept;
        ~Mesh();

        void draw() const;

    private:
        u32 _VAO, _VBO, _EBO;
        GLsizei _index;
};
}// namespace zap
