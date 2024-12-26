#pragma once

// ��������� ����������� ����� ������ �����
class ISalaryCalculation
{
public:
    virtual ~ISalaryCalculation() = default;

    // ����� ����������� ����� ��� ������� �����
    virtual double calculate() const = 0;
};