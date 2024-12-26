#pragma once
#include "ExpressionEvaluator.h"

// ����� Multiplier - ������������ ���� ��������� (x1 * x2 * x3 * ...)
class Multiplier : public ExpressionEvaluator
{
public:
    using ExpressionEvaluator::ExpressionEvaluator;

    double calculate() const override;

    void logToScreen() const override;
    void logToFile(const std::string& filename) const override;
};

