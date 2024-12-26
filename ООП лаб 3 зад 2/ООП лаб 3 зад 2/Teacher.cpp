#include "Teacher.h"
#include <iostream>

Teacher::Teacher(const std::string& fullName,
    char gender,
    int birthYear,
    int experience,
    int startYear,
    const std::string& position,
    const std::string& academicDegree,
    const std::string& academicTitle)
    : Person(fullName, gender, birthYear)
    , experience_(experience)
    , startYear_(startYear)
    , position_(position)
    , academicDegree_(academicDegree)
    , academicTitle_(academicTitle)
{
}

double Teacher::calculate() const
{
    // Базовый оклад 5000
    double sum = 5000.0;

    // +700 за степень кандидата наук, +1200 за доктора наук
    if (academicDegree_ == "кандидат наук")
    {
        sum += 700.0;
    }
    else if (academicDegree_ == "доктор наук")
    {
        sum += 1200.0;
    }

    // +2200 за звание доцента, +3500 за звание профессора
    if (academicTitle_ == "доцент")
    {
        sum += 2200.0;
    }
    else if (academicTitle_ == "профессор")
    {
        sum += 3500.0;
    }

    // +700 за каждые 5 лет стажа
    // Т. е. за experience_ = 0...4 лет => 0,
    //                     5...9 => 700,
    //                     10...14 => 1400 и т.д
    // Можем сделать так:
    int chunks5 = experience_ / 5; // целочисленное деление
    sum += 700.0 * chunks5;

    return sum;
}

void Teacher::printInfo() const
{
    // Вызываем Person::printInfo() для общих данных
    Person::printInfo();

    // Добавляем специфические поля
    std::cout << ", стаж (лет): " << experience_
        << ", год начала работы: " << startYear_
        << ", должность: " << position_
        << ", степень: " << academicDegree_
        << ", звание: " << academicTitle_
        << std::endl;
}
