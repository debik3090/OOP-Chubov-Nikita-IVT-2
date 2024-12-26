#pragma once
#include "ILoggable.h"
#include <cstddef>   // size_t

class ExpressionEvaluator : public ILoggable
{
protected:
    double* operands_;      // ������������ ������ ���������
    size_t numOperands_;    // ������� ���-�� ��������� (��������� � �������)

public:
    // ����������� ��� ���������� - 20 ���������, �������������� ������
    ExpressionEvaluator();

    // ����������� � ���������� n - n ���������, �������������� ������
    ExpressionEvaluator(size_t n);

    // ����������� ����������
    virtual ~ExpressionEvaluator();

    // ��������� �������� value ������ �������� �� ������� pos
    void setOperand(size_t pos, double value);

    // ��������� ����� ������ �� n ��������� �������� �������� ops
    void setOperands(double ops[], size_t n);

    // ����� ����������� ����� ��� ���������� ���������
    virtual double calculate() const = 0;

    // ������ ���������� ILoggable 
    virtual void logToScreen() const override = 0;
    virtual void logToFile(const std::string& filename) const override = 0;

    // ������ ��� ���������� ���������
    size_t getNumOperands() const { return numOperands_; }

protected:
    std::string formatOperand(double value) const;
};
