/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Entity.hpp
*/

#include <Zap/ECS/Entity.hpp>
#include <algorithm>

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
    ComponentType type = typeid(component).name();

    addComponent(type, component);
}

void zap::ecs::Entity::addComponent(ComponentType type, std::shared_ptr<zap::ecs::Component> component)
{
    _components[type] = component;
    _componentList.push_back(component);
}

std::shared_ptr<zap::ecs::Component> zap::ecs::Entity::removeComponent(ComponentType type)
{
    auto it = _components.find(type);
    if (it != _components.end()) {
        std::shared_ptr<zap::ecs::Component> removed = it->second;
        _components.erase(it);
        _componentList.erase(::std::remove(_componentList.begin(), _componentList.end(), removed), _componentList.end());
        return removed;
    }
    return nullptr;
}

std::shared_ptr<zap::ecs::Component> zap::ecs::Entity::getComponent(ComponentType type) const
{
    auto it = _components.find(type);
    return it != _components.end() ? it->second : nullptr;
}

bool zap::ecs::Entity::hasComponent(ComponentType type) const
{
    return _components.find(type) != _components.end();
}

const std::vector<std::shared_ptr<zap::ecs::Component>> &zap::ecs::Entity::getAllComponents() const
{
    return _componentList;
}
