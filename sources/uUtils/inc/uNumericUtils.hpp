#ifndef UNUMERIC_UTILS_HPP
#define UNUMERIC_UTILS_HPP

#define UNUMERIC_USE_SSTREAM_FOR_FLOAT_CONVERSION 1U

#include <charconv>
#include <string>
#include <string_view>
#include <cstdint>
#include <cctype>
#include <algorithm>
#if (1 == UNUMERIC_USE_SSTREAM_FOR_FLOAT_CONVERSION)
    #include <sstream>
#endif /* (1 == UNUMERIC_USE_SSTREAM_FOR_FLOAT_CONVERSION) */


#ifdef NUMERIC_UTILS_LOGGING_ENABLED
    #include "uLogger.hpp"
    #define NU_LOG(SEVERITY, ...) LOG_PRINT(SEVERITY, __VA_ARGS__)
    #undef  LOG_HDR
    #define LOG_HDR     LOG_STRING("NUMERIC  :");
#else
    /* disable logging */
    #define NU_LOG(SEVERITY, ...)
#endif

/*--------------------------------------------------------------------------------------------------------*/
/**
 * @namespace numeric
 * @brief Provides utility functions for numeric conversions from strings.
 */
/*--------------------------------------------------------------------------------------------------------*/

namespace numeric
{

/*--------------------------------------------------------------------------------------------------------*/
/**
 * @namespace internal
 * @brief Contains internal helper functions for numeric.
 */
/*--------------------------------------------------------------------------------------------------------*/
namespace internal
{

/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Removes leading and trailing whitespace from a string.
 *
 * This internal utility function trims whitespace characters from both ends of the input string.
 * It is intended for internal use within the numeric namespace.
 *
 * @param str The input string to be trimmed.
 * @return A new string with leading and trailing whitespace removed.
 */
/*--------------------------------------------------------------------------------------------------------*/
inline std::string trim(const std::string& str)
{
    auto begin = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();

    return (begin < end) ? std::string(begin, end) : std::string();

}/* trim() */

} /* namespace internal */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Detects the numeric base from a string prefix and returns the base along with the stripped string.
 *
 * This function examines the beginning of the input string to determine if it has a base prefix:
 * - "0x" or "0X" for hexadecimal (base 16)
 * - "0b" or "0B" for binary (base 2)
 * - A leading "0" followed by digits for octal (base 8)
 * If no prefix is found, base 10 is assumed.
 *
 * @param input The input string potentially containing a base prefix.
 * @return A pair consisting of the detected base and the string view with the prefix removed.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline std::pair<int, std::string_view> detect_base_and_strip_prefix(const std::string& input)
{
    std::string_view view = input;
    int base = 10;
    if (view.size() > 2 && view[0] == '0') {
        if (view[1] == 'x' || view[1] == 'X') {
            base = 16;
            view.remove_prefix(2);
        } else if (view[1] == 'b' || view[1] == 'B') {
            base = 2;
            view.remove_prefix(2);
        } else if (std::isdigit(view[1])) {
            base = 8;
            view.remove_prefix(1);
        }
    }

    return {base, view};

} /* detect_base_and_strip_prefix() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a signed integer of type T.
 *
 * This function trims the input string, detects the numeric base from any prefix,
 * and attempts to convert the string to a signed integer using `std::from_chars`.
 * It logs errors if the input is invalid or out of range.
 *
 * @tparam T A signed integer type (e.g., int8_t, int32_t).
 * @param input The input string to convert.
 * @param output Reference to the variable where the result will be stored.
 * @return True if the conversion was successful, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

template<typename T>
bool string_to_signed(const std::string& input, T& output)
{
    bool bRetVal = false;

    // Single-pass loop for structured early exits
    do {
        std::string trimmed = internal::trim(input);
        if (trimmed.empty()) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Input is empty"));
            break;
        }

        auto [base, view] = detect_base_and_strip_prefix(trimmed);
        auto [ptr, ec] = std::from_chars(view.data(), view.data() + view.size(), output, base);
        if (ec == std::errc()) {
            bRetVal = true;
            break;
        }

        if (ec == std::errc::invalid_argument) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid format:"); LOG_STRING(input));
            break;
        }

        if (ec == std::errc::result_out_of_range) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Value out of range:"); LOG_STRING(input));
            break;
        }

        NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid number:"); LOG_STRING(input));

    } while (false);

    return bRetVal;

} /* string_to_signed() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to an unsigned integer of type T.
 *
 * This function trims the input string, detects the numeric base from any prefix
 * (e.g., "0x" for hex, "0b" for binary, "0" for octal), and attempts to convert
 * the string to an unsigned integer using `std::from_chars`.
 * It logs detailed error messages if the input is invalid or out of range.
 *
 * @tparam T An unsigned integer type (e.g., uint8_t, uint32_t).
 * @param input The input string to convert.
 * @param output Reference to the variable where the result will be stored.
 * @return True if the conversion was successful, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

template<typename T>
bool string_to_unsigned(const std::string& input, T& output)
{
    bool bRetVal = false;

    // Single-pass loop for structured early exits
    do {
        std::string trimmed = internal::trim(input);
        if (trimmed.empty()) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Input is empty"));
            break;
        }

        auto [base, view] = detect_base_and_strip_prefix(trimmed);
        auto [ptr, ec] = std::from_chars(view.data(), view.data() + view.size(), output, base);
        if (ec == std::errc()) {
            bRetVal = true;
            break;
        }

        if (ec == std::errc::invalid_argument) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid format:"); LOG_STRING(input));
            break;
        }

        if (ec == std::errc::result_out_of_range) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Value out of range:"); LOG_STRING(input));
            break;
        }

        NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid number:"); LOG_STRING(input));

    } while (false);

    return bRetVal;
} /* string_to_unsigned() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a floating-point number of type T.
 *
 * This function trims the input string and attempts to convert it to a floating-point
 * value using `std::from_chars`. It supports types like `float`, `double`, and `long double`.
 * Logs detailed error messages if the input is invalid or out of range.
 *
 * @tparam T A floating-point type (e.g., float, double, long double).
 * @param input The input string to convert.
 * @param output Reference to the variable where the result will be stored.
 * @return True if the conversion was successful, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

#if (1 == UNUMERIC_USE_SSTREAM_FOR_FLOAT_CONVERSION)

template<typename T>
bool string_to_floating(const std::string& input, T& output)
{
    bool bRetVal = false;

    do {
        std::string trimmed = internal::trim(input);
        if (trimmed.empty()) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Input is empty"));
            break;
        }

        std::istringstream iss(trimmed);
        iss >> output;

        if (iss.fail() || !iss.eof()) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid format or extra characters:"); LOG_STRING(input));
            break;
        }

        bRetVal = true;

    } while (false);

    return bRetVal;
}

#else

template<typename T>
bool string_to_floating(const std::string& input, T& output)
{
    bool bRetVal = false;

    // Single-pass loop for structured early exits
    do {
        std::string trimmed = internal::trim(input);
        if (trimmed.empty()) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Input is empty"));
            break;
        }

        auto [ptr, ec] = std::from_chars(trimmed.data(), trimmed.data() + trimmed.size(), output);
        if (ec == std::errc()) {
            bRetVal = true;
            break;
        }

        if (ec == std::errc::invalid_argument) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid format:"); LOG_STRING(input));
            break;
        }

        if (ec == std::errc::result_out_of_range) {
            NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Value out of range:"); LOG_STRING(input));
            break;
        }

        NU_LOG(LOG_ERROR, LOG_HDR; LOG_STRING("Invalid number:"); LOG_STRING(input));

    } while (false);

    return bRetVal;

} /* string_to_floating() */

#endif /* (1 == UNUMERIC_USE_SSTREAM_FOR_FLOAT_CONVERSION) */

/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to an int8_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2int8(const std::string& s, int8_t& out)
{
    return string_to_signed<int8_t>(s, out);

} /* str2int8() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to an int16_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2int16(const std::string& s, int16_t& out)
{
    return string_to_signed<int16_t>(s, out);

} /* str2int16() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to an int32_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2int32(const std::string& s, int32_t& out)
{
    return string_to_signed<int32_t>(s, out);

} /* str2int32() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to an int64_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2int64(const std::string& s, int64_t& out)
{
    return string_to_signed<int64_t>(s, out);

} /* str2int64() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a uint8_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2uint8(const std::string& s, uint8_t& out)
{
    return string_to_unsigned<uint8_t>(s, out);

} /* str2uint8() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a uint16_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2uint16(const std::string& s, uint16_t& out)
{
    return string_to_unsigned<uint16_t>(s, out);

} /* str2uint16() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a uint32_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2uint32(const std::string& s, uint32_t& out)
{
    return string_to_unsigned<uint32_t>(s, out);

} /* str2uint32() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a uint64_t value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2uint64(const std::string& s, uint64_t& out)
{
    return string_to_unsigned<uint64_t>(s, out);

} /* str2uint64() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a float value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2float(const std::string& s, float& out)
{
    return string_to_floating<float>(s, out);

} /* str2float() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a double value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2double(const std::string& s, double& out)
{
    return string_to_floating<double>(s, out);

} /* str2double() */



/*--------------------------------------------------------------------------------------------------------*/
/**
 * @brief Converts a string to a long double value.
 * @param s The input string.
 * @param out Reference to the output variable.
 * @return True if conversion succeeds, false otherwise.
 */
/*--------------------------------------------------------------------------------------------------------*/

inline bool str2long_double(const std::string& s, long double& out)
{
    return string_to_floating<long double>(s, out);

} /* str2long_double() */


} // namespace numeric

#endif // UNUMERIC_UTILS_HPP
