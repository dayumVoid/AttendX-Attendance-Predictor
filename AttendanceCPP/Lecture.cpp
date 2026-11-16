#include "Lecture.h"

Lecture::Lecture(const std::string& name, int attended, int held)
    : Course(name, attended, held) {}

std::string Lecture::getType() const {
    return "Lecture";
}
