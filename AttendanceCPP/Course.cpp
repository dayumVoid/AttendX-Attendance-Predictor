#include "Course.h"
#include <stdexcept>

Course::Course(const std::string& name, int attended, int held)
    : name(name), attended(attended), held(held) {
    if (attended < 0 || held < 0 || attended > held) {
        throw std::invalid_argument("Invalid attendance numbers");
    }
}

Course::~Course() {}

std::string Course::getName() const {
    return name;
}

int Course::getAttended() const {
    return attended;
}

int Course::getHeld() const {
    return held;
}

void Course::markPresent(int count) {
    attended += count;
    held += count;
}

void Course::markAbsent(int count) {
    held += count;
}

double Course::percentage() const {
    if (held == 0) {
        return 0.0;
    }
    return 100.0 * attended / held;
}
