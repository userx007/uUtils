
#include "uBoolExprParser.hpp"
#include <cassert>
#include <iostream>

void runTests()
{
    BoolExprParser parser;
    bool result;

    // Basic tests
    assert(parser.evaluate("TRUE", result) && result == true);
    assert(parser.evaluate("FALSE", result) && result == false);
    assert(parser.evaluate("!TRUE", result) && result == false);
    assert(parser.evaluate("!FALSE", result) && result == true);

    // Logical AND
    assert(parser.evaluate("TRUE && FALSE", result) && result == false);
    assert(parser.evaluate("TRUE && !FALSE", result) && result == true);

    // Logical OR
    assert(parser.evaluate("TRUE || FALSE", result) && result == true);
    assert(parser.evaluate("!TRUE || FALSE", result) && result == false);

    // Nested expressions
    assert(parser.evaluate("(TRUE && FALSE) || TRUE", result) && result == true);
    assert(parser.evaluate("((TRUE && FALSE) || (FALSE || TRUE)) && TRUE", result) && result == true);
    assert(parser.evaluate("!(!TRUE || FALSE)", result) && result == true);

    // Complex precedence
    assert(parser.evaluate("TRUE || FALSE && FALSE", result) && result == true);

    // Redundant parentheses
    assert(parser.evaluate("(((!FALSE))))", result) && result == true);

    // Invalid expression (should return false)
    assert(!parser.evaluate("TRUE && (FALSE || TRUE", result));

    std::cout << "All tests passed successfully." << std::endl;
}

int main()
{
    runTests();
    return 0;
}
