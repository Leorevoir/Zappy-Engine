#pragma once

#include "Engine/Math/Vector2.hpp"
#include "GLEngineTypes.hpp"

#include "NonCopyable.hpp"

namespace zap {

/**
* @class
* @brief
* @pattern
*/
class EventManager final : public NonCopyable
{
    public:
        static void init(WindowPtr window);
        static void pollEvents() noexcept;

        [[nodiscard]] static bool isKeyPressed(const int key) noexcept;
        [[nodiscard]] static bool isButtonPressed(const int button) noexcept;
        [[nodiscard]] static const math::Vector2<double> getCursorPosition() noexcept;

    private:
        static WindowPtr _window;
};

}// namespace zap
