#pragma once

/**
* @file GLEngineTypes.hpp
* @brief define types for the Engine
* WARN: **always** include `<glad/gl.h>` **before** `<GLFW/glfw3.h>`
*/

// clang-format off
#include <glad/gl.h>
#include "GLFW/glfw3.h"
// clang-format on

namespace zap {
using WindowPtr = GLFWwindow *;
}
