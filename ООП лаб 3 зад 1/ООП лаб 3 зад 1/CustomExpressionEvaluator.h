#pragma once
#include "ExpressionEvaluator.h"

// ��������, ���������� �� "��������������" ����������� �� �������
// �����������, ��� ��� ��������� ����:  (x1 + x2) * (x3 - x4) + x5 ... 
class CustomExpressionEvaluator : public ExpressionEvaluator
{
public:
    using ExpressionEvaluator::ExpressionEvaluator;

    double calculate() const override;

    void logToScreen() const override;
    void logToFile(const std::string& filename) const override;
};
