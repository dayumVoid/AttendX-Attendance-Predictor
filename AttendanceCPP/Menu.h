#ifndef MENU_H
#define MENU_H

#include "Predictor.h"
#include "Storage.h"
#include "Student.h"
#include <memory>

class Menu {
private:
    Student student;
    Storage storage;
    Predictor predictor;

    void setupStudent();
    void printMenu() const;
    void addCourse();
    void updateAttendance();
    void showSummary() const;
    void showPrediction() const;
    void showForecast() const;
    void saveData() const;
    std::shared_ptr<Course> selectCourse() const;

public:
    Menu();
    void run();
};

#endif
