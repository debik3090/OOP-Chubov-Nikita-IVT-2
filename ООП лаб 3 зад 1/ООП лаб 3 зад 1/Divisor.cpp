#include "Divisor.h"
#include <iostream>   
#include <fstream>    
#include <algorithm>  // std::swap
#include <cstdlib>    // std::rand()

// ����� calculate() �������� �� ���������� ���������� ��������� ���� "�������":
// (x1 / x2 / x3 / ...).
// �� �������: ���� ����� ��������� (������� �� �������) ���������� ����, �� 
// ��������� ��������� ������������� 0
double Divisor::calculate() const
{
    // ���� ������ ��� ��������� (numOperands_ == 0), ���������� 0
    if (numOperands_ == 0)
        return 0.0;

    // �������� ��������� � ������� ��������
    double result = operands_[0];

    // ����� �� ����������� ��������
    for (size_t i = 1; i < numOperands_; ++i)
    {
        // ���� ��������� ����,
        // � ������� ������� � ��������� = 0
        if (operands_[i] == 0.0)
        {
            return 0.0;
        }
        // ���� ���� ���, ���������� �������
        result /= operands_[i];
    }
    return result;
}

// ����� logToScreen() ��������� ��������� ILoggable � ������� 
// ��������� �� �����. ������: "Divisor expression: x1 / x2 / x3 / ...
void Divisor::logToScreen() const
{
    std::cout << "Divisor expression: ";

    // ���������� ��� �������� � ������� ��
    // ��������� ��������������� ����� formatOperand()
    // ������� ����������� ������������� ����� � ������
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);

        // ����� ���������� ������ ���� /
        // ����� ���������� �������� ������  / �� ������
        if (i < numOperands_ - 1) std::cout << " / ";
    }
    std::cout << std::endl;
}

// ����� logToFile() � ������ logToScreen(), �� ������ ��� � ����
// �������� filename ����� ��� �����. ������ ����������� � ����� ����� (std::ios::app)
void Divisor::logToFile(const std::string& filename) const
{
    // ��������� ���� � ������ append.
    std::ofstream ofs(filename, std::ios::app);

    // ���������, ������� �� ������� ����.
    if (!ofs.is_open())
    {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return;
    }

    // ���������� logToScreen() � ����� � ���� ������ � ������������ / ����� ����������
    ofs << "Divisor expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << " / ";
    }
    ofs << std::endl;

    // ��������� ����.
    ofs.close();
}

// ���������� ������ shuffle() ���������� IShuffle � 
// ��������� ������������� ���� ��������� � ������� operands_
void Divisor::shuffle()
{
    // ���������� ��� ������� ������� � ������ ������� 
    // ������� �� �������� ��������� ���������
    for (size_t i = 0; i < numOperands_; ++i)
    {
        // j � ��������� ������ �� 0 �� numOperands_ - 1
        size_t j = static_cast<size_t>(std::rand() % numOperands_);
        std::swap(operands_[i], operands_[j]);
    }
}

// ���������� ������ shuffle(), ����������� ������������ 
// �������� ������ �� ��������� �������� i � j
void Divisor::shuffle(size_t i, size_t j)
{
    // ���������, ����� ��� ������� �� �������� �� �������
    if (i < numOperands_ && j < numOperands_)
    {
        std::swap(operands_[i], operands_[j]);
    }
}