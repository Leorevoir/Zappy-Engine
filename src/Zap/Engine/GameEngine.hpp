/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** GameEngine.hpp
*/

#pragma once

#include <Zap/Engine/Engine.hpp>

namespace zap::abstract {

class GameEngine : public abstract::Engine
{
    public:
        virtual ~GameEngine() = default;

        void startup();
        void update();

    private:
};

}// namespace zap::abstract
