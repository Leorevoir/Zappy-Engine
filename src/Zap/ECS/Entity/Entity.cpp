/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Entity.hpp
*/

#include <Zap/ECS/Entity/Entity.hpp>
#include <Zap/ECS/Entity/EntityCount.hpp>
#include <Zap/Logger.hpp>

#include <algorithm>

/**
 * public
 */

zap::ecs::Entity::Entity()
{
    _name = "_entity" + std::to_string(EntityCount::increment());
}

zap::ecs::Entity::Entity(const std::string &name) : _name(name)
{
    /* __ctor__ */
}

const std::string &zap::ecs::Entity::getName() const
{
    return _name;
}

void zap::ecs::Entity::setName(const std::string &name)
{
    _name = name;
}

void zap::ecs::Entity::addComponent(std::shared_ptr<zap::ecs::Component> component)
{
    const ComponentName name = typeid(component).name();

    addComponent(name, component);
    logger::debug("add component: ", name, " to entity: ", _name);
}

void zap::ecs::Entity::addComponent(ComponentName name, std::shared_ptr<zap::ecs::Component> component)
{
    _components[name] = component;
    _componentList.push_back(component);
    logger::debug("add component: ", name, " to entity: ", _name);
}

std::shared_ptr<zap::ecs::Component> zap::ecs::Entity::removeComponent(ComponentName name)
{
    auto it = _components.find(name);

    if (it != _components.end()) {
        std::shared_ptr<zap::ecs::Component> removed = it->second;

        _components.erase(it);
        _componentList.erase(::std::remove(_componentList.begin(), _componentList.end(), removed), _componentList.end());
        return removed;
    }
    return nullptr;
}

std::shared_ptr<zap::ecs::Component> zap::ecs::Entity::getComponent(ComponentName name) const
{
    const auto it = _components.find(name);

    return it != _components.end() ? it->second : nullptr;
}

bool zap::ecs::Entity::hasComponent(ComponentName name) const
{
    return _components.find(name) != _components.end();
}

const std::vector<std::shared_ptr<zap::ecs::Component>> &zap::ecs::Entity::getAllComponents() const
{
    return _componentList;
}
