/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Engine.hpp
*/

#include <Zap/Types.hpp>

#include <Zap/Engine/Entity.hpp>

#include <memory>
#include <vector>

namespace zap::abstract {

class Engine
{
    public:
        virtual ~Engine() = default;
        virtual void init() = 0;

        void update();
        void render();
        void flush();

        void addEntity(void);
        void addSystem(void);

    protected:
        Vec2u _window_size;
        std::vector<std::unique_ptr<Entity>> _entities;
};
}// namespace zap::abstract
