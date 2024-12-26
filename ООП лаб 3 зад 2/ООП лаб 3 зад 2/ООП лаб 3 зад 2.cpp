#include <iostream>
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include "ISalaryCalculation.h"

int main()
{
    std::system("chcp 65001 > nul");
    std::setlocale(LC_ALL, "ru-RU");

    // Создадим 2 преподавателей и 2 студентов
    Teacher* t1 = new Teacher(
        "Иванов Иван Иванович",   // ФИО
        'M',                     // пол
        1970,                    // год рождения
        10,                      // стаж
        2000,                    // год начала работы
        "Доцент кафедры Математики", // должность
        "кандидат наук",         // ученая степень
        "доцент"                 // ученое звание
    );

    Teacher* t2 = new Teacher(
        "Петров Пётр Петрович",
        'M',
        1960,
        18,
        1995,
        "Профессор кафедры Физики",
        "доктор наук",
        "профессор"
    );

    Student* s1 = new Student(
        "Студентка Вера Сергеевна",
        'F',
        2002,   // год рождения
        2020,   // год поступления
        "123456", // номер зачётки
        4.8     // средний балл
    );

    Student* s2 = new Student(
        "Студент Василий Викторович",
        'M',
        2000,
        2018,
        "987654",
        4.3
    );

    // Помещаем все объекты в один контейнер базовых указателей 
    // (как вариант — вектор или массив)
    std::vector<ISalaryCalculation*> people;
    // Добавляем объектов (все они реализуют ISalaryCalculation)
    people.push_back(t1);
    people.push_back(t2);
    people.push_back(s1);
    people.push_back(s2);

    // 1) Демонстрация полиморфизма calculate()
    //    (все объекты ведут себя по-разному)
    std::cout << "=== Полиморфизм calculate() ===" << std::endl;
    for (size_t i = 0; i < people.size(); ++i)
    {
        double sum = people[i]->calculate();
        std::cout << i << ") Сумма оплаты труда = " << sum << std::endl;
    }
    std::cout << std::endl;

    // 2) Демонстрация RTTI и вывода полной информации
    //    Проверяем, является ли объект Student или Teacher 
    //    (через dynamic_cast к Person, потому что есть printInfo())
    std::cout << "=== RTTI и полный вывод информации (printInfo) ===" << std::endl;
    for (size_t i = 0; i < people.size(); ++i)
    {
        // У нас people[i] — это ISalaryCalculation*, но мы знаем, что 
        // объект ещё и Person, поэтому безопасно делаем cast:
        Person* person = dynamic_cast<Person*>(people[i]);
        if (person)
        {
            // Вызываем printInfo() (виртуальный метод)
            // который в зависимости от реального класса выведет 
            // нужные данные
            std::cout << "Object " << i << ": ";
            person->printInfo();
        }
    }
    std::cout << std::endl;

    // 3) Освобождаем память
    //    Поскольку у нас были вызовы new, нужно сделать delete
    for (auto& p : people)
    {
        // Приведение к Person*, чтобы корректно удалять
        // Виртуальные деструкторы уже обеспечены в базовых классах
        Person* pers = dynamic_cast<Person*>(p);
        if (pers)
            delete pers;
    }
    people.clear();

    return 0;
}
