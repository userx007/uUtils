#include "uIniParserEx.hpp"
#include <iostream>
#include <cassert>
#include <unordered_map>

#define TEST_INI_FILE "testex.ini"

void testLoadFile()
{
    IniParserEx parser;
    assert(parser.load(TEST_INI_FILE) && "Failed to load test.ini");
    std::cout << "testLoadFile passed!\n";
}

void testBasicKeyValue()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    assert(parser.getValue("Common", "base") == "/usr/local");
    assert(parser.getValue("Common", "bin") == "/usr/local/bin");
    std::cout << "Basic key-value tests passed." << std::endl;
}

void testVariableSubstitution()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    assert(parser.getValue("Paths", "scripts") == "/usr/local/bin/scripts");
    assert(parser.getValue("Paths", "nested") == "/usr/local/bin/scripts/nested");
    std::cout << "Variable substitution tests passed." << std::endl;
}

void testCrossSectionReferences()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    assert(parser.getValue("Paths", "scripts") == "/usr/local/bin/scripts");
    assert(parser.getValue("Paths", "nested") == "/usr/local/bin/scripts/nested");
    std::cout << "Cross-section reference tests passed." << std::endl;
}

void testDefaultValue()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    assert(parser.getValue("Common", "nonexistent", "default") == "default");
    std::cout << "Default value tests passed." << std::endl;
}

void testSectionExists()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    assert(parser.sectionExists("Common"));
    assert(!parser.sectionExists("Nonexistent"));
    std::cout << "Section exists tests passed." << std::endl;
}

void testGetSection()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    std::unordered_map<std::string, std::string> section;
    assert(parser.getSection("Common", section));
    assert(section["base"] == "/usr/local");
    assert(section["bin"] == "/usr/local/bin");
    assert(!parser.getSection("Nonexistent", section));
    std::cout << "Get section tests passed." << std::endl;
}

void testGetResolvedSection()
{
    IniParserEx parser;
    parser.load(TEST_INI_FILE);
    std::unordered_map<std::string, std::string> resolved;

    assert(parser.getResolvedSection("Paths", resolved));
    assert(resolved["scripts"] == "/usr/local/bin/scripts");
    assert(resolved["nested"] == "/usr/local/bin/scripts/nested");

    assert(parser.getResolvedSection("Common", resolved));
    assert(resolved["base"] == "/usr/local");
    assert(resolved["bin"] == "/usr/local/bin");

    assert(!parser.getResolvedSection("Nonexistent", resolved));
    std::cout << "Get resolved section tests passed." << std::endl;
}

int main()
{
    testLoadFile();
    testBasicKeyValue();
    testVariableSubstitution();
    testCrossSectionReferences();
    testDefaultValue();
    testSectionExists();
    testGetSection();
    testGetResolvedSection();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
