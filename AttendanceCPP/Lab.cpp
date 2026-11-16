#include "Lab.h"

Lab::Lab(const std::string& name, int attended, int held)
    : Course(name, attended, held) {}

std::string Lab::getType() const {
    return "Lab";
}
