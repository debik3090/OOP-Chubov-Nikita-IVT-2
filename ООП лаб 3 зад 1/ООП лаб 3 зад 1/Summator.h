#pragma once
#include "ExpressionEvaluator.h"

// ����� Summator - ����� ���� ��������� (x1 + x2 + x3 + ...)
class Summator : public ExpressionEvaluator
{
public:
    // ���������� ������������ �������� ������
    using ExpressionEvaluator::ExpressionEvaluator;

    // ���������� ����� ������������ ������ calculate()
    double calculate() const override;

    // ���������� ������� ���������� ILoggable
    void logToScreen() const override;
    void logToFile(const std::string& filename) const override;
};
