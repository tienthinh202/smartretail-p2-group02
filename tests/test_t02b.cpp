#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Rename the application's main so this file can have its own main.
#define main project_main
#include "../src/main.cpp"
#undef main

int main() {
    struct Test {
        std::string input;
        bool expectedReturn;
        int expectedMinutes;
        std::string expectedError;
    };

    const std::string lengthError =
        "Time must contain exactly 5 characters";
    const std::string formatError =
        "Time must use HH:MM format";
    const std::string digitError =
        "Hour and minute must contain only digits";
    const std::string hourError =
        "Hour must be between 00 and 23";
    const std::string minuteError =
        "Minute must be between 00 and 59";

    const std::vector<Test> tests = {
        {"00:00", true, 0, ""},
        {"09:05", true, 545, ""},
        {"12:30", true, 750, ""},
        {"23:59", true, 1439, ""},
        {"24:00", false, -1, hourError},
        {"00:60", false, -1, minuteError},
        {"25:61", false, -1, hourError},
        {"", false, -1, lengthError},
        {"9:05", false, -1, lengthError},
        {"09:050", false, -1, lengthError},
        {"09-05", false, -1, formatError},
        {"a9:05", false, -1, digitError},
        {"0a:05", false, -1, digitError},
        {"09:a5", false, -1, digitError},
        {"09:0a", false, -1, digitError},
        {" 9:05", false, -1, digitError},
        {"09:05 ", false, -1, lengthError}
    };

    std::size_t passed = 0;

    for (std::size_t i = 0; i < tests.size(); ++i) {
        const Test& test = tests[i];
        int minutes = -1;
        std::string error = "Previous error";

        bool result = toMinutes(test.input, minutes, error);

        bool ok = result == test.expectedReturn
               && minutes == test.expectedMinutes
               && error == test.expectedError;

        if (ok) {
            ++passed;
        }

        std::cout << "T02b-"
                  << std::setfill('0') << std::setw(2) << i + 1
                  << std::setfill(' ')
                  << " | input=" << std::quoted(test.input)
                  << " | return=" << std::boolalpha << result
                  << ", minutes=" << minutes
                  << ", error=" << std::quoted(error)
                  << " | " << (ok ? "PASS" : "FAIL")
                  << '\n';
    }

    std::cout << "\nResult: " << passed << "/"
              << tests.size() << " tests passed\n";

    return passed == tests.size() ? 0 : 1;
}
