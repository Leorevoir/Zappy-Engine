/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** JsoncObject.hpp
*/

#include "Engine/Math/Vector2.hpp"
#include "Error.hpp"
#include <Parser/JsoncTypes.hpp>
#include <variant>

namespace zap::parser {

using ParsedJson = JsonProto;
using JsonMap = std::unordered_map<std::string, ParsedJson>;

/**
* @brief parser::getValue
* @details retrives a value from a ParsedJson object
* @return <T> the value of type T
*/
template<typename T>
static inline T getValue(const ParsedJson &jsonc)
{
    if (std::holds_alternative<T>(jsonc.value)) {
        return std::get<T>(jsonc.value);
    }
    if constexpr (std::is_same_v<T, double>) {
        if (std::holds_alternative<int>(jsonc.value)) {
            return static_cast<double>(std::get<int>(jsonc.value));
        }
    }
    throw exception::Error("getValue", std::is_same_v<T, double> ? "Expected number (int or double)" : "Expected type not found");
}

/**
* @brief parser::getVector3
* @details retrieves a 3D vector from a ParsedJson object
* @return Vector3<T> with x, y, z components
*/
template<typename T>
static inline T getVector3(const ParsedJson &jsonc, const char *keyX = "x", const char *keyY = "y", const char *keyZ = "z")
{
    const JsonMap &map = getValue<JsonMap>(jsonc);

    if (map.find(keyX) == map.end() || map.find(keyY) == map.end() || map.find(keyZ) == map.end()) {
        throw exception::Error("getVector3", "Keys '", keyX, "', '", keyY, "' or '", keyZ, "' not found in JSON object");
    }

    const T x = getValue<double>(map.at(keyX));
    const T y = getValue<double>(map.at(keyY));
    const T z = getValue<double>(map.at(keyZ));

    return T{x, y, z};
}

/**
* @brief parser::getVector2
* @details retrieves a 2D vector from a ParsedJson object
* @return Vector2<T> with x, y components
*/
template<typename T>
static inline math::Vector2<T> getVector2(const ParsedJson &jsonc, const char *keyX = "x", const char *keyY = "y")
{
    const JsonMap &map = getValue<JsonMap>(jsonc);

    if (map.find(keyX) == map.end() || map.find(keyY) == map.end()) {
        throw exception::Error("getVector2", "Keys '", keyX, "' or '", keyY, "' not found in JSON object");
    }

    const T x = getValue<T>(map.at(keyX));
    const T y = getValue<T>(map.at(keyY));

    return math::Vector2<T>{x, y};
}

/**
* @brief parser::getObject
* @details retrieves a JSON object from a ParsedJson object
* @return JsonMap containing the key-value pairs of the object
*/
static inline const JsonMap getObject(const JsonValue &jsonc, const char *key)
{
    const JsonMap &map = std::get<JsonMap>(jsonc);

    if (map.find(key) == map.end()) {
        throw exception::Error("getObject", "Key '", key, "' not found in JSON object");
    }

    return std::get<JsonMap>(map.at(key).value);
}

}// namespace zap::parser
