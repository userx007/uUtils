
#include <iostream>
#include <string>
#include <limits>
#include "uNumericUtils.hpp"

void test_string_to_signed()
{
    int32_t result;
    std::string input;

    // Valid cases
    input = "123";
    if (numeric::string_to_signed(input, result) && result == 123) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "-123";
    if (numeric::string_to_signed(input, result) && result == -123) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "0x7B";
    if (numeric::string_to_signed(input, result) && result == 123) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    // Invalid cases
    input = "abc";
    if (!numeric::string_to_signed(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "";
    if (!numeric::string_to_signed(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }
}

void test_string_to_unsigned()
{
    uint32_t result;
    std::string input;

    // Valid cases
    input = "123";
    if (numeric::string_to_unsigned(input, result) && result == 123) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "0x7B";
    if (numeric::string_to_unsigned(input, result) && result == 123) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    // Invalid cases
    input = "-123";
    if (!numeric::string_to_unsigned(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "abc";
    if (!numeric::string_to_unsigned(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "";
    if (!numeric::string_to_unsigned(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }
}

void test_string_to_floating()
{
    double result;
    std::string input;

    // Valid cases
    input = "123.456";
    if (numeric::string_to_floating(input, result) && result == 123.456) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "-123.456";
    if (numeric::string_to_floating(input, result) && result == -123.456) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    // Invalid cases
    input = "abc";
    if (!numeric::string_to_floating(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "";
    if (!numeric::string_to_floating(input, result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }
}

void test_str2int()
{
    int8_t int8_result;
    int16_t int16_result;
    int32_t int32_result;
    int64_t int64_result;
    std::string input;

    // Valid cases
    input = "127";
    if (numeric::str2int8(input, int8_result) && int8_result == 127) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "32767";
    if (numeric::str2int16(input, int16_result) && int16_result == 32767) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "2147483647";
    if (numeric::str2int32(input, int32_result) && int32_result == 2147483647) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "9223372036854775807";
    if (numeric::str2int64(input, int64_result) && int64_result == 9223372036854775807) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    // Invalid cases
    input = "128";
    if (!numeric::str2int8(input, int8_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "32768";
    if (!numeric::str2int16(input, int16_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "2147483648";
    if (!numeric::str2int32(input, int32_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "9223372036854775808";
    if (!numeric::str2int64(input, int64_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }
}

void test_str2uint()
{
    uint8_t uint8_result;
    uint16_t uint16_result;
    uint32_t uint32_result;
    uint64_t uint64_result;
    std::string input;

    // Valid cases
    input = "255";
    if (numeric::str2uint8(input, uint8_result) && uint8_result == 255) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "65535";
    if (numeric::str2uint16(input, uint16_result) && uint16_result == 65535) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "4294967295";
    if (numeric::str2uint32(input, uint32_result) && uint32_result == 4294967295) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "18446744073709551615";
    if (numeric::str2uint64(input, uint64_result) && uint64_result == 18446744073709551615U) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    // Invalid cases
    input = "256";
    if (!numeric::str2uint8(input, uint8_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "65536";
    if (!numeric::str2uint16(input, uint16_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "4294967296";
    if (!numeric::str2uint32(input, uint32_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "18446744073709551616";
    if (!numeric::str2uint64(input, uint64_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }
}

void test_str2float()
{
    float float_result;
    double double_result;
    long double long_double_result;
    std::string input;

    // Valid cases
    input = "123.456";
    if (numeric::str2float(input, float_result) && float_result == 123.456f) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "123.456";
    if (numeric::str2double(input, double_result) && double_result == 123.456) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "123.456";
    if (numeric::str2long_double(input, long_double_result) && long_double_result == 123.456L) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    // Invalid cases
    input = "abc";
    if (!numeric::str2float(input, float_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "abc";
    if (!numeric::str2double(input, double_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }

    input = "abc";
    if (!numeric::str2long_double(input, long_double_result)) {
        std::cout << "Passed: " << input << std::endl;
    } else {
        std::cout << "Failed: " << input << std::endl;
    }
}

int main()
{
    test_string_to_signed();
    test_string_to_unsigned();
    test_string_to_floating();
    test_str2int();
    test_str2uint();
    test_str2float();

    return 0;
}
