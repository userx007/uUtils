
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "uStringUtils.hpp"

void test_trim()
{
    std::string input = "  Hello, World!  ";
    std::string expected = "Hello, World!";
    std::string result = ustring::trim(input);
    std::cout << "test_trim: " << (result == expected ? "Passed" : "Failed") << std::endl;
}

void test_trimInPlace()
{
    std::string input = "  Hello, World!  ";
    std::string expected = "Hello, World!";
    ustring::trimInPlace(input);
    std::cout << "test_trimInPlace: " << (input == expected ? "Passed" : "Failed") << std::endl;
}

void test_tolowercase()
{
    const std::string input = "Hello, World!";
    std::string expected = "hello, world!";
    std::string result = ustring::tolowercase(input);
    std::cout << "test_tolowercase: " << (result == expected ? "Passed" : "Failed") << std::endl;
}

void test_tolowercaseInPlace()
{
    std::string input = "Hello, World!";
    std::string expected = "hello, world!";
    ustring::tolowercase(input);
    std::cout << "test_tolowercaseInPlace: " << (input == expected ? "Passed" : "Failed") << std::endl;
}

void test_splitAtFirst_char()
{
    std::string input = "Hello, World!";
    char delimiter = ',';
    std::pair<std::string, std::string> expected = {"Hello", "World!"};
    std::pair<std::string, std::string> result;
    ustring::splitAtFirst(input, delimiter, result);
    std::cout << "test_splitAtFirst_char: " << ((result == expected) ? "Passed" : "Failed") << std::endl;
}

void test_splitAtFirst_string()
{
    std::string input = "Hello, World!";
    std::string delimiter = ", ";
    std::pair<std::string, std::string> expected = {"Hello", "World!"};
    std::pair<std::string, std::string> result;
    ustring::splitAtFirst(input, delimiter, result);
    std::cout << "test_splitAtFirst_string: " << ((result == expected) ? "Passed" : "Failed") << std::endl;
}

void test_tokenize_whitespace()
{
    std::string input = "Hello, World! This is a test.";
    std::vector<std::string> expected = {"Hello,", "World!", "This", "is", "a", "test."};
    std::vector<std::string> result;
    ustring::tokenize(input, result);
    std::cout << "test_tokenize_whitespace: " << ((result == expected) ? "Passed" : "Failed") << std::endl;
}

void test_tokenize_char()
{
    std::string input = "Hello,World!,This,is,a,test.";
    char delimiter = ',';
    std::vector<std::string> expected = {"Hello", "World!", "This", "is", "a", "test."};
    std::vector<std::string> result;
    ustring::tokenize(input, delimiter, result);
    std::cout << "test_tokenize_char: " << ((result == expected) ? "Passed" : "Failed") << std::endl;
}

void test_tokenize_string()
{
    std::string input = "Hello, World! This is a test.";
    std::string delimiter = " ";
    std::vector<std::string> expected = {"Hello,", "World!", "This", "is", "a", "test."};
    std::vector<std::string> result;
    ustring::tokenize(input, delimiter, result);
    std::cout << "test_tokenize_string: " << ((result == expected) ? "Passed" : "Failed") << std::endl;
}

void test_tokenize_multiple_delimiters()
{
    std::string input = "Hello, World! This is a test.";
    std::vector<std::string> delimiters = {", ", " "};
    std::vector<std::string> expected = {"Hello", "World!", "This", "is", "a", "test."};
    std::vector<std::string> result;
    ustring::tokenize(input, delimiters, result);
    std::cout << "test_tokenize_multiple_delimiters: " << ((result == expected) ? "Passed" : "Failed") << std::endl;
}

int main()
{
    test_trim();
    test_trimInPlace();
    test_tolowercase();
    test_tolowercaseInPlace();
    test_splitAtFirst_char();
    test_splitAtFirst_string();
    test_tokenize_whitespace();
    test_tokenize_char();
    test_tokenize_string();
    test_tokenize_multiple_delimiters();
    return 0;
}
