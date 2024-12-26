#include "Person.h"
#include <iostream>

Person::Person(const std::string& fullName, char gender, int birthYear)
    : fullName_(fullName), gender_(gender), birthYear_(birthYear)
{
}

void Person::printInfo() const
{
    std::cout << "ФИО: " << fullName_
        << ", пол: " << (gender_ == 'M' ? "Мужской" : "Женский")
        << ", год рождения: " << birthYear_;
}
