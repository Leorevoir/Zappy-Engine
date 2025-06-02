/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** TutoGame.cpp
*/

#include <TutoGame.hpp>

#include <Zap/Filename.hpp>

#include <memory>

/**
* public
*/

void tuto::Game::init()
{
    zap::ecs::Entity player;

    player.addComponent(load_model("player"));
}

/**
* private
*/

tuto::Model tuto::Game::load_model(const std::string &name) const
{
    return std::make_shared<zap::ecs::Model>(zap::Filename::getPath("assets/models/" + name + ".obj"));
}
