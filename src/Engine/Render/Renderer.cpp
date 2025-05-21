/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"
#include "Error.hpp"
#include "Filename.hpp"
#include "Macro.hpp"

/**
* public
*/

#define TEST_SHADER_VERTEX "assets/shaders/test.vert"
#define TEST_SHADER_FRAGMENT "assets/shaders/test.frag"

/**
* @brief Renderer::initialize
* @details initialize the renderer with a window (to be rendered to)
* @return void
*/
void zap::Renderer::initialize(WindowPtr window)
{
    _window = window;
    _shader = std::make_unique<zap::Shader>(TEST_SHADER_VERTEX, TEST_SHADER_FRAGMENT);
    _texture = std::make_unique<zap::Texture>(Filename::getPath("assets/textures/container.jpg"));
    _quad = std::make_unique<Quad>();
    _shader->use();
    _shader->setInt("texture1", 0);
}

void zap::Renderer::shutdown() noexcept
{
    /* __dtor__ >> clear any shader <$| GPU |$> ressources */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    _shader.reset();
    _texture.reset();
    _quad.reset();
}

extern "C" {
static inline void c_render_clear_context(void)
{
    glClearColor(ZAP_GL_CLEAR_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);
}
}

void zap::Renderer::render() noexcept
{
    c_render_clear_context();

    _shader->use();
    _texture->bind(0);
    _quad->draw();
}

/**
* private
*/

zap::WindowPtr zap::Renderer::_window = nullptr;
zap::ShaderPtr zap::Renderer::_shader = nullptr;
zap::TexturePtr zap::Renderer::_texture = nullptr;
zap::QuadPtr zap::Renderer::_quad = nullptr;

zap::u32 zap::Renderer::VAO = 0;
zap::u32 zap::Renderer::VBO = 0;
zap::u32 zap::Renderer::EBO = 0;
