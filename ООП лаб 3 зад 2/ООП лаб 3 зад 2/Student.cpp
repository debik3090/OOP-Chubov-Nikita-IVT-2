#include "Student.h"
#include <iostream>

Student::Student(const std::string& fullName,
    char gender,
    int birthYear,
    int admissionYear,
    const std::string& recordBookNumber,
    double averageMark)
    : Person(fullName, gender, birthYear)
    , admissionYear_(admissionYear)
    , recordBookNumber_(recordBookNumber)
    , averageMark_(averageMark)
{
}

double Student::calculate() const
{
    // Если средний балл > 4.5 => стипендия = 1000, иначе 700
    if (averageMark_ > 4.5)
        return 1000.0;
    else
        return 700.0;
}

void Student::printInfo() const
{
    // Вызываем базовый метод, чтобы не повторять поля 
    Person::printInfo();

    // Добавляем специфическую информацию
    std::cout << ", год поступления: " << admissionYear_
        << ", номер зачетки: " << recordBookNumber_
        << ", средний балл: " << averageMark_
        << std::endl;
}
