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
    // ���� ������� ���� > 4.5 => ��������� = 1000, ����� 700
    if (averageMark_ > 4.5)
        return 1000.0;
    else
        return 700.0;
}

void Student::printInfo() const
{
    // �������� ������� �����, ����� �� ��������� ���� 
    Person::printInfo();

    // ��������� ������������� ����������
    std::cout << ", ��� �����������: " << admissionYear_
        << ", ����� �������: " << recordBookNumber_
        << ", ������� ����: " << averageMark_
        << std::endl;
}
