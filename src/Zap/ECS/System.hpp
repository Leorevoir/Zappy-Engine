/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** System.hpp
*/

#pragma once

#include <Zap/Types.hpp>

namespace zap::ecs {

class System
{
    public:
        virtual ~System() = default;
        virtual void update() = 0;

        i32 priority = 0;
};

}// namespace zap::ecs
