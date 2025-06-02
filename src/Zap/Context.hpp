/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Context.hpp
*/

#include <Zap/ECS/Engine.hpp>

namespace zap::context {

void run(const char *title, ecs::Engine &game);
void run(const char *title, ecs::Engine &game, const Vec2u windowSize);
void run(const char *title, ecs::Engine &game, const Vec2u windowSize, f64 frame_rate);

}// namespace zap::context
