#include "Multiplier.h"
#include <iostream>   
#include <fstream>    

// ����� calculate() �������� �� ���������� ���������� ��������� ����
// (x1 * x2 * x3 * ...)
double Multiplier::calculate() const
{
    // ���� ��������� ��� �������� ����� ������� 0 (��� 1)
    // �� ����� ������� ���������� 0.0 ��� ��� ��������� ���������� �� ������
    if (numOperands_ == 0)
        return 0.0;

    // �������� ��������� � 1.0
    double result = 1.0;

    // ����������� ��� ��������, ���������� � ������� operands_
    for (size_t i = 0; i < numOperands_; ++i)
    {
        result *= operands_[i];
    }
    return result;
}

// ����� logToScreen() ��������� ��������� ILoggable � ������� 
// ��������� �� ����� � �������: "Multiplier expression: x1 * x2 * x3 * ..."
void Multiplier::logToScreen() const
{
    std::cout << "Multiplier expression: ";

    // ���������� ��� �������� � ������� ��
    // ��������� ��������������� ����� formatOperand()
    // ������� �������� ����������� ������������� ����� � ������
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);

        // ����� ���������� ������ ���� *
        // ����� ���������� �������� ������ * �� ������
        if (i < numOperands_ - 1) std::cout << " * ";
    }
    std::cout << std::endl;
}

// ����� logToFile() ���������� logToScreen() �� ������ ������ � ����
// ��� �������� ������� ���������� filename
void Multiplier::logToFile(const std::string& filename) const
{
    // ��������� ���� ��� ������ � ����� (append).
    std::ofstream ofs(filename, std::ios::app);

    // ���� �� ������� ������� ���� � ������� ��������� �� ������
    if (!ofs.is_open())
    {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return;
    }

    // ���������� � ���� ������ � ���������� (��������, ���������� "*")
    ofs << "Multiplier expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << " * ";
    }
    ofs << std::endl;

    // ��������� ����
    ofs.close();
}
