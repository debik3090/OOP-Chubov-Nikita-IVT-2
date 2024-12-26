#pragma once
#include <string>

// Базовый класс Person
class Person
{
protected:
    std::string fullName_; // ФИО
    char gender_;          // пол
    int birthYear_;        // год рождения

public:
    // Конструктор
    Person(const std::string& fullName, char gender, int birthYear);

    // Виртуальный деструктор для корректного удаления из базовых указателей
    virtual ~Person() = default;

    // Геттеры-сеттеры 
    std::string getFullName() const { return fullName_; }
    char getGender() const { return gender_; }
    int getBirthYear() const { return birthYear_; }

    // Пример виртуального метода: вывести информацию о человеке
    virtual void printInfo() const;
};
