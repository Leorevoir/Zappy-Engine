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

#include <Engine/Core/Timer.hpp>
#include <iostream>
/**
* public
*/

/**
 * @brief max amount of objects to be rendered
 */
#define ZAP_MAX_OBJECTS_AMOUNT 100000

/**
* @brief Renderer::initialize
* @details initialize the renderer with a window (to be rendered to)
* @return void
*/
void zap::Renderer::initialize(WindowPtr window)
{
    _window = window;
    _camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 155.0f));
    _asteroid_shader = std::make_shared<Shader>(Filename::getPath("assets/shaders/asteroid.vert"), Filename::getPath("assets/shaders/asteroid.frag"));
    _planet_shader = std::make_shared<Shader>(Filename::getPath("assets/shaders/planet.vert"), Filename::getPath("assets/shaders/planet.frag"));
    _asteroid_model = std::make_shared<Model>(Filename::getPath("assets/objects/rock/rock.obj"));
    _planet_model = std::make_shared<Model>(Filename::getPath("assets/objects/planet/planet.obj"));

    /**
     * WARN: ugly
     */

    glm::mat4 *model_matrices;
    model_matrices = new glm::mat4[ZAP_MAX_OBJECTS_AMOUNT];
    srand(static_cast<u32>(core::Timer::getTotalTime()));
    zap::f32 radius = 150.0;
    zap::f32 offset = 25.0f;
    for (u32 i = 0; i < ZAP_MAX_OBJECTS_AMOUNT; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        zap::f32 angle = (float) i / (float) ZAP_MAX_OBJECTS_AMOUNT * 360.0f;
        zap::f32 displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        zap::f32 x = sin(angle) * radius + displacement;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        zap::f32 y = displacement * 0.4f;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        zap::f32 z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        zap::f32 scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        zap::f32 rotation_angle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotation_angle, glm::vec3(0.4f, 0.6f, 0.8f));

        model_matrices[i] = model;
    }

    u32 buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, ZAP_MAX_OBJECTS_AMOUNT * sizeof(glm::mat4), &model_matrices[0], GL_STATIC_DRAW);

    for (u32 i = 0; i < _asteroid_model->_meshes.size(); ++i) {
        u32 VAO = _asteroid_model->_meshes[i]._VAO;
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) 0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
}

void zap::Renderer::shutdown() noexcept
{
    /* __dtor__ >> clear any shader <$| GPU |$> ressources */
    _asteroid_model.reset();
    _planet_model.reset();
    _asteroid_shader.reset();
    _planet_shader.reset();
}

static inline void c_render_clear_context(void)
{
    glClearColor(ZAP_GL_CLEAR_COLOR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void zap::Renderer::render() noexcept
{
    c_render_clear_context();

    /**
     * WARN: ugly
     */

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.f / 1080.f, 0.1f, 1000.0f);
    glm::mat4 view = _camera->getViewMatrix();
    _asteroid_shader->use();
    _asteroid_shader->setMat4("projection", projection);
    _asteroid_shader->setMat4("view", view);
    _planet_shader->use();
    _planet_shader->setMat4("projection", projection);
    _planet_shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    _planet_shader->setMat4("model", model);
    _planet_model->draw(*_planet_shader);

    _asteroid_shader->use();
    _asteroid_shader->setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _asteroid_model->_textures[0]._id);
    for (unsigned int i = 0; i < _asteroid_model->_meshes.size(); i++) {
        glBindVertexArray(_asteroid_model->_meshes[i]._VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(_asteroid_model->_meshes[i]._indices.size()), GL_UNSIGNED_INT, 0, ZAP_MAX_OBJECTS_AMOUNT);
        glBindVertexArray(0);
    }
}

/**
* private
*/

zap::WindowPtr zap::Renderer::_window = nullptr;
zap::CameraPtr zap::Renderer::_camera = nullptr;
zap::ShaderPtr zap::Renderer::_planet_shader = nullptr;
zap::ShaderPtr zap::Renderer::_asteroid_shader = nullptr;
zap::ModelPtr zap::Renderer::_asteroid_model = nullptr;
zap::ModelPtr zap::Renderer::_planet_model = nullptr;
