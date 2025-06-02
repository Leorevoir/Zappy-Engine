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
        virtual void init() = 0;

        void startup();
        void update();
};

}// namespace zap::abstract
