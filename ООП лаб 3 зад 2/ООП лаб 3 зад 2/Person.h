#pragma once
#include <string>

// ������� ����� Person
class Person
{
protected:
    std::string fullName_; // ���
    char gender_;          // ���
    int birthYear_;        // ��� ��������

public:
    // �����������
    Person(const std::string& fullName, char gender, int birthYear);

    // ����������� ���������� ��� ����������� �������� �� ������� ����������
    virtual ~Person() = default;

    // �������-������� 
    std::string getFullName() const { return fullName_; }
    char getGender() const { return gender_; }
    int getBirthYear() const { return birthYear_; }

    // ������ ������������ ������: ������� ���������� � ��������
    virtual void printInfo() const;
};
