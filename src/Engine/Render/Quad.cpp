#include "Quad.hpp"

// clang-format off
static std::vector<zap::f32> vertices = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

static std::vector<zap::u32> indices = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
// clang-format on

zap::Quad::Quad()
{
    _mesh = std::make_unique<Mesh>(vertices, indices);
}

void zap::Quad::draw() const
{
    _mesh->draw();
}
