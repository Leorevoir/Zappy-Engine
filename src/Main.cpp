/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Main.cpp
*/

#include <Zap/Macro.hpp>

#include <TutoGame.hpp>

int main(void)
{
    tuto::Game game;

    return zap::context::run("Zappy", game);
}
