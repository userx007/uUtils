#include "uFileLister.hpp"

#include <iostream>
#include <vector>
#include <regex>

int main() {
    std::string testDir = "."; // Use the current directory for testing

    // Create FileLister instance
    FileLister lister(testDir);

    std::cout << "Listing files sorted by name:\n";
    lister.listFiles(FileLister::SortCriteria::NAME);

    std::cout << "\nListing files sorted by size:\n";
    lister.listFiles(FileLister::SortCriteria::SIZE);

    std::cout << "\nListing files sorted by modification time:\n";
    lister.listFiles(FileLister::SortCriteria::TIME);

    // Test regex matching
    std::cout << "\nListing files matching regex pattern: .*\\.txt\n";
    std::regex pattern(".*\\.txt");
    std::vector<std::string> matchedFiles;
    lister.listFilesMatchingRegex(pattern, matchedFiles);

    for (const auto& file : matchedFiles) {
        std::cout << file << std::endl;
    }

    return 0;
}
