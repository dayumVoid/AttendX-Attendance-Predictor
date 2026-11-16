#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include <memory>
#include <string>
#include <vector>

class Student {
private:
    std::string name;
    std::string roll;
    std::vector<std::shared_ptr<Course>> courses;

public:
    Student();

    void setName(const std::string& newName);
    void setRoll(const std::string& newRoll);
    std::string getName() const;
    std::string getRoll() const;

    void addCourse(std::shared_ptr<Course> course);
    void clearCourses();
    size_t courseCount() const;
    std::shared_ptr<Course> getCourse(size_t index) const;

    int totalAttended() const;
    int totalHeld() const;
};

#endif
