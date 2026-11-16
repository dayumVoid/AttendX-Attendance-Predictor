#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
protected:
    std::string name;
    int attended;
    int held;

public:
    Course(const std::string& name, int attended, int held);
    virtual ~Course();

    virtual std::string getType() const = 0;

    std::string getName() const;
    int getAttended() const;
    int getHeld() const;
    void markPresent(int count = 1);
    void markAbsent(int count = 1);
    double percentage() const;
};

#endif
