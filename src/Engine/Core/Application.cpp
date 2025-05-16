/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Error.hpp"

// clang-format off
#include <glad/gl.h>
#include "GLFW/glfw3.h"
// clang-format on

/**
* public
*/

/**
* @brief Application::getInstance
* @details get instance of the Application (singleton)
* @return Application & (ref to the instance)
*/
zap::core::Application &zap::core::Application::getInstance() noexcept
{
    static Application instance;

    return instance;
}

#include <iostream>
/**
* @brief Application::run
* @details main entry-point, run the application
* @return void
*/
void zap::core::Application::run()
{
    std::cout << "vector tests" << std::endl;
    math::Vector2<float> vec2(1.0f, 2.0f);
    math::Vector3<unsigned short> vec3(3, 4, 1);

    std::cout << vec2 << std::endl;
    std::cout << vec3 << std::endl;
    //
}

/**
* private
*/

/**
 * @brief __ctor__
 * @details private __ctor__
 * @return [this]
 */
zap::core::Application::Application()
{
    _init();
}

/**
* @brief __dtor__
* @details private __dtor__
* @return [~this]
*/
zap::core::Application::~Application()
{
    _destroy();
}

/**
* @brief Application::_init
* @details initialize GLFW context & ressources
* @return void
*/
void zap::core::Application::_init()
{
    if (glfwInit() == GLFW_FALSE) {
        throw exception::Error("core::Application::_init()", "Failed to initialize GLFW");
    }
}

/**
* @brief Application::_destroy
* @details destroy GLFW context & ressources
* @return void
*/
void zap::core::Application::_destroy() noexcept
{
    glfwTerminate();
}
