
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "uHexlifyUtils.hpp"

void test_string_hexlify()
{
    std::vector<uint8_t> buffer = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    std::string hex;
    hexutils::string_hexlify(buffer, 0, buffer.size(), hex);
    std::string expected = "123456789ABCDEF0";
    std::cout << "Test string_hexlify: " << ((hex == expected) ? "Passed" : "Failed") << std::endl;
}

void test_string_unhexlify()
{
    std::string hex = "123456789ABCDEF0";
    std::vector<uint8_t> buffer;
    hexutils::string_unhexlify(hex, buffer);
    std::vector<uint8_t> expected = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    std::cout << "Test string_unhexlify: " << ((buffer == expected) ? "Passed" : "Failed") << std::endl;
}

void test_string_hexlify_any_little_endian()
{
    std::vector<uint32_t> buffer = {0x12345678, 0x9ABCDEF0};
    std::string hex;
    hexutils::string_hexlify_any(buffer, hex, hexutils::Endianness::Little);
    std::string expected = "4C78563412F0DEBC9A"; // 'L' marker for Little Endian
    std::cout << "Test string_hexlify_any (Little Endian): " << ((hex == expected) ? "Passed" : "Failed") << std::endl;
}

void test_string_unhexlify_any_little_endian()
{
    std::string hex = "4C78563412F0DEBC9A"; // 'L' marker for Little Endian
    std::vector<uint32_t> result;
    bool success = hexutils::string_unhexlify_any<uint32_t>(hex, result); // Explicit type
    std::vector<uint32_t> expected = {0x12345678, 0x9ABCDEF0};
    bool match = success && result.size() == expected.size() &&
                 std::memcmp(result.data(), expected.data(), result.size() * sizeof(uint32_t)) == 0;
    std::cout << "Test string_unhexlify_any (Little Endian): " << (match ? "Passed" : "Failed") << std::endl;
}

void test_string_hexlify_any_big_endian()
{
    std::vector<uint32_t> buffer = {0x12345678, 0x9ABCDEF0};
    std::string hex;
    hexutils::string_hexlify_any(buffer, hex, hexutils::Endianness::Big);
    std::string expected = "42123456789ABCDEF0"; // 'B' marker for Big Endian
    std::cout << "Test string_hexlify_any (Big Endian): " << ((hex == expected) ? "Passed" : "Failed") << std::endl;
}

void test_string_unhexlify_any_big_endian()
{
    std::string hex = "42123456789ABCDEF0"; // 'B' marker for Big Endian
    std::vector<uint32_t> result;
    bool success = hexutils::string_unhexlify_any<uint32_t>(hex, result); // Explicit type
    std::vector<uint32_t> expected = {0x12345678, 0x9ABCDEF0};
    bool match = success && result.size() == expected.size() &&
                 std::memcmp(result.data(), expected.data(), result.size() * sizeof(uint32_t)) == 0;
    std::cout << "Test string_unhexlify_any (Big Endian): " << (match ? "Passed" : "Failed") << std::endl;
}

int main()
{
    test_string_hexlify();
    test_string_unhexlify();
    test_string_hexlify_any_little_endian();
    test_string_unhexlify_any_little_endian();
    test_string_hexlify_any_big_endian();
    test_string_unhexlify_any_big_endian();
    return 0;
}
