/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Entity.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace zap::ecs {

class Component
{
    public:
        virtual ~Component() = default;
};

using ComponentType = std::string;

class Entity
{
    public:
        explicit Entity(const std::string &name);

        const std::string &getName() const;
        void setName(const std::string &name);

        void addComponent(std::shared_ptr<Component> component);
        void addComponent(ComponentType type, std::shared_ptr<Component> component);
        std::shared_ptr<Component> removeComponent(ComponentType type);
        std::shared_ptr<Component> getComponent(ComponentType type) const;
        bool hasComponent(ComponentType type) const;
        const std::vector<std::shared_ptr<Component>> &getAllComponents() const;

    private:
        std::string _name;
        std::unordered_map<ComponentType, std::shared_ptr<Component>> _components;
        std::vector<std::shared_ptr<Component>> _componentList;
};

}// namespace zap::ecs
