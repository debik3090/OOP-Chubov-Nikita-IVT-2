#pragma once

#include "Person.h"
#include "ISalaryCalculation.h"
#include <string>

// ����� Teacher ����������� �� Person
// ��������� ��������� ISalaryCalculation ��� ������� ��������
class Teacher : public Person, public ISalaryCalculation
{
private:
    // �������� ��������� �� �������:
    int experience_;              // ���� (���-�� ��� ������)
    int startYear_;               // ��� ������ ������ � ������������
    std::string position_;        // ��������
    std::string academicDegree_;  // ������ �������: �������� ���� ��� ������ ����
    std::string academicTitle_;   // ������ ������: ������ ��� ���������

public:
    // �����������
    Teacher(const std::string& fullName,
        char gender,
        int birthYear,
        int experience,
        int startYear,
        const std::string& position,
        const std::string& academicDegree,
        const std::string& academicTitle);

    // ���������� ���������� ISalaryCalculation:
    // ����� �����:
    //  5000 + 700 �� ������� ������� ��������� ���� (��� +1200 �� �������) +
    //  +2200 �� ������ ������� (��� +3500 �� ����������) + 700 �� ������ 5 ��� �����
    double calculate() const override;

    // ������������� printInfo()
    void printInfo() const override;
};
