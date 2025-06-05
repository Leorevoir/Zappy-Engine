/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Macro.hpp
*/

#pragma once

#define SUCCESS 0
#define ERROR 84

#if defined(_MSC_VER)
    #define RESTRICT __restrict
#elif defined(__GNUC__)
    #define RESTRICT __restrict__
#else
    #define RESTRICT
#endif

#if defined(UNIT_TESTS)
    #define unit_static
#else
    #define unit_static static
#endif

#if defined(DEBUG)
    #define ZAP_VISIBILITY __attribute__((visibility("default")))
#else
    #define ZAP_VISIBILITY __attribute__((visibility("hidden")))
#endif

#define UNUSED __attribute__((unused))

/**
* @brief DEFAULT MACROS
* @details default general macros to avoid magic numbers everywhere
*/

#define ZAP_EPSILON 1e-6
#define ZAP_EPSILON_F32 1e-6f

#define ZAP_INVALID_INDEX -1

#define ZAP_DEFAULT_VALUE 0

#define ZAP_OPENGL_CONTEXT_MAJOR 3
#define ZAP_OPENGL_CONTEXT_MINOR 3

#define ZAP_GLINT_VIEWPORT 0
#define ZAP_DEFAULT_RATIO 1
#define ZAP_DEFAULT_INTERVAL 1

#define ZAP_DEFAULT_WIDOW_SIZE {1920, 1080}
#define ZAP_GL_CLEAR_COLOR 0.1f, 0.1f, 0.1f, 1.0f

#define ZAP_INFO_LOG_BUFFER_SIZE 1042

#define ZAP_DEFAULT_GLSIZEI 1

#define ZAP_DEFAULT_FRAMERATE 60.0
