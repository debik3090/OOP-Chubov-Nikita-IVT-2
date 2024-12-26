#include "Subtractor.h"
#include <iostream>
#include <fstream>
#include <algorithm>  // std::swap
#include <cstdlib>    // std::rand, std::srand

double Subtractor::calculate() const
{
    if (numOperands_ == 0)
        return 0.0;

    double result = operands_[0];
    for (size_t i = 1; i < numOperands_; ++i)
    {
        result -= operands_[i];
    }
    return result;
}

void Subtractor::logToScreen() const
{
    // ������� ������� ���������� ���������
    std::cout << "Operands: " << numOperands_ << std::endl;

    // ����� ������� ������ ���������
    // ������: 5.6-(-2.1)-3.2-1.5
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) std::cout << "-";
    }
    std::cout << std::endl;

    // ����� ����� ������� ���������, ���� ����� � ��� �� ������:
    double result = calculate();
    std::cout << "Result = " << result << std::endl;
}

void Subtractor::logToFile(const std::string& filename) const
{
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs.is_open())
    {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return;
    }
    ofs << "Operands: " << numOperands_ << std::endl;

    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << "-";
    }
    ofs << std::endl;

    // ����������, ����� ��������� (��� �� ���������) ����� ����������
    double result = calculate();
    ofs << "Result = " << result << std::endl;

    ofs.close();
}


// ������������ ������������� ���� ���������
void Subtractor::shuffle()
{
    // ������ ������� ������ � ��������� �������,
    // ����� ������ ���� � �����.
    if (numOperands_ > 1)
    {
        size_t first = 0;
        size_t last = numOperands_ - 1;

        // �������� �� ��������� ����������
        double temp = operands_[first];
        operands_[first] = operands_[last];
        operands_[last] = temp;

        // ������ ���� � ����� (������ ��� ����� swap).
        operands_[first] = -operands_[first];
        operands_[last] = -operands_[last];
    }
}

void Subtractor::shuffle(size_t i, size_t j)
{
    // ������ ������� i-�� � j-�� �������, 
    // ����� ������ ���� � �����.
    if (i < numOperands_ && j < numOperands_)
    {
        double temp = operands_[i];
        operands_[i] = operands_[j];
        operands_[j] = temp;

        // ������ ����
        operands_[i] = -operands_[i];
        operands_[j] = -operands_[j];
    }
}

