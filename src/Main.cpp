/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Main.cpp
*/

#include "Engine/Core/Application.hpp"
#include "Macro.hpp"

int main(void)
{
    zap::core::Application::getInstance().run();

    return SUCCESS;
}
