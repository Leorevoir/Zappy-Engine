/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** EntityCount.cpp
*/

#pragma once

#include <Zap/Types.hpp>

namespace zap::ecs {

class EntityCount
{
    public:
        static u32 increment();
        static u32 decrement();

        static u32 _count;
};

}// namespace zap::ecs
