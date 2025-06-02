/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Engine.hpp
*/

#pragma once

#include <Zap/ECS/Entity.hpp>
#include <Zap/ECS/System.hpp>
#include <string>

namespace zap::ecs {

class Engine
{
    public:
        virtual ~Engine() = default;

        void addEntity(std::shared_ptr<Entity> entity);
        void removeEntity(std::shared_ptr<Entity> entity);
        std::shared_ptr<Entity> getEntityByName(const std::string &name);
        void removeAllEntities();

        void addSystem(std::shared_ptr<System> system, int priority);
        void removeSystem(std::shared_ptr<System> system);
        void removeAllSystems();

        void update();

    protected:
        std::vector<std::shared_ptr<Entity>> _entities;
        std::unordered_map<std::string, std::shared_ptr<Entity>> _entityNames;

        std::vector<std::shared_ptr<System>> _systems;
};

}// namespace zap::ecs
