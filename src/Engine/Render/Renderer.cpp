/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"
#include "Filename.hpp"
#include "Macro.hpp"

#include <Engine/Core/Timer.hpp>
#include <Engine/Render/InstanceBuffer.hpp>

/**
* public
*/

/**
 * @brief max amount of objects to be rendered
 */
#define ZAP_MAX_OBJECTS_AMOUNT 100000

const std::vector<glm::mat4> generateAsteroidTransforms(zap::u32 count, const float radius, const float offset)
{
    std::vector<glm::mat4> matrices;

    matrices.reserve(count);
    srand(static_cast<zap::u32>(zap::core::Timer::getTotalTime()));

    for (zap::u32 i = 0; i < count; ++i) {

        glm::mat4 model = glm::mat4(1.0f);

        const float angle = (float) i / (float) count * 360.0f;
        float displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        const float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        const float y = displacement * 0.4f;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        const float z = cos(angle) * radius + displacement;

        model = glm::translate(model, glm::vec3(x, y, z));

        const float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        const float rotation_angle = static_cast<float>(rand() % 360);
        model = glm::rotate(model, glm::radians(rotation_angle), glm::vec3(0.4f, 0.6f, 0.8f));

        matrices.push_back(model);
    }
    return matrices;
}

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
    const auto matrices = generateAsteroidTransforms(ZAP_MAX_OBJECTS_AMOUNT, 150.0f, 25.0f);
    InstanceBuffer instanceBuffer(matrices);

    for (u32 i = 0; i < _asteroid_model->_meshes.size(); ++i) {
        instanceBuffer.bindToVAO(_asteroid_model->_meshes[i]._VAO);
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
