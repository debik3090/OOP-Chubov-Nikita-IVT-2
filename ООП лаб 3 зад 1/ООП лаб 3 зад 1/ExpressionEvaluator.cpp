#include "ExpressionEvaluator.h"
#include <iostream>
#include <fstream>

ExpressionEvaluator::ExpressionEvaluator()
{
    numOperands_ = 20;              // �� ��������� 20
    operands_ = new double[20];     // �������� ������������ ������ ��� 20 ���������
    for (size_t i = 0; i < numOperands_; ++i)
        operands_[i] = 0.0;         // �������������� ������
}

ExpressionEvaluator::ExpressionEvaluator(size_t n)
{
    numOperands_ = n;
    operands_ = new double[n];
    for (size_t i = 0; i < numOperands_; ++i)
        operands_[i] = 0.0;
}

ExpressionEvaluator::~ExpressionEvaluator()
{
    // ����������� ������������ ������
    delete[] operands_;
    operands_ = nullptr;
    numOperands_ = 0;
}

void ExpressionEvaluator::setOperand(size_t pos, double value)
{
    if (pos < numOperands_)
    {
        operands_[pos] = value;
    }
    // � �������� ���� ������ �� ���������� ������������ �������
}

void ExpressionEvaluator::setOperands(double ops[], size_t n)
{
    // ��������� ������� ���������, ������� ���� � �������,
    // �� �� ����� ������ numOperands_
    size_t limit = (n < numOperands_) ? n : numOperands_;
    for (size_t i = 0; i < limit; ++i)
    {
        operands_[i] = ops[i];
    }
}

std::string ExpressionEvaluator::formatOperand(double value) const
{
    // ���� ����� ������������� - ����� � ������
    if (value < 0)
    {
        return "(" + std::to_string(value) + ")";
    }
    else
    {
        return std::to_string(value);
    }
}
