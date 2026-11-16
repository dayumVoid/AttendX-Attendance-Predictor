#ifndef STORAGE_H
#define STORAGE_H

#include "Student.h"
#include <string>

class Storage {
private:
    std::string filename;

public:
    explicit Storage(const std::string& filename);

    bool save(const Student& student) const;
    bool load(Student& student) const;
};

#endif
