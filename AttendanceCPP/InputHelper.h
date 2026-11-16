#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <string>

namespace Input {
    std::string readLine(const std::string& prompt);
    int readInt(const std::string& prompt, int minValue, int maxValue);
}

#endif
