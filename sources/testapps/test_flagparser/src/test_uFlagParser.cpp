
#include <iostream>
#include <stdexcept>
#include "uFlagParser.hpp"

void test_valid_flag_string()
{
    try {
        FlagParser parser("aBcD");
        std::cout << "test_valid_flag_string: Passed" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "test_valid_flag_string: Failed - " << e.what() << std::endl;
    }
}

void test_invalid_flag_string()
{
    try {
        FlagParser parser("aBcDd");
        std::cout << "test_invalid_flag_string: Failed" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "test_invalid_flag_string: Passed - " << e.what() << std::endl;
    }
}

void test_get_flag_uppercase()
{
    FlagParser parser("aBcD");
    bool result = parser.get_flag('B');
    std::cout << "test_get_flag_uppercase: " << (result ? "Passed" : "Failed") << std::endl;
}

void test_get_flag_lowercase()
{
    FlagParser parser("aBcD");
    bool result = parser.get_flag('c');
    std::cout << "test_get_flag_lowercase: " << (!result ? "Passed" : "Failed") << std::endl;
}

void test_get_flag_missing()
{
    FlagParser parser("aBcD");
    bool result = parser.get_flag('e');
    std::cout << "test_get_flag_missing: " << (!result ? "Passed" : "Failed") << std::endl;
}

void test_uppercase_flag()
{
    FlagParser parser("AB");
    bool resultA = parser.get_flag('a');
    bool resultB = parser.get_flag('b');
    std::cout << "test_uppercase_flag: " << (resultA && resultB ? "Passed" : "Failed") << std::endl;
}

void test_lowercase_flag()
{
    FlagParser parser("ab");
    bool resultA = parser.get_flag('a');
    bool resultB = parser.get_flag('b');
    std::cout << "test_lowercase_flag: " << (!resultA && !resultB ? "Passed" : "Failed") << std::endl;
}

void test_missing_flag()
{
    FlagParser parser("aB");
    bool result = parser.get_flag('z');
    std::cout << "test_missing_flag: " << (!result ? "Passed" : "Failed") << std::endl;
}

void test_conflicting_flags()
{
    try {
        FlagParser parser("aA");
        std::cout << "test_conflicting_flags: Failed" << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "test_conflicting_flags: Passed" << std::endl;
    }
}

void test_case_insensitive_query()
{
    FlagParser parser("A");
    bool resultLower = parser.get_flag('a');
    bool resultUpper = parser.get_flag('A');
    std::cout << "test_case_insensitive_query: " << (resultLower && resultUpper ? "Passed" : "Failed") << std::endl;
}

int main()
{
    test_valid_flag_string();
    test_invalid_flag_string();
    test_get_flag_uppercase();
    test_get_flag_lowercase();
    test_get_flag_missing();
    test_uppercase_flag();
    test_lowercase_flag();
    test_missing_flag();
    test_conflicting_flags();
    test_case_insensitive_query();
    return 0;
}
