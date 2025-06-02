/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** GameEngine.cpp
*/

#include "Zap/Logger.hpp"
#include <Zap/GameEngine.hpp>

void zap::abstract::GameEngine::startup()
{
    logger::debug("initializing game engine...");
    this->init();
    logger::debug("game engine initialized");
}

void zap::abstract::GameEngine::update()
{
    //
}

void zap::abstract::GameEngine::render()
{
    // ecs::Engine::render();
}

void zap::abstract::GameEngine::flush()
{
    // ecs::Engine::flush();
    logger::debug("game engine flushed");
}
