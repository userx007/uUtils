
#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>
#include <cmath>
#include "uCalculator.hpp"

void test_basic_arithmetic() {
    std::unordered_map<std::string, double> vars;
    Calculator calc1("2 + 3 * 4", vars);
    assert(calc1.evaluate() == 14);

    Calculator calc2("10 / 2 + 6", vars);
    assert(calc2.evaluate() == 11);

    Calculator calc3("8 - 3 * 2", vars);
    assert(calc3.evaluate() == 2);

    std::cout << "Basic arithmetic tests passed.\n";
}

void test_parentheses_and_order() {
    std::unordered_map<std::string, double> vars;
    Calculator calc("2 * (3 + 4)", vars);
    assert(calc.evaluate() == 14);

    Calculator calc2("(2 + 3) * (4 + 1)", vars);
    assert(calc2.evaluate() == 25);

    std::cout << "Parentheses and order tests passed.\n";
}

void test_functions() {
    std::unordered_map<std::string, double> vars;
    Calculator calc1("sqrt(16)", vars);
    assert(calc1.evaluate() == 4);

    Calculator calc2("sin(0)", vars);
    assert(calc2.evaluate() == 0);

    Calculator calc3("log(e)", vars);
    assert(std::abs(calc3.evaluate() - 1.0) < 1e-9);

    std::cout << "Function tests passed.\n";
}

void test_variables_and_assignment() {
    std::unordered_map<std::string, double> vars;
    Calculator calc1("x = 5", vars);
    assert(calc1.evaluate() == 5);
    assert(vars["x"] == 5);

    Calculator calc2("x * 2", vars);
    assert(calc2.evaluate() == 10);

    Calculator calc3("y = x + 3", vars);
    assert(calc3.evaluate() == 8);
    assert(vars["y"] == 8);

    std::cout << "Variable assignment and usage tests passed.\n";
}

void test_errors() {
    std::unordered_map<std::string, double> vars;
    try {
        Calculator calc("5 / 0", vars);
        calc.evaluate();
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected division by zero error.\n";
    }

    try {
        Calculator calc("unknownFunc(2)", vars);
        calc.evaluate();
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected unknown function error.\n";
    }

    try {
        Calculator calc("z + 2", vars);
        calc.evaluate();
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected undefined variable error.\n";
    }

    std::cout << "Error handling tests passed.\n";
}

void test_complex_expressions() {
    std::unordered_map<std::string, double> vars;

    Calculator c1("a = 3 + 4 * 2 / (1 - 5)^2", vars);
    assert(std::abs(c1.evaluate() - 3.5) < 1e-9);

    Calculator c2("b = sqrt(16) + log(e^2)", vars);
    assert(std::abs(c2.evaluate() - (4 + 2)) < 1e-9);

    Calculator c3("c = sin(pi / 2) + cos(0)", vars);
    assert(std::abs(c3.evaluate() - 2.0) < 1e-9);

    Calculator c4("d = (2 + 3) * (7 - 4)^2", vars);
    assert(std::abs(c4.evaluate() - 45.0) < 1e-9);

    Calculator c5("e = 2^3^2", vars); // 2^(3^2) = 2^9 = 512
    assert(std::abs(c5.evaluate() - 512.0) < 1e-9);

    Calculator c6("f = log10(1000) + log(e)", vars);
    assert(std::abs(c6.evaluate() - (3 + 1)) < 1e-9);

    Calculator c7("g = (1 + 2) * (3 + 4) / (5 - 2)", vars);
    assert(std::abs(c7.evaluate() - 7.0) < 1e-9);

    Calculator c8("h = sqrt((3 + 5)^2 + (12 - 4)^2)", vars); // sqrt(64 + 64) = sqrt(128)
    assert(std::abs(c8.evaluate() - std::sqrt(128)) < 1e-9);

    Calculator c9("i = (2 + 3 * (4 + 5)) / (7 - 2)", vars); // (2 + 3*9)/5 = 29/5
    assert(std::abs(c9.evaluate() - 5.8) < 1e-9);

    Calculator c10("j = (pi^2 + e^2) / (1 + sin(0))", vars);
    assert(std::abs(c10.evaluate() - ((M_PI * M_PI + M_E * M_E) / 1)) < 1e-9);

    std::cout << "Complex expression tests passed.\n";
}

int main() {
    test_basic_arithmetic();
    test_parentheses_and_order();
    test_functions();
    test_variables_and_assignment();
    test_errors();
    test_complex_expressions();
    std::cout << "All tests passed successfully.\n";
    return 0;
}

