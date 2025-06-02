/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Entity.cpp
*/

#include <Zap/Engine/Entity.hpp>

/**
* EntityCounter
*/

u32 zap::EntityCounter::_count = 0;

u32 zap::EntityCounter::increment(void)
{
    return ++_count;
}

u32 zap::EntityCounter::count(void)
{
    return _count;
}

void zap::EntityCounter::reset(void)
{
    _count = 0;
}

/**
* Entity
*/

zap::Entity::Entity(const std::string &name) : _name(name)
{
    /* __ctor__ */
}

zap::Entity::Entity() : Entity("_entity" + std::to_string(EntityCounter::increment()))
{
    /* __ctor__ */
}

std::vector<std::shared_ptr<zap::Component>> zap::Entity::getAll() const noexcept
{
    std::vector<std::shared_ptr<Component>> result;

    for (const auto &pair : components) {
        result.push_back(pair.second);
    }
    return result;
}
