/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.cpp
*/

#include <Zap/Context.hpp>
#include <Zap/GameEngine.hpp>
#include <Zap/Macro.hpp>
#include <iostream>

class Game : public zap::abstract::GameEngine
{
    public:
        Game() = default;
        ~Game() override = default;

        void init() override
        {
            std::cout << "initialisation du jeu ici" << std::endl;
        }

    private:
};

int main(void)
{
    Game game;

    return zap::context::run("Zappy", game);
}
