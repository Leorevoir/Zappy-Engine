/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** MouseEvent.hpp
*/

#pragma once

#include "IEvent.hpp"
#include <Engine/Math/Vector2.hpp>

namespace zap {

class MouseEvent : public IEvent
{
    public:
        explicit MouseEvent(const math::Vector2<double> &) noexcept;

        [[nodiscard]] const math::Vector2<double> getPosition() const noexcept;

    protected:
        math::Vector2<double> _position;
};

class MouseMovedEvent : public MouseEvent
{
    public:
        using MouseEvent::MouseEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

class MouseScrolledEvent : public MouseEvent
{
    public:
        using MouseEvent::MouseEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

class MouseButtonEvent : public IEvent
{
    public:
        explicit MouseButtonEvent(int button) noexcept;

        [[nodiscard]] int getButton() const noexcept;

    protected:
        int _button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
    public:
        using MouseButtonEvent::MouseButtonEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
    public:
        using MouseButtonEvent::MouseButtonEvent;

        [[nodiscard]] EventType getType() const noexcept override;
};

}// namespace zap
