/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** EntityCount.cpp
*/

#include <Zap/ECS/Entity/EntityCount.hpp>

/**
 * public
 */

u32 zap::ecs::EntityCount::_count = 0;

u32 zap::ecs::EntityCount::increment()
{
    return ++_count;
}

u32 zap::ecs::EntityCount::decrement()
{
    if (_count == 0) {
        return 0;
    }
    return --_count;
}
