/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** TutoGame.cpp
*/

#include <TutoGame.hpp>

#include <Zap/Filename.hpp>
#include <Zap/ObjLoader.hpp>

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

zap::ecs::Texture::TexturePtr tuto::Game::load_texture(const std::string &name) const
{
    return zap::ecs::Texture::load(zap::Filename::getPath("assets/textures/" + name + ".png"));
}

zap::ecs::Model::ModelPtr tuto::Game::load_model(const std::string &name) const
{
    return zap::ecs::Model::load(zap::obj::load(zap::Filename::getPath("assets/models/" + name + ".obj")));
}
