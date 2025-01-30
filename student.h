
#include <fstream>
#include <queue>
#include <sstream>

class Value {
private:
    std::string value;
public:
    explicit Value(const std::string &value) {
        this->value = value;
    };

    explicit Value(int value) {
        this->value = value;
    };

    explicit operator int() const {
        std::stringstream ss;
        int result;
        ss << value; ss >> result;
        return result;
    }

    explicit operator std::string() const {
//        auto* res = new std::string(value);
        return value;
    }
};

struct Student {
private:
    std::string _first_name;
    std::string _last_name;
    std::string _group;

    int _age;
    int _missed_lessons;
    int _passed_exams;
    int _all_exams;

public:
    Student() = default;

    void setFirstName(const Value &firstName) {
        this->_first_name = (std::string) firstName;
    }

    void setLastName(const Value &lastName) {
        this->_last_name = (std::string) lastName;
    }

    void setGroup(const Value &group) {
        this->_group = (std::string) group;
    }

    void setAge(const Value &age) {
        this->_age = (int) age;
    }

    void setMissedLessons(const Value & missedLessons) {
        _missed_lessons = (int) missedLessons;
    }

    void setPassedExams(const Value & passedExams) {
        _passed_exams = (int) passedExams;
    }

    void setAllExams(const Value & allExams) {
        _all_exams = (int) allExams;
    }

    void grow() {
        ++_age;
    }

    void miss_lesson() {
        ++_missed_lessons;
    }

    void pass_exam() {
        ++_passed_exams;
    }

    void print_about() {
        std::cout << "Студент " << _last_name << ' ' << _first_name << " из группы " << _group << std::endl;
        std::cout << "Возраст: " << _age << ". Пропущено пар: " << _missed_lessons << std::endl;
        std::cout << "Сдано экзаменов " << _passed_exams << " из " << _all_exams << std::endl;
    }

    void save_to_file(const std::string &filename) {
        std::ofstream os(filename);
        os << _first_name << ':'
           << _last_name << ':'
           << _group << ':'
           << _age << ':'
           << _missed_lessons << ':'
           << _passed_exams << ':'
           << _all_exams << std::endl;

        os.flush();
        os.close();
    }

    static Student load_from_file(const std::string &filename) {
        std::ifstream is(filename);
        std::string buffer;
        std::queue<Value> queue;

        while (getline(is, buffer, ':')) {
            queue.emplace(buffer);
        }

        if (queue.size() != 7) {
            std::cerr << "Неверные данные в файле" << std::endl;
            exit(-1);
        }

        std::stringstream ss;
        Student student;
        student.setFirstName(pop(queue));
        student.setLastName(pop(queue));
        student.setGroup(pop(queue));
        student.setAge(pop(queue));
        student.setMissedLessons(pop(queue));
        student.setPassedExams(pop(queue));
        student.setAllExams(pop(queue));

        return student;
    }

private:
    template<class T>
    static T pop(std::queue<T> &vector) {
        T t = vector.front();
        vector.pop();
        return t;
    }
};
