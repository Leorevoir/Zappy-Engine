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

#define UNUSED __attribute__((unused))

/**
* @brief DEFAULT MACROS
* @details default general macros to avoid magic numbers everywhere
*/

#define ZAP_OPENGL_CONTEXT_MAJOR 3
#define ZAP_OPENGL_CONTEXT_MINOR 3

#define ZAP_GLINT_VIEWPORT 0
#define ZAP_DEFAULT_RATIO 1
#define ZAP_DEFAULT_INTERVAL 1
