#pragma once

#include "Person.h"
#include "ISalaryCalculation.h"

// Класс Student наследуемся от Person
// плюс реализуем интерфейс ISalaryCalculation (для расчёта стипендии)
class Student : public Person, public ISalaryCalculation
{
private:
    int admissionYear_;  // год поступления
    std::string recordBookNumber_; // номер зачетки
    double averageMark_; // средний балл

public:
    // Конструктор 
    Student(const std::string& fullName,
        char gender,
        int birthYear,
        int admissionYear,
        const std::string& recordBookNumber,
        double averageMark);

    // Переопределяем метод из ISalaryCalculation
    // Условие: если средний балл > 4.5, то 1000, иначе 700
    double calculate() const override;

    // Переопределим printInfo() для вывода дополнительной инфы
    void printInfo() const override;

    // Геттеры и прочие методы при необходимости
};
