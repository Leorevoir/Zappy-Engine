/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.cpp
*/

#include <Engine/Event/EventManager.hpp>
#include <Engine/Render/Renderer.hpp>
#include <Engine/System/Timer.hpp>
#include <Engine/ZapEngine.hpp>

#include <Macro.hpp>

#include <thread>

int main(const int argc, const char **argv)
{
    if (argc != 2) {
        return ERROR;
    }

    zap::Engine::initialize(argv[1]);
    zap::Window &window = zap::Engine::getWindow();

    while (!window.shouldClose()) {

        zap::EventManager::pollEvents();
        zap::Timer::update();
        zap::Renderer().render();

        window.swapBuffer();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    return SUCCESS;
}
