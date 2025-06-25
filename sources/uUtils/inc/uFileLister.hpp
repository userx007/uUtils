#ifndef FILELISTER_H
#define FILELISTER_H

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <regex>
#include <iomanip> // Include for std::setw

namespace fs = std::filesystem;

class FileLister {
public:
    enum class SortCriteria {
        NAME,
        SIZE,
        TIME
    };

    FileLister(const std::string& directory) : directory_(directory) {}

    void listFiles(SortCriteria criteria) {
        std::vector<fs::directory_entry> files;
        for (const auto& entry : fs::directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                files.push_back(entry);
            }
        }

        switch (criteria) {
            case SortCriteria::NAME:
                std::sort(files.begin(), files.end(),
                          [](const fs::directory_entry& a, const fs::directory_entry& b) {
                              return a.path().filename() < b.path().filename();
                          });
                break;
            case SortCriteria::SIZE:
                std::sort(files.begin(), files.end(),
                          [](const fs::directory_entry& a, const fs::directory_entry& b) {
                              return fs::file_size(a) < fs::file_size(b);
                          });
                break;
            case SortCriteria::TIME:
                std::sort(files.begin(), files.end(),
                          [](const fs::directory_entry& a, const fs::directory_entry& b) {
                              return fs::last_write_time(a) < fs::last_write_time(b);
                          });
                break;
        }

        for (const auto& file : files) {
            auto ftime = fs::last_write_time(file);
            std::time_t cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));

            std::tm* tm = std::localtime(&cftime);

            char timebuf[20];
            std::strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);

            std::cout << std::setw(7) << fs::file_size(file) << " "
                      << timebuf << " "
                      << file.path().filename().string() << std::endl;
        }
    }


    // list files matching a regex
    void listFilesMatchingRegex(const std::regex& pattern, std::vector<std::string>& matchedFiles) const {
        for (const auto& entry : fs::directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (std::regex_match(filename, pattern)) {
                    matchedFiles.push_back(filename);
                }
            }
        }
    }

    // list files and extract part of filename using regex group
    void listFilesAndExtractGroup(const std::regex& pattern,
                                  std::vector<std::string>& matchedFiles,
                                  std::vector<std::string>& extractedParts) const {
        for (const auto& entry : fs::directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                std::smatch match;
                if (std::regex_match(filename, match, pattern)) {
                    matchedFiles.push_back(filename);
                    if (match.size() > 1) {
                        extractedParts.push_back(match[1].str());
                    } else {
                        extractedParts.push_back("");
                    }
                }
            }
        }
    }

private:
    std::string directory_;
};

#endif // FILELISTER_H
