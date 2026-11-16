#include "Storage.h"
#include "Lecture.h"
#include "Lab.h"
#include <fstream>
#include <sstream>
#include <vector>

Storage::Storage(const std::string& filename) : filename(filename) {}

bool Storage::save(const Student& student) const {
    std::ofstream out(filename);
    if (!out) {
        return false;
    }
    out << student.getName() << "|" << student.getRoll() << "\n";
    for (size_t i = 0; i < student.courseCount(); i++) {
        auto course = student.getCourse(i);
        out << course->getType() << "|" << course->getName() << "|"
            << course->getAttended() << "|" << course->getHeld() << "\n";
    }
    return true;
}

bool Storage::load(Student& student) const {
    std::ifstream in(filename);
    if (!in) {
        return false;
    }

    std::string line;
    if (!std::getline(in, line)) {
        return false;
    }

    std::stringstream header(line);
    std::string name;
    std::string roll;
    std::getline(header, name, '|');
    std::getline(header, roll, '|');
    student.setName(name);
    student.setRoll(roll);
    student.clearCourses();

    while (std::getline(in, line)) {
        std::stringstream row(line);
        std::string type;
        std::string courseName;
        std::string attendedText;
        std::string heldText;
        std::getline(row, type, '|');
        std::getline(row, courseName, '|');
        std::getline(row, attendedText, '|');
        std::getline(row, heldText, '|');

        try {
            int attended = std::stoi(attendedText);
            int held = std::stoi(heldText);
            if (type == "Lab") {
                student.addCourse(std::make_shared<Lab>(courseName, attended, held));
            } else {
                student.addCourse(std::make_shared<Lecture>(courseName, attended, held));
            }
        } catch (...) {
        }
    }
    return true;
}
