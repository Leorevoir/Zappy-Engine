/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** TutoGame.hpp
*/

#pragma once

#include <Zap/Context.hpp>
#include <Zap/ECS/Model/Model.hpp>
#include <Zap/ECS/Texture/Texture.hpp>
#include <Zap/GameEngine.hpp>

namespace tuto {

class Game final : public zap::abstract::GameEngine
{
    public:
        explicit Game() = default;
        ~Game() override = default;

        void init() override;

    private:
        zap::ecs::Model::ModelPtr load_model(const std::string &name) const;
        zap::ecs::Texture::TexturePtr load_texture(const std::string &name) const;
};

}// namespace tuto
