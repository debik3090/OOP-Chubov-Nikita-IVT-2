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
    // ������� ����� 5000
    double sum = 5000.0;

    // +700 �� ������� ��������� ����, +1200 �� ������� ����
    if (academicDegree_ == "�������� ����")
    {
        sum += 700.0;
    }
    else if (academicDegree_ == "������ ����")
    {
        sum += 1200.0;
    }

    // +2200 �� ������ �������, +3500 �� ������ ����������
    if (academicTitle_ == "������")
    {
        sum += 2200.0;
    }
    else if (academicTitle_ == "���������")
    {
        sum += 3500.0;
    }

    // +700 �� ������ 5 ��� �����
    // �. �. �� experience_ = 0...4 ��� => 0,
    //                     5...9 => 700,
    //                     10...14 => 1400 � �.�
    // ����� ������� ���:
    int chunks5 = experience_ / 5; // ������������� �������
    sum += 700.0 * chunks5;

    return sum;
}

void Teacher::printInfo() const
{
    // �������� Person::printInfo() ��� ����� ������
    Person::printInfo();

    // ��������� ������������� ����
    std::cout << ", ���� (���): " << experience_
        << ", ��� ������ ������: " << startYear_
        << ", ���������: " << position_
        << ", �������: " << academicDegree_
        << ", ������: " << academicTitle_
        << std::endl;
}
