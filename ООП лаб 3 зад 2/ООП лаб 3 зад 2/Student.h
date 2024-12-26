#pragma once

#include "Person.h"
#include "ISalaryCalculation.h"

// ����� Student ����������� �� Person
// ���� ��������� ��������� ISalaryCalculation (��� ������� ���������)
class Student : public Person, public ISalaryCalculation
{
private:
    int admissionYear_;  // ��� �����������
    std::string recordBookNumber_; // ����� �������
    double averageMark_; // ������� ����

public:
    // ����������� 
    Student(const std::string& fullName,
        char gender,
        int birthYear,
        int admissionYear,
        const std::string& recordBookNumber,
        double averageMark);

    // �������������� ����� �� ISalaryCalculation
    // �������: ���� ������� ���� > 4.5, �� 1000, ����� 700
    double calculate() const override;

    // ������������� printInfo() ��� ������ �������������� ����
    void printInfo() const override;

    // ������� � ������ ������ ��� �������������
};
