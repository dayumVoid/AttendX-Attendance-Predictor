#ifndef LAB_H
#define LAB_H

#include "Course.h"

class Lab : public Course {
public:
    Lab(const std::string& name, int attended, int held);
    std::string getType() const override;
};

#endif
