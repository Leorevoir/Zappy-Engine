/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** GameEngine.hpp
*/

#pragma once

#include <Zap/ECS/Engine.hpp>

namespace zap::abstract {

class GameEngine : public ecs::Engine
{
    public:
        virtual ~GameEngine() = default;

        void startup() override;
        void update();
        void render() override;
        void flush() override;
};

}// namespace zap::abstract
