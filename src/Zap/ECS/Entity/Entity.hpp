/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Entity.hpp
*/

#pragma once

#include <Zap/ECS/Entity/Component.hpp>
#include <Zap/Types.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace zap::ecs {

class Entity
{
    public:
        explicit Entity();
        explicit Entity(const std::string &name);

        const std::string &getName() const;
        void setName(const std::string &name);

        void addComponent(std::shared_ptr<Component> component);
        void addComponent(ComponentName name, std::shared_ptr<Component> component);
        std::shared_ptr<Component> removeComponent(ComponentName name);
        std::shared_ptr<Component> getComponent(ComponentName name) const;
        bool hasComponent(ComponentName name) const;
        const std::vector<std::shared_ptr<Component>> &getAllComponents() const;

    private:
        std::string _name;
        std::unordered_map<ComponentName, std::shared_ptr<Component>> _components;
        std::vector<std::shared_ptr<Component>> _componentList;
};

}// namespace zap::ecs
