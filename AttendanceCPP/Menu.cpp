#include "Menu.h"
#include "InputHelper.h"
#include "Lab.h"
#include "Lecture.h"
#include <iomanip>
#include <iostream>

Menu::Menu() : storage("attendance.txt"), predictor(75.0) {}

void Menu::run() {
    std::cout << "=====================================\n";
    std::cout << "   STUDENT ATTENDANCE PREDICTOR\n";
    std::cout << "=====================================\n";

    if (storage.load(student)) {
        std::cout << "Saved data loaded for " << student.getName() << "\n";
    } else {
        setupStudent();
    }

    int choice = 0;
    do {
        printMenu();
        choice = Input::readInt("Choose an option: ", 1, 7);
        switch (choice) {
            case 1:
                addCourse();
                break;
            case 2:
                updateAttendance();
                break;
            case 3:
                showSummary();
                break;
            case 4:
                showPrediction();
                break;
            case 5:
                showForecast();
                break;
            case 6:
                saveData();
                break;
            default:
                break;
        }
    } while (choice != 7);

    saveData();
    std::cout << "Goodbye!\n";
}

void Menu::setupStudent() {
    student.setName(Input::readLine("Student name: "));
    student.setRoll(Input::readLine("Roll number: "));
}

void Menu::printMenu() const {
    std::cout << "\n------------- MENU -------------\n";
    std::cout << "1. Add subject\n";
    std::cout << "2. Update attendance\n";
    std::cout << "3. View attendance summary\n";
    std::cout << "4. How many more classes do I need?\n";
    std::cout << "5. Semester forecast\n";
    std::cout << "6. Save\n";
    std::cout << "7. Save and exit\n";
}

void Menu::addCourse() {
    std::string name = Input::readLine("Subject name: ");
    int type = Input::readInt("Type (1 = Lecture, 2 = Lab): ", 1, 2);
    int held = Input::readInt("Classes held so far: ", 0, 1000);
    int attended = Input::readInt("Classes attended so far: ", 0, held);

    if (type == 1) {
        student.addCourse(std::make_shared<Lecture>(name, attended, held));
    } else {
        student.addCourse(std::make_shared<Lab>(name, attended, held));
    }
    std::cout << "Subject added.\n";
}

std::shared_ptr<Course> Menu::selectCourse() const {
    if (student.courseCount() == 0) {
        std::cout << "No subjects added yet.\n";
        return nullptr;
    }
    for (size_t i = 0; i < student.courseCount(); i++) {
        auto course = student.getCourse(i);
        std::cout << i + 1 << ". " << course->getName() << " (" << course->getType() << ")\n";
    }
    int index = Input::readInt("Select subject number: ", 1, static_cast<int>(student.courseCount()));
    return student.getCourse(static_cast<size_t>(index - 1));
}

void Menu::updateAttendance() {
    auto course = selectCourse();
    if (!course) {
        return;
    }
    int present = Input::readInt("New classes attended: ", 0, 1000);
    int absent = Input::readInt("New classes missed: ", 0, 1000);
    course->markPresent(present);
    course->markAbsent(absent);
    std::cout << "Updated. Attendance is now " << std::fixed << std::setprecision(1)
              << course->percentage() << "%\n";
}

void Menu::showSummary() const {
    std::cout << "\nStudent: " << student.getName() << "   Roll: " << student.getRoll() << "\n";
    if (student.courseCount() == 0) {
        std::cout << "No subjects added yet.\n";
        return;
    }

    std::cout << std::left << std::setw(4) << "#" << std::setw(20) << "Subject"
              << std::setw(10) << "Type" << std::setw(10) << "Attended"
              << std::setw(7) << "Held" << std::setw(9) << "Percent"
              << "Status\n";
    std::cout << std::string(68, '-') << "\n";

    for (size_t i = 0; i < student.courseCount(); i++) {
        auto course = student.getCourse(i);
        bool safe = predictor.meetsTarget(course->getAttended(), course->getHeld());
        std::cout << std::left << std::setw(4) << i + 1 << std::setw(20) << course->getName()
                  << std::setw(10) << course->getType() << std::setw(10) << course->getAttended()
                  << std::setw(7) << course->getHeld() << std::fixed << std::setprecision(1)
                  << std::setw(9) << course->percentage() << (safe ? "SAFE" : "SHORT") << "\n";
    }

    std::cout << std::string(68, '-') << "\n";
    int attended = student.totalAttended();
    int held = student.totalHeld();
    std::cout << "Overall: " << attended << "/" << held << " = " << std::fixed
              << std::setprecision(1) << predictor.currentPercentage(attended, held) << "%\n";
}

void Menu::showPrediction() const {
    if (student.courseCount() == 0) {
        std::cout << "No subjects added yet.\n";
        return;
    }

    std::cout << "\nTarget attendance: " << predictor.getTarget() << "%\n\n";

    for (size_t i = 0; i < student.courseCount(); i++) {
        auto course = student.getCourse(i);
        int attended = course->getAttended();
        int held = course->getHeld();
        std::string label = course->getName() + " (" + course->getType() + ")";

        if (predictor.meetsTarget(attended, held)) {
            int skip = predictor.classesCanSkip(attended, held);
            std::cout << label << ": SAFE. You can miss " << skip << " more "
                      << course->getType() << "(s) and stay at or above the target.\n";
        } else {
            int need = predictor.classesNeeded(attended, held);
            std::cout << label << ": SHORT. Attend the next " << need << " "
                      << course->getType() << "(s) in a row to reach the target.\n";
        }
    }

    int attended = student.totalAttended();
    int held = student.totalHeld();
    std::cout << "\nOverall: ";
    if (predictor.meetsTarget(attended, held)) {
        std::cout << "SAFE. You can miss " << predictor.classesCanSkip(attended, held)
                  << " more classes overall.\n";
    } else {
        std::cout << "SHORT. Attend the next " << predictor.classesNeeded(attended, held)
                  << " classes in a row to reach the target.\n";
    }
}

void Menu::showForecast() const {
    auto course = selectCourse();
    if (!course) {
        return;
    }

    int attended = course->getAttended();
    int held = course->getHeld();
    int remaining = Input::readInt("Classes still remaining this semester: ", 0, 1000);

    int minimum = predictor.minimumToAttend(attended, held, remaining);
    double best = predictor.predictFinal(attended, held, remaining, remaining);

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "\nIf you attend all " << remaining << " remaining classes: " << best << "%\n";

    if (minimum < 0) {
        std::cout << "Even with full attendance you cannot reach " << predictor.getTarget() << "%.\n";
        return;
    }

    std::cout << "Minimum you must attend out of " << remaining << ": " << minimum << "\n";
    std::cout << "You can afford to miss at most " << remaining - minimum << " of them.\n";

    int plan = Input::readInt("How many do you plan to attend? ", 0, remaining);
    double finalPercent = predictor.predictFinal(attended, held, remaining, plan);
    std::cout << "Predicted final attendance: " << finalPercent << "% ("
              << (finalPercent + 1e-9 >= predictor.getTarget() ? "SAFE" : "SHORT") << ")\n";
}

void Menu::saveData() const {
    if (storage.save(student)) {
        std::cout << "Data saved.\n";
    } else {
        std::cout << "Could not save data.\n";
    }
}
