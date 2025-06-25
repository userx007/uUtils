
#include "uBoolExprParserThrow.hpp"
#include <iostream>
#include <cassert>

void runTests()
{
    BoolExprParser parser;

    // Basic tests
    assert(parser.evaluate("TRUE") == true);
    assert(parser.evaluate("FALSE") == false);
    assert(parser.evaluate("!TRUE") == false);
    assert(parser.evaluate("!FALSE") == true);

    // AND tests
    assert(parser.evaluate("TRUE && FALSE") == false);
    assert(parser.evaluate("TRUE && TRUE") == true);
    assert(parser.evaluate("FALSE && FALSE") == false);
    assert(parser.evaluate("FALSE && TRUE") == false);

    // OR tests
    assert(parser.evaluate("TRUE || FALSE") == true);
    assert(parser.evaluate("FALSE || FALSE") == false);
    assert(parser.evaluate("TRUE || TRUE") == true);
    assert(parser.evaluate("FALSE || TRUE") == true);

    // Mixed tests
    assert(parser.evaluate("!TRUE || FALSE") == false);
    assert(parser.evaluate("TRUE && !FALSE") == true);
    assert(parser.evaluate("(TRUE && FALSE) || TRUE") == true);
    assert(parser.evaluate("!(TRUE || FALSE)") == false);
    assert(parser.evaluate("!(TRUE && FALSE)") == true);
    assert(parser.evaluate("(!TRUE && FALSE) || TRUE") == true);
    assert(parser.evaluate("((TRUE && FALSE) || (FALSE || TRUE)) && TRUE") == true);
    assert(parser.evaluate("!(!TRUE || FALSE)") == true);
    assert(parser.evaluate("TRUE || FALSE && FALSE") == true);
    assert(parser.evaluate("(((!FALSE))))") == true);

    // Invalid expression test
    try {
        parser.evaluate("TRUE && (FALSE || TRUE"); // Missing closing parenthesis
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected
    }


    std::cout << "All tests passed!" << std::endl;
}

int main()
{
    runTests();
    return 0;
}
