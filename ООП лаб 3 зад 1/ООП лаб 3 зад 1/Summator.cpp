#include "Summator.h"
#include <iostream>   // ��� ������ � �������
#include <fstream>    // ��� ������ � �������� �������

// ����� calculate() ��������� ����� ���� ���������: (x1 + x2 + x3 + ...)
double Summator::calculate() const
{
    double result = 0.0;
    // �������� �� ������� operands_ � ����������� �����.
    for (size_t i = 0; i < numOperands_; ++i)
    {
        result += operands_[i];
    }
    return result;
}

// ����� logToScreen() ������� ������ ����: "Summator expression: x1 + x2 + x3 + ..."
void Summator::logToScreen() const
{
    std::cout << "Summator expression: ";

    // ���������� ��� �������� � ������� �� � �������Operand()
    // ������� ����������� ������������� ����� � ������
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);
        // ����� ���������� ��������� ���� "+".
        if (i < numOperands_ - 1) std::cout << " + ";
    }
    std::cout << std::endl;
}

// ����� logToFile() � ������ logToScreen() 
// ������ ����� ��� �� � ������� � � ��������� ���� (filename)
void Summator::logToFile(const std::string& filename) const
{
    // ��������� ���� � ������ ���������� (append)
    std::ofstream ofs(filename, std::ios::app);

    // ���������, ������� �� ������� ����
    if (!ofs.is_open())
    {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return;
    }

    // ���������� � ���� �������� ��������� � ��������, �������� �� ������ "+"
    ofs << "Summator expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << " + ";
    }
    ofs << std::endl;

    // ��������� ���� �� ���������� ������
    ofs.close();
}
