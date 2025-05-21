#pragma once

#include "Mesh.hpp"
#include <memory>

namespace zap {

class Quad
{
    public:
        Quad();
        void draw() const;

    private:
        std::unique_ptr<Mesh> _mesh;
};

}// namespace zap
