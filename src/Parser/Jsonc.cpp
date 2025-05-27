/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Parser
*/

#include <Error.hpp>
#include <Parser/Jsonc.hpp>
#include <fstream>
#include <sstream>

#if defined(UNIT_TESTS)
namespace zap::parser {
#endif

unit_static char get(zap::parser::Iterator &it, const zap::parser::Iterator &end)
{
    if (it == end) {
        throw zap::exception::Error("zap::parser::get", "Unexpected end of input");
    }
    return *it++;
}

unit_static char peek(const zap::parser::Iterator it, const zap::parser::Iterator &end)
{
    if (it == end) {
        throw zap::exception::Error("zap::parser::peek", "Unexpected end of input");
    }
    return *it;
}

unit_static void expect(zap::parser::Iterator &it, const zap::parser::Iterator &end, char expected)
{
    if (const char c = get(it, end); c != expected) {
        throw zap::exception::Error("zap::parser::expect", "Expected '", expected, "', got '", c, "'");
    }
}

unit_static void skipWhitespace(zap::parser::Iterator &it, const zap::parser::Iterator &end)
{
    while (it != end) {
        if (std::distance(it, end) >= 2 && std::string(it, it + 2) == "//") {
            it += 2;
            while (it != end && *it != '\n') {
                ++it;
            }
        } else if (std::distance(it, end) >= 2 && std::string(it, it + 2) == "/*") {
            it += 2;
            while (std::distance(it, end) >= 2 && std::string(it, it + 2) != "*/") {
                ++it;
            }
            if (std::distance(it, end) >= 2 && std::string(it, it + 2) == "*/") {
                ++it;
            }
        } else if (!std::isspace(*it)) {
            break;
        }
        ++it;
    }
}

unit_static void check_comma(const zap::parser::Iterator &it, const zap::parser::Iterator &end)
{
    auto start = it;
    bool has_comma = false;

    skipWhitespace(start, end);
    if (start == end) {
        return;
    }
    if (peek(start, end) == ',') {
        has_comma = true;
        ++start;
    }
    skipWhitespace(start, end);
    if (start == end && has_comma) {
        throw zap::exception::Error("zap::parser::check_comma", "Unexpected trailing comma");
    }
    if (const char next = peek(start, end); next != '}' && next != ']' && !has_comma) {
        throw zap::exception::Error("zap::parser::check_comma", "Expected a comma");
    }
}

unit_static zap::parser::JsonValue parseNull(zap::parser::Iterator &it, const zap::parser::Iterator &end)
{
    if (std::distance(it, end) >= 4 && std::string(it, it + 4) == "null") {
        std::advance(it, 4);
        check_comma(it, end);
        return nullptr;
    }
    throw zap::exception::Error("zap::parser::parseNull", "Expected 'null'");
}

unit_static zap::parser::JsonValue parseBool(zap::parser::Iterator &it, const zap::parser::Iterator &end)
{
    if (std::distance(it, end) >= 4 && std::string(it, it + 4) == "true") {
        std::advance(it, 4);
        check_comma(it, end);
        return true;
    }
    if (std::distance(it, end) >= 5 && std::string(it, it + 5) == "false") {
        std::advance(it, 5);
        check_comma(it, end);
        return false;
    }
    throw zap::exception::Error("zap::parser::parseBool", "Expected 'true' or 'false'");
}

unit_static zap::parser::JsonValue parseNumber(zap::parser::Iterator &it, const zap::parser::Iterator &end)
{
    const zap::parser::Iterator start = it;
    bool isFloat = false;

    if (it != end && *it == '-') {
        ++it;
    }
    while (it != end && std::isdigit(*it)) {
        ++it;
    }
    if (it != end && *it == '.') {
        isFloat = true;
        ++it;
        while (it != end && std::isdigit(*it)) {
            ++it;
        }
    }
    check_comma(it, end);
    const std::string numStr(start, it);
    try {
        if (isFloat) {
            return std::stod(numStr);
        }
        return std::stoi(numStr);
    } catch (const std::invalid_argument &) {
        throw zap::exception::Error("zap::parser::parseNumber", "Invalid number");
    } catch (const std::out_of_range &) {
        throw zap::exception::Error("zap::parser::parseNumber", "Invalid number");
    }
}

unit_static zap::parser::JsonValue parseString(zap::parser::Iterator &it, const zap::parser::Iterator &end, const bool key = false)
{
    std::string result;
    bool terminated = false;

    expect(it, end, '"');
    while (it != end) {
        const char c = get(it, end);
        if (c == '"') {
            terminated = true;
            break;
        }
        if (c == '\\') {
            switch (get(it, end)) {
                case '\\':
                    result += '\\';
                    break;
                case 'b':
                    result += '\b';
                    break;
                case 'f':
                    result += '\f';
                    break;
                case 'n':
                    result += '\n';
                    break;
                case 'r':
                    result += '\r';
                    break;
                case 't':
                    result += '\t';
                    break;
                default:
                    throw zap::exception::Error("zap::parser::parseString", "Invalid escape sequence");
            }
        } else {
            result += c;
        }
    }
    if (!terminated) {
        throw zap::exception::Error("zap::parser::parseString", "Unterminated string");
    }
    if (!key) {
        check_comma(it, end);
    }
    return result;
}

unit_static zap::parser::JsonValue parseValue(zap::parser::Iterator &it, const zap::parser::Iterator &end);

unit_static zap::parser::JsonValue parseArray(zap::parser::Iterator &it,// NOLINT(*-no-recursion)
    const zap::parser::Iterator &end)
{
    std::vector<zap::parser::JsonProto> array;

    expect(it, end, '[');
    skipWhitespace(it, end);
    if (peek(it, end) == ']') {
        ++it;
        return nullptr;
    }
    while (true) {
        skipWhitespace(it, end);
        array.emplace_back(parseValue(it, end));
        skipWhitespace(it, end);
        if (peek(it, end) == ']') {
            ++it;
            break;
        }
    }
    check_comma(it, end);
    return array;
}

unit_static zap::parser::JsonValue parseObject(zap::parser::Iterator &it,// NOLINT(*-no-recursion)
    const zap::parser::Iterator &end)
{
    std::unordered_map<std::string, zap::parser::JsonProto> object;

    expect(it, end, '{');
    skipWhitespace(it, end);
    if (peek(it, end) == '}') {
        ++it;
        return nullptr;
    }
    while (true) {
        skipWhitespace(it, end);
        zap::parser::JsonValue key = parseString(it, end, true);
        if (std::get<std::string>(key).empty()) {
            throw zap::exception::Error("zap::parser::parseObject", "Expected string key");
        }
        skipWhitespace(it, end);
        expect(it, end, ':');
        skipWhitespace(it, end);
        object[std::get<std::string>(key)] = zap::parser::JsonProto(parseValue(it, end));
        skipWhitespace(it, end);
        if (peek(it, end) == '}') {
            ++it;
            break;
        }
    }
    check_comma(it, end);
    return object;
}

unit_static zap::parser::JsonValue parseValue(zap::parser::Iterator &it,// NOLINT(*-no-recursion)
    const zap::parser::Iterator &end)
{
    skipWhitespace(it, end);
    zap::parser::JsonValue object;

    if (char c = peek(it, end); std::isdigit(c)) {
        object = parseNumber(it, end);
    } else {
        switch (c) {
            case '"':
                object = parseString(it, end);
                break;
            case '-':
                object = parseNumber(it, end);
                break;
            case 'n':
                object = parseNull(it, end);
                break;
            case 't':
            case 'f':
                object = parseBool(it, end);
                break;
            case '[':
                object = parseArray(it, end);
                break;
            case '{':
                object = parseObject(it, end);
                break;
            default:
                throw zap::exception::Error("zap::parser::parseValue", "Unknown value");
        }
    }
    skipWhitespace(it, end);
    if (it != end && peek(it, end) == ',') {
        ++it;
    }
    return object;
}

#if defined(UNIT_TESTS)
};
#endif

zap::parser::JsonValue zap::parser::Jsonc(const char *RESTRICT filepath)
{
    std::stringstream ss;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw exception::Error("zap::parser::Jsonc", "Could not open ", filepath);
    }
    ss << file.rdbuf();
    const std::string content = ss.str();
    Iterator it = content.begin();
    const Iterator end = content.end();
    const JsonValue result = parseValue(it, end);
    skipWhitespace(it, end);
    if (it != end) {
        throw exception::Error("zap::parser::Jsonc", "Unexpected trailing data in ", filepath);
    }
    return result;
}
