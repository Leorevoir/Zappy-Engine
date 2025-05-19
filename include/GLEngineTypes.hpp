#pragma once

/**
* @file GLEngineTypes.hpp
* @brief define types for the Engine
* WARN: **always** include `<glad/gl.h>` **before** `<GLFW/glfw3.h>`
*/

/**
* INFO: avoid including opengl headers in every files that actually still need zap engine types
*/
#if !defined(ZAP_TYPES_ONLY)
// clang-format off
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// clang-format on
namespace zap {
using WindowPtr = GLFWwindow *;
}// namespace zap
#endif

namespace zap {

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

}// namespace zap
