#pragma once

#include "Person.h"
#include "ISalaryCalculation.h"
#include <string>

// Класс Teacher наследуется от Person
// реализует интерфейс ISalaryCalculation для расчёта зарплаты
class Teacher : public Person, public ISalaryCalculation
{
private:
    // Основные параметры по условию:
    int experience_;              // стаж (кол-во лет работы)
    int startYear_;               // год начала работы в университете
    std::string position_;        // должност
    std::string academicDegree_;  // ученая степень: кандидат наук или доктор наук
    std::string academicTitle_;   // ученое звание: доцент или профессор

public:
    // Конструктор
    Teacher(const std::string& fullName,
        char gender,
        int birthYear,
        int experience,
        int startYear,
        const std::string& position,
        const std::string& academicDegree,
        const std::string& academicTitle);

    // Реализация интерфейса ISalaryCalculation:
    // Сумма равна:
    //  5000 + 700 за научную степень кандидата наук (или +1200 за доктора) +
    //  +2200 за звание доцента (или +3500 за профессора) + 700 за каждые 5 лет стажа
    double calculate() const override;

    // Переопределим printInfo()
    void printInfo() const override;
};
