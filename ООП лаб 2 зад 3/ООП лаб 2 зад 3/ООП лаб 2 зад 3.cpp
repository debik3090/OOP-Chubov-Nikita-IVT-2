#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
using namespace std;

class Student {
private:
    string fullName; //фио студента
    string gender; //пол студента
    int birthYear; //год рождения
    int enrollmentYear; //год поступления
    string recordBookNumber; //номер зачетной книжки
    double averageScore; //средний балл

    //метод для расчета среднего балла
    double calculateAverage(const vector<int>& scores) {
        if (scores.empty()) return 0.0; //если нет оценок, возвращаем 0
        int sum = 0;
        for (int score : scores) {
            sum += score; //суммируем оценки
        }
        return static_cast<double>(sum) / scores.size(); //считаем среднее
    }

public:
    //конструктор без параметров
    Student() : fullName(""), gender(""), birthYear(0), enrollmentYear(0),
        recordBookNumber(""), averageScore(0.0) {}

    //конструктор с параметрами
    Student(const string& fullName, const string& gender, int birthYear,
        int enrollmentYear, const string& recordBookNumber, double averageScore)
        : fullName(fullName), gender(gender), birthYear(birthYear),
        enrollmentYear(enrollmentYear), recordBookNumber(recordBookNumber),
        averageScore(averageScore) {}

    //сеттеры
    void setFullName(const string& fullName) { this->fullName = fullName; }
    void setGender(const string& gender) { this->gender = gender; }
    void setBirthYear(int birthYear) { this->birthYear = birthYear; }
    void setEnrollmentYear(int enrollmentYear) { this->enrollmentYear = enrollmentYear; }
    void setRecordBookNumber(const string& recordBookNumber) { this->recordBookNumber = recordBookNumber; }
    void setAverageScore(double averageScore) { this->averageScore = averageScore; }

    //геттеры
    string getFullName() const { return fullName; }
    string getGender() const { return gender; }
    int getBirthYear() const { return birthYear; }
    int getEnrollmentYear() const { return enrollmentYear; }
    string getRecordBookNumber() const { return recordBookNumber; }
    double getAverageScore() const { return averageScore; }

    //метод для пересчета среднего балла
    void recalculateAverageScore(const vector<int>& newScores) {
        averageScore = calculateAverage(newScores);
    }

    //методы сериализации
    void serialize() const {
        ofstream file("student.txt");
        if (file.is_open()) {
            file << fullName << endl
                << gender << endl
                << birthYear << endl
                << enrollmentYear << endl
                << recordBookNumber << endl
                << averageScore << endl;
            file.close();
        }
    }

    void serialize(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << fullName << endl
                << gender << endl
                << birthYear << endl
                << enrollmentYear << endl
                << recordBookNumber << endl
                << averageScore << endl;
            file.close();
        }
    }

    void deserialize() {
        ifstream file("student.txt");
        if (file.is_open()) {
            getline(file, fullName);
            getline(file, gender);
            file >> birthYear >> enrollmentYear;
            file.ignore();
            getline(file, recordBookNumber);
            file >> averageScore;
            file.close();
        }
    }

    void deserialize(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, fullName);
            getline(file, gender);
            file >> birthYear >> enrollmentYear;
            file.ignore();
            getline(file, recordBookNumber);
            file >> averageScore;
            file.close();
        }
    }

    //метод для вывода информации о студенте
    void printInfo() const {
        cout << "фио: " << fullName << endl;
        cout << "пол: " << gender << endl;
        cout << "год рождения: " << birthYear << endl;
        cout << "год поступления: " << enrollmentYear << endl;
        cout << "номер зачетной книжки: " << recordBookNumber << endl;
        cout << "средний балл: " << averageScore << endl;
    }
};

//функция для имитации сессии
void simulateSession(Student& student) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, 5);

    vector<int> scores(4);
    for (int& score : scores) {
        score = dist(gen); //генерация случайных оценок
    }
    student.recalculateAverageScore(scores);
}

int main() {
    std::system("chcp 65001 > nul"); //переключаем консоль в UTF-8
    std::setlocale(LC_ALL, "ru-RU"); //устанавливаем русскую локаль

    //создание массива студентов
    Student students[3];
    students[0].setFullName("Иванов Иван Иванович");
    students[0].setGender("Мужской");
    students[0].setBirthYear(2000);
    students[0].setEnrollmentYear(2018);
    students[0].setRecordBookNumber("12345");

    students[1].setFullName("Петрова Анна Сергеевна");
    students[1].setGender("Женский");
    students[1].setBirthYear(2001);
    students[1].setEnrollmentYear(2019);
    students[1].setRecordBookNumber("23456");

    students[2].setFullName("Сидоров Павел Андреевич");
    students[2].setGender("Мужской");
    students[2].setBirthYear(1999);
    students[2].setEnrollmentYear(2017);
    students[2].setRecordBookNumber("34567");

    //создание студента в куче
    Student* heapStudent = new Student("Федорова Ольга Викторовна", "Женский", 2002, 2020, "45678", 0.0);

    //имитация трех сессий
    for (int i = 0; i < 3; ++i) {
        for (Student& student : students) {
            simulateSession(student);
        }
        simulateSession(*heapStudent);
    }

    //сортировка студентов по убыванию среднего балла
    vector<Student> allStudents(begin(students), end(students));
    allStudents.push_back(*heapStudent);

    sort(allStudents.begin(), allStudents.end(), [](const Student& a, const Student& b) {
        return a.getAverageScore() > b.getAverageScore();
        });

    //вывод результатов
    cout << "результаты студентов после трех сессий:" << endl;
    for (const Student& student : allStudents) {
        student.printInfo();
        cout << endl;
    }

    //удаляем студента из кучи
    delete heapStudent;

    return 0;
}
