#include "uIniParser.hpp"

#include <iostream>
#include <map>
#include <cassert>

void testLoadFile()
{
    IniParser parser;
    assert(parser.load("test.ini") && "Failed to load test.ini");
    std::cout << "testLoadFile passed!\n";
}

void testGetValue()
{
    IniParser parser;
    parser.load("test.ini");

    assert(parser.getValue("Common", "Version") == "1.0.5");
    assert(parser.getValue("Common", "Author") == "John Doe");
    assert(parser.getValue("Script", "Path") == "/usr/local/scripts/start.sh");
    assert(parser.getValue("Plugin1", "Enabled") == "true");
    assert(parser.getValue("Plugin1", "Timeout") == "500");

    std::cout << "testGetValue passed!\n";
}

void testMissingValue()
{
    IniParser parser;
    parser.load("test.ini");

    assert(parser.getValue("Plugin1", "NonExistentKey", "DefaultVal") == "DefaultVal");
    std::cout << "testMissingValue passed!\n";
}

void testGetSection()
{
    IniParser parser;
    parser.load("test.ini");

    std::map<std::string, std::string> pluginData;
    assert(parser.getSection("Plugin1", pluginData));
    assert(pluginData["Enabled"] == "true");
    assert(pluginData["Timeout"] == "500");

    std::map<std::string, std::string> emptySection;
    assert(parser.getSection("EmptySection", emptySection));
    assert(emptySection.empty());

    std::map<std::string, std::string> missingData;
    assert(!parser.getSection("NonExistent", missingData));
    assert(missingData.empty());

    std::cout << "testGetSection passed!\n";
}

void testSectionExists()
{
    IniParser parser;
    parser.load("test.ini");

    assert(parser.sectionExists("Common"));
    assert(!parser.sectionExists("NonExistent"));

    std::cout << "testSectionExists passed!\n";
}

int main()
{
    testLoadFile();
    testGetValue();
    testMissingValue();
    testGetSection();
    testSectionExists();

    std::cout << "All tests passed successfully!\n";
    return 0;
}
