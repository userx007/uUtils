#include "uCalculator.hpp"

#include <iostream>
#include <unordered_map>


int main() {
    std::unordered_map<std::string, double> variables;
    std::string input;

    std::cout << "Enter expressions (e.g., x = 5, 2 * x + sqrt(9), pi^2). Type 'exit' to quit.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "") {
            continue; // skip new lines
        } else if (input == "vars") {
            if(!variables.empty()) {
                std::cout << "variables:" << std::endl;
                std::for_each(variables.begin(), variables.end(),
                    [](const auto& item) {
                        std::cout << "\t" << item.first << " : " << item.second << std::endl;
                    });
            }

        } else if (input == "clear") {
            if(!variables.empty()) {
                variables.clear();
            }

        } else if (input == "exit") {
            break;

        } else {
            try {
                Calculator calc(input, variables);
                double result = calc.evaluate();
                std::cout << "\tResult: " << result << std::endl;
            } catch (const std::exception& ex) {
                std::cerr << "\tError: " << ex.what() << std::endl;
            }
        }
    }

    return 0;
}
