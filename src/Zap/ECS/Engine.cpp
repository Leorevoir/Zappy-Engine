/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Engine.cpp
*/

#include <Zap/ECS/Engine.hpp>
#include <algorithm>

void zap::ecs::Engine::addEntity(std::shared_ptr<Entity> entity)
{
    if (_entityNames.count(entity->getName())) {
        throw std::runtime_error("Entity with name " + entity->getName() + " already exists");
    }
    _entities.push_back(entity);
    _entityNames[entity->getName()] = entity;
}

void zap::ecs::Engine::removeEntity(std::shared_ptr<Entity> entity)
{
    _entityNames.erase(entity->getName());
    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

std::shared_ptr<zap::ecs::Entity> zap::ecs::Engine::getEntityByName(const std::string &name)
{
    auto it = _entityNames.find(name);

    return it != _entityNames.end() ? it->second : nullptr;
}

void zap::ecs::Engine::removeAllEntities()
{
    _entities.clear();
    _entityNames.clear();
}

void zap::ecs::Engine::addSystem(std::shared_ptr<System> system, int priority)
{
    system->priority = priority;
    _systems.push_back(system);
    std::sort(_systems.begin(), _systems.end(), [](auto &a, auto &b) { return a->priority < b->priority; });
}

void zap::ecs::Engine::removeSystem(std::shared_ptr<System> system)
{
    _systems.erase(std::remove(_systems.begin(), _systems.end(), system), _systems.end());
}

void zap::ecs::Engine::removeAllSystems()
{
    _systems.clear();
}

void zap::ecs::Engine::update()
{
    for (auto &system : _systems) {
        system->update();
    }
}
