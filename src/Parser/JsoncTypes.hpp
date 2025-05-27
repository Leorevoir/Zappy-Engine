/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** JsoncTypes
*/

#pragma once

#include <string>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

namespace zap::parser {

template<typename JsonValue>
using JsonBase = std::variant<std::nullptr_t, int, bool, double, std::string, std::vector<JsonValue>, std::unordered_map<std::string, JsonValue>>;

struct JsonProto {
        using type = JsonBase<JsonProto>;
        type value;

        constexpr explicit JsonProto() = default;

        template<typename T, typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, JsonProto>>>
        constexpr explicit JsonProto(T &&val) : value(std::forward<T>(val))
        {
            /* empty __ctor__ */
        }

        explicit operator JsonProto::type() const
        {
            return value;
        }
};

using JsonValue = JsonProto::type;

using Iterator = std::string::const_iterator;

}// namespace zap::parser
