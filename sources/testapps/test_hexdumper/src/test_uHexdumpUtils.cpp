
#include "uHexdumpUtils.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

// Helper function to generate test data
std::vector<uint8_t> generate_test_data(size_t size)
{
    std::vector<uint8_t> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = static_cast<uint8_t>(i % 256);
    }
    return data;
}

// Helper function to capture stdout
std::string capture_stdout(void (*func)(const uint8_t*, size_t, size_t, bool, bool, bool, bool), const uint8_t* data, size_t dataSize, size_t bytesPerLine, bool showSpaces, bool showAscii, bool showOffset, bool decimalOffset)
{
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    func(data, dataSize, bytesPerLine, showSpaces, showAscii, showOffset, decimalOffset);
    std::cout.rdbuf(oldCoutBuf);
    return oss.str();
}

// Test HexDump1 with direct parameters
void test_HexDump1_direct()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::string output = capture_stdout(hexutils::HexDump1, data.data(), data.size(), 16, true, true, true, false);
    std::cout << "HexDump1 (direct) Test Passed\n";
}

// Test HexDump1 with flag string
void test_HexDump1_flag()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    hexutils::HexDump1S(data.data(), data.size(), 16, "sao");
    std::cout.rdbuf(oldCoutBuf);
    std::string output = oss.str();
    std::cout << "HexDump1 (flag) Test Passed\n";
}

// Test HexDump1 with flag string
void test_HexDump11_flag()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    hexutils::HexDump1S(data.data(), data.size(), 16, "Sao");
    std::cout.rdbuf(oldCoutBuf);
    std::string output = oss.str();
    std::cout << "HexDump1 (flag) Test Passed\n";
}

// Test HexDump1 with flag string
void test_HexDump111_flag()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    hexutils::HexDump1S(data.data(), data.size(), 16, "SAo");
    std::cout.rdbuf(oldCoutBuf);
    std::string output = oss.str();
    std::cout << "HexDump1 (flag) Test Passed\n";
}


// Test HexDump1 with flag string
void test_HexDump1111_flag()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    hexutils::HexDump1S(data.data(), data.size(), 16, "SaO");
    std::cout.rdbuf(oldCoutBuf);
    std::string output = oss.str();
    std::cout << "HexDump1 (flag) Test Passed\n";
}



// Test HexDump2 with direct parameters
void test_HexDump2_direct()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::string output = capture_stdout(hexutils::HexDump2, data.data(), data.size(), 16, true, true, true, false);
    std::cout << "HexDump2 (direct) Test Passed\n";
}

// Test HexDump2 with flag string
void test_HexDump2_flag()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    hexutils::HexDump2S(data.data(), data.size(), 16, "sao");
    std::cout.rdbuf(oldCoutBuf);
    std::string output = oss.str();
    std::cout << "HexDump2S (flag) Test Passed\n";
}

// Test HexDump3 with direct parameters
void test_HexDump3_direct()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::string output = capture_stdout(hexutils::HexDump3, data.data(), data.size(), 16, true, true, true, false);
    std::cout << "HexDump3 (direct) Test Passed\n";
}

// Test HexDump3 with flag string
void test_HexDump3_flag()
{
    std::vector<uint8_t> data = generate_test_data(64);
    std::ostringstream oss;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(oss.rdbuf());
    hexutils::HexDump3S(data.data(), data.size(), 16, "sao");
    std::cout.rdbuf(oldCoutBuf);
    std::string output = oss.str();
    std::cout << "HexDump3S (flag) Test Passed\n";
}

int main()
{

    test_HexDump1_direct();
    test_HexDump1_flag();
    test_HexDump11_flag();
    test_HexDump111_flag();
    test_HexDump1111_flag();
    test_HexDump2_direct();
    test_HexDump2_flag();
    test_HexDump3_direct();
    test_HexDump3_flag();

    return 0;
}
