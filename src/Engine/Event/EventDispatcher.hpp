/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** EventDispatcher.hpp
*/

#pragma once

#include "IEvent.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

namespace zap {

/**
* @class EventDispatcher
* @brief used to dispatch events to the callbacks subscribed to them
* @pattern Observer
*/
class EventDispatcher final
{
    public:
        using Callback = std::function<void(const IEvent &)>;
        using CallbackMap = std::unordered_map<EventType, std::vector<Callback>>;

        void dispatch(const IEvent &event) const noexcept;
        void subscribe(const EventType type, Callback handler) noexcept;

    private:
        CallbackMap _callbacks;
};

}// namespace zap
