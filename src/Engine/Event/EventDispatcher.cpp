/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** EventDispatcher.cpp
*/

#include "EventDispatcher.hpp"

/**
* public
*/

/**
* @brief EventDispatcher::subscribe
* @details subscribe a callback to an event type
* @param type the event type
* @param handler the callback to call when the event is dispatched
* @return void
*/
void zap::EventDispatcher::subscribe(const EventType type, Callback handler) noexcept
{
    _callbacks[type].push_back(handler);
}

/**
* @brief EventDispatcher::dispatch
* @details dispatch an event to all the callbacks subscribed to it
* @param event the event to dispatch
* @return void
*/
void zap::EventDispatcher::dispatch(const IEvent &event) const noexcept
{
    const auto it = _callbacks.find(event.getType());

    if (it != _callbacks.end()) {
        for (const auto &handler : it->second) {
            handler(event);
        }
    }
}
