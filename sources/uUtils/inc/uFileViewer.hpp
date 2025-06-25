#ifndef UFILE_VIEWER_HPP
#define UFILE_VIEWER_HPP

#include "uFlagParser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstddef>
#include <cctype>


#define uHEXDUMP_USE_COLORS   1U

#if (1 == uHEXDUMP_USE_COLORS)
#define uHEXDUMP_ERROR_COLOR   "\033[91m"    // Bright Red
#define uHEXDUMP_OFFSET_COLOR  "\033[92m"    // Bright Green
#define uHEXDUMP_HEX_COLOR     "\033[96m"    // Bright Cyan
#define uHEXDUMP_ASCII_COLOR   "\033[97m"    // Bright White
#define uHEXDUMP_RESET_COLOR   "\033[0m"     // Reset to default
#else
#define uHEXDUMP_OFFSET_COLOR  ""
#define uHEXDUMP_HEX_COLOR     ""
#define uHEXDUMP_ASCII_COLOR   ""
#define uHEXDUMP_RESET_COLOR   ""
#endif // (1 == uHEXDUMP_USE_COLORS)

/**
 * Concatenates two arguments and appends a reset color code for formatted output.
 */
#define FRMT(a, b) a b uHEXDUMP_RESET_COLOR

class uFileViewer
{
    public:

        explicit uFileViewer(const std::string& filename )
        : m_File(filename, std::ios::binary)
        {
            if (!m_File) {
                std::printf(FRMT(uHEXDUMP_ERROR_COLOR, "Error: Could not open file: %s\n"), filename.c_str());
                m_bValid = false;
            }
        }

        ~uFileViewer()
        {
            if (m_File.is_open()) {
                m_File.close();
            }
        }

        void show() const
        {
            if (!m_bValid) return;

            std::string line;
            while (std::getline(m_File, line)) {
                std::printf(FRMT(uHEXDUMP_ASCII_COLOR, "%s\n"), line.c_str());
            }
        }

        void showhex(std::size_t szBytesPerLine = 16, const std::string& flagString = "", std::size_t szShowOffset = 0, std::size_t szChunkSize = 1024 )
        {
            if (!m_bValid) return;

            m_File.clear(); // Clear any error flags
            m_File.seekg(szShowOffset, std::ios::beg);

            bool bShowSpaces = true;
            bool bShowAscii = true;
            bool bShowOffset = true;
            bool bDecimalOffset = false;

            if(!flagString.empty()) {
                try {
                    FlagParser flags(flagString);

                    if (flagString.find_first_of("sS") != std::string::npos)
                        bShowSpaces = flags.get_flag('S');
                    if (flagString.find_first_of("aA") != std::string::npos)
                        bShowAscii = flags.get_flag('A');
                    if (flagString.find_first_of("oO") != std::string::npos)
                        bShowOffset = flags.get_flag('O');
                    if (flagString.find_first_of("dD") != std::string::npos)
                        bDecimalOffset = flags.get_flag('D');
                } catch (const std::exception& e) {
                    std::printf(FRMT(uHEXDUMP_ERROR_COLOR, "Error: Invalid flag string: %s\n"), e.what());
                    return;
                }
            }

            std::vector<char> buffer(szChunkSize);
            size_t szCrtOffset = 0;

            while (m_File) {
                m_File.read(buffer.data(), szChunkSize);
                std::streamsize bytesRead = m_File.gcount();
                if (bytesRead > 0) {
                    buffer.resize(static_cast<size_t>(bytesRead)); // Resize buffer to actual bytes read
                    m_HexDumpSection(buffer, szCrtOffset, szBytesPerLine, bShowSpaces, bShowAscii, bShowOffset, bDecimalOffset);
                    szCrtOffset += static_cast<size_t>(bytesRead);
                }
            }
        }

    private:

        void m_HexDumpSection(const std::vector<char>& data, size_t szCrtOffset, size_t szBytesPerLine = 16, bool bShowSpaces = true, bool bShowAscii = true, bool bShowOffset = true, bool bDecimalOffset = false)
        {
            if (szBytesPerLine > 96) {
                szBytesPerLine = 96;
            }

            size_t szOffset =szCrtOffset;
            size_t szDataSize = data.size();
            size_t szLines = szDataSize / szBytesPerLine;
            size_t szLastLineLen = szDataSize % szBytesPerLine;

            if (szLastLineLen != 0) ++szLines;

            char buffer[288];  // Shared buffer for all sections max 96

            for (size_t i = 0; i < szLines; ++i) {
                size_t szLineStart = i * szBytesPerLine;
                size_t szLineLen = (i == szLines - 1 && szLastLineLen != 0) ? szLastLineLen : szBytesPerLine;

                /*  Offset */
                if (bShowOffset) {
                    if (bDecimalOffset) {
                        snprintf(buffer, sizeof(buffer), "%08zu | ", szOffset + szLineStart);
                    } else {
                        snprintf(buffer, sizeof(buffer), "%08zX | ", szOffset + szLineStart);
                    }
                    std::printf(FRMT(uHEXDUMP_OFFSET_COLOR, "%s"), buffer);
                }

                /* Hex values */
                size_t pos = 0;
                for (size_t j = 0; j < szBytesPerLine; ++j) {
                    if (j < szLineLen) {
                        pos += snprintf(buffer + pos, sizeof(buffer) - pos, bShowSpaces ? "%02X " : "%02X", static_cast<unsigned char>(data[szLineStart + j]));
                    } else {
                        pos += snprintf(buffer + pos, sizeof(buffer) - pos, bShowSpaces ? "   " : "  ");
                    }
                }
                std::printf(FRMT(uHEXDUMP_HEX_COLOR, "%s"), buffer);

                /* ASCII characters */
                if (bShowAscii) {
                    pos = 0;
                    pos += snprintf(buffer + pos, sizeof(buffer) - pos, " | ");
                    for (size_t j = 0; j < szLineLen; ++j) {
                        uint8_t ch = static_cast<unsigned char>(data[szLineStart + j]);
                        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "%c", isprint(ch) ? ch : '.');
                    }
                    std::printf(FRMT(uHEXDUMP_ASCII_COLOR, "%s"), buffer);
                }

                std::printf("\n");
            }
        }

        mutable std::ifstream m_File;
        bool m_bValid = true;

};

#endif // UFILE_VIEWER_HPP


