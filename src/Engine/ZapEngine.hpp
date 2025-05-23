/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** ZapEngine.hpp
*/

#include <NonCopyable.hpp>

#include <Engine/System/Window.hpp>

namespace zap {

/**
* @class Engine
* @brief main entry point of the ZapEngine
*/
class Engine final : public abstract::NonCopyable
{
    public:
        static void initialize();

        static Window &getWindow() noexcept;

    private:
        explicit Engine();
        ~Engine() noexcept;

        void _init();
        void _destroy();
};

}// namespace zap
