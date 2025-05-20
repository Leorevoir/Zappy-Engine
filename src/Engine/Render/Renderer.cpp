/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"
#include "Macro.hpp"

/**
* public
*/

static float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
};

static zap::u32 VBO, VAO;

#define TEST_SHADER_VERTEX "assets/shaders/test.vert"
#define TEST_SHADER_FRAGMENT "assets/shaders/test.frag"

/**
* @brief Renderer::initialize
* @details initialize the renderer with a window (to be rendered to)
* @return void
*/
void zap::Renderer::initialize(WindowPtr window) noexcept
{
    _window = window;
    _shader = std::make_unique<zap::Shader>(TEST_SHADER_VERTEX, TEST_SHADER_FRAGMENT);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void zap::Renderer::shutdown() noexcept
{
    /* __dtor__ >> clear any shader <$| GPU |$> ressources */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    _shader.reset();
}

extern "C" {
static inline void c_render_clear_context(void)
{
    glClearColor(ZAP_GL_CLEAR_COLOR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
}

void zap::Renderer::render() noexcept
{
    c_render_clear_context();
    _shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/**
* private
*/

zap::WindowPtr zap::Renderer::_window = nullptr;
zap::ShaderPtr zap::Renderer::_shader = nullptr;
