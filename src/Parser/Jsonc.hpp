/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Jsonc.hpp
*/

#pragma once

#include <Macro.hpp>
#include <Parser/JsoncTypes.hpp>

namespace zap::parser {

JsonValue Jsonc(const char *RESTRICT filepath);

#if defined(UNIT_TESTS)
unit_static void skipWhitespace(Iterator &it, const Iterator &end);
unit_static char get(Iterator &it, const Iterator &end);
unit_static char peek(Iterator it, const Iterator &end);
unit_static void expect(Iterator &it, const Iterator &end, char expected);
unit_static void check_comma(const Iterator &it, const Iterator &end);
unit_static JsonValue parseNull(Iterator &it, const Iterator &end);
unit_static JsonValue parseBool(Iterator &it, const Iterator &end);
unit_static JsonValue parseNumber(Iterator &it, const Iterator &end);
unit_static JsonValue parseString(Iterator &it, const Iterator &end, const bool key);
unit_static JsonValue parseArray(Iterator &it, const Iterator &end);
unit_static JsonValue parseObject(Iterator &it, const Iterator &end);
unit_static JsonValue parseValue(Iterator &it, const Iterator &end);
#endif

}// namespace zap::parser
