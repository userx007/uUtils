#ifndef UCALCULATOR_HPP
#define UCALCULATOR_HPP

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <unordered_map>

class Calculator
{
public:
    Calculator(const std::string& expr, std::unordered_map<std::string, double>& vars)
        : expression(expr), pos(0), variables(vars)
    {
        variables["pi"] = M_PI;
        variables["e"] = M_E;
    }

    double evaluate()
    {
        skipWhitespace();
        size_t assignPos = expression.find('=');
        if (assignPos != std::string::npos) {
            std::string varName = expression.substr(0, assignPos);
            expression = expression.substr(assignPos + 1);
            pos = 0;
            trim(varName);
            double value = parseExpression();
            variables[varName] = value;
            return value;
        } else {
            return parseExpression();
        }
    }

private:
    std::string expression;
    size_t pos;
    std::unordered_map<std::string, double>& variables;

    void skipWhitespace()
    {
        while (pos < expression.length() && isspace(expression[pos])) ++pos;
    }

    void trim(std::string& str)
    {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        str = str.substr(first, (last - first + 1));
    }

    double parseExpression()
    {
        double result = parseTerm();
        while (true) {
            skipWhitespace();
            if (pos < expression.length() && (expression[pos] == '+' || expression[pos] == '-')) {
                char op = expression[pos++];
                double term = parseTerm();
                result = (op == '+') ? result + term : result - term;
            } else {
                break;
            }
        }
        return result;
    }

    double parseTerm()
    {
        double result = parsePower();
        while (true) {
            skipWhitespace();
            if (pos < expression.length() && (expression[pos] == '*' || expression[pos] == '/')) {
                char op = expression[pos++];
                double factor = parsePower();
                result = (op == '*') ? result * factor : result / factor;
            } else {
                break;
            }
        }
        return result;
    }

    double parsePower()
    {
        double base = parseFactor();
        skipWhitespace();
        if (pos < expression.length() && expression[pos] == '^') {
            ++pos;
            double exponent = parsePower();  // right-associative
            return std::pow(base, exponent);
        }
        return base;
    }

    double parseFactor()
    {
        skipWhitespace();
        if (pos < expression.length() && expression[pos] == '(') {
            ++pos;
            double result = parseExpression();
            if (pos >= expression.length() || expression[pos] != ')') {
                throw std::runtime_error("Missing closing parenthesis");
            }
            ++pos;
            return result;
        } else if (isalpha(expression[pos])) {
            return parseFunctionOrVariable();
        } else {
            return parseNumber();
        }
    }

    double parseFunctionOrVariable()
    {
        std::string name;
        while (pos < expression.length() && (isalpha(expression[pos]) || expression[pos] == '_')) {
            name += expression[pos++];
        }

        skipWhitespace();
        if (pos < expression.length() && expression[pos] == '(') {
            ++pos;
            double arg = parseExpression();
            if (pos >= expression.length() || expression[pos] != ')') {
                throw std::runtime_error("Missing closing parenthesis after function argument");
            }
            ++pos;

            if (name == "sin") return std::sin(arg);
            if (name == "cos") return std::cos(arg);
            if (name == "tan") return std::tan(arg);
            if (name == "sqrt") return std::sqrt(arg);
            if (name == "log") return std::log(arg);
            if (name == "log10") return std::log10(arg);

            throw std::runtime_error("Unknown function: " + name);
        } else {
            if (variables.find(name) != variables.end()) {
                return variables[name];
            } else {
                throw std::runtime_error("Undefined variable: " + name);
            }
        }
    }

    double parseNumber()
    {
        skipWhitespace();
        size_t start = pos;
        while (pos < expression.length() && (isdigit(expression[pos]) || expression[pos] == '.')) ++pos;
        if (start == pos) {
            throw std::runtime_error("Expected number");
        }
        return std::stod(expression.substr(start, pos - start));
    }
};

#endif // UCALCULATOR_HPP

