#ifndef BOOLEAN_EXPRESSION_PARSER_HPP
#define BOOLEAN_EXPRESSION_PARSER_HPP

#include <string_view>
#include <stdexcept>
#include <cctype>

class BoolExprParser
{
public:

    constexpr bool evaluate(std::string_view input) const
    {
        return parseExpression(input);
    }

private:

    constexpr bool parseExpression(std::string_view& expr) const
    {
        bool value = parseTerm(expr);
        while (true) {
            skipWhitespace(expr);
            if (expr.starts_with("||")) {
                expr.remove_prefix(2);
                value = value || parseTerm(expr);
            } else {
                break;
            }
        }
        return value;
    }

    constexpr bool parseTerm(std::string_view& expr) const
    {
        bool value = parseFactor(expr);
        while (true) {
            skipWhitespace(expr);
            if (expr.starts_with("&&")) {
                expr.remove_prefix(2);
                value = value && parseFactor(expr);
            } else {
                break;
            }
        }
        return value;
    }

    constexpr bool parseFactor(std::string_view& expr) const
    {
        skipWhitespace(expr);
        if (expr.starts_with("!")) {
            expr.remove_prefix(1);
            return !parseFactor(expr);
        }
        if (expr.starts_with("(")) {
            expr.remove_prefix(1);
            bool value = parseExpression(expr);
            skipWhitespace(expr);
            if (!expr.starts_with(")")) {
                throw std::invalid_argument("Mismatched parentheses");
            }
            expr.remove_prefix(1);
            return value;
        }
        if (expr.starts_with("TRUE")) {
            expr.remove_prefix(4);
            return true;
        }
        if (expr.starts_with("FALSE")) {
            expr.remove_prefix(5);
            return false;
        }
        throw std::invalid_argument("Unexpected token in factor");
    }

    constexpr void skipWhitespace(std::string_view& expr) const
    {
        while (!expr.empty() && std::isspace(static_cast<unsigned char>(expr.front()))) {
            expr.remove_prefix(1);
        }
    }
};

#endif // BOOLEAN_EXPRESSION_PARSER_HPP
