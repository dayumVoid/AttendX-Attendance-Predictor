#include "Student.h"

Student::Student() : name(""), roll("") {}

void Student::setName(const std::string& newName) {
    name = newName;
}

void Student::setRoll(const std::string& newRoll) {
    roll = newRoll;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getRoll() const {
    return roll;
}

void Student::addCourse(std::shared_ptr<Course> course) {
    courses.push_back(course);
}

void Student::clearCourses() {
    courses.clear();
}

size_t Student::courseCount() const {
    return courses.size();
}

std::shared_ptr<Course> Student::getCourse(size_t index) const {
    return courses.at(index);
}

int Student::totalAttended() const {
    int sum = 0;
    for (const auto& course : courses) {
        sum += course->getAttended();
    }
    return sum;
}

int Student::totalHeld() const {
    int sum = 0;
    for (const auto& course : courses) {
        sum += course->getHeld();
    }
    return sum;
}
