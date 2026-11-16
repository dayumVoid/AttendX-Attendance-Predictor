#include "InputHelper.h"
#include <cstdlib>
#include <iostream>

namespace Input {

std::string readLine(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            std::exit(0);
        }
        if (!line.empty()) {
            return line;
        }
    }
}

int readInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::string line = readLine(prompt);
        try {
            size_t pos = 0;
            int value = std::stoi(line, &pos);
            if (pos == line.size() && value >= minValue && value <= maxValue) {
                return value;
            }
        } catch (...) {
        }
        std::cout << "Enter a number between " << minValue << " and " << maxValue << "\n";
    }
}

}
