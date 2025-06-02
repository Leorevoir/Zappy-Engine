/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Component.hpp
*/

#pragma once

#include <string>

namespace zap::ecs {

class Component
{
    public:
        virtual ~Component() = default;
};

using ComponentName = std::string;

}// namespace zap::ecs
