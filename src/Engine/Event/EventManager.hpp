/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** EventManager.hpp
*/

#pragma once

#include "EventDispatcher.hpp"
#include "GLEngineTypes.hpp"

#include "Macro.hpp"

#include "NonCopyable.hpp"

namespace zap {

/**
* @class EventManager
* @brief used to manage events... literally
* @pattern Singleton
*/
class EventManager final : public NonCopyable
{
    public:
        static void init(WindowPtr window);
        static void pollEvents() noexcept;
        static void subscribe(const EventType type, EventDispatcher::Callback handler) noexcept;

    private:
        static EventDispatcher _dispatcher;
        static WindowPtr _window;

        static void keyCallback(WindowPtr UNUSED win, const int key, const int UNUSED scancode, const int action, const int UNUSED mods) noexcept;
};

}// namespace zap
