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

#include <Parser/DebugPrintJsonc.hpp>
#include <Parser/Jsonc.hpp>

int main(const int argc, const char **argv)
{
    if (argc == 2) {
        zap::parser::printJsonc(zap::parser::Jsonc(argv[1]), true);
        return SUCCESS;
    }

    zap::Engine::initialize();
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
