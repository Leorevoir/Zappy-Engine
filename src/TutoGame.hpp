/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** TutoGame.hpp
*/

#pragma once

#include <Zap/Context.hpp>
#include <Zap/ECS/Texture/Model.hpp>
#include <Zap/GameEngine.hpp>

namespace tuto {

using Model = std::shared_ptr<zap::ecs::Model>;

class Game final : public zap::abstract::GameEngine
{
    public:
        explicit Game() = default;
        ~Game() override = default;

        void init() override;

    private:
        Model load_model(const std::string &name) const;
};

}// namespace tuto
