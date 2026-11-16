#ifndef LECTURE_H
#define LECTURE_H

#include "Course.h"

class Lecture : public Course {
public:
    Lecture(const std::string& name, int attended, int held);
    std::string getType() const override;
};

#endif
