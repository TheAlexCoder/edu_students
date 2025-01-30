#include <iostream>
#include <list>
#include <functional>
#include "student.h"

typedef void (Student::*StudentSet) (const Value &);

int main() {
    std::cout << "Введите 0 если хотите открыть файл" << std::endl;
    std::cout << "Введите 1 если хотите ввести данные вручную" << std::endl;
    int source;
    std::cin >> source;

    if (source == 0) {
        std::cout << "Введите путь и название файла: ";
        std::string filename;
        std::cin >> filename;
        auto student = Student::load_from_file(filename);
        student.print_about();
    } else if (source == 1) {
        Student student;
        std::string buffer;
        std::vector<std::string> names =
                {"фимилию", "имя", "группу", "возраст",
                 "количество пропущенных пар у", "количество сданных экзаменов у", "общее количество экзаменов у"};
        StudentSet funcs[] = {
                &Student::setLastName,
                &Student::setFirstName,
                &Student::setGroup,
                &Student::setAge,
                &Student::setMissedLessons,
                &Student::setPassedExams,
                &Student::setAllExams,
                };

        for (int i = 0; i < names.size(); ++i) {
            std::cout << "Введите " << names[i] << " студента: ";
            std::cin >> buffer;

            (&student->*funcs[i])(Value(buffer));
        }

        std::cout << "Данные студента" << std::endl;
        student.print_about();

        std::cout << "Введите путь и название файла, куда сохранить данные студента: ";
        std::cin >> buffer;
        student.save_to_file(buffer);

    } else {
        std::cerr << "Неверный ввод" << std::endl;
        exit(-1);
    }
    return 0;
}
