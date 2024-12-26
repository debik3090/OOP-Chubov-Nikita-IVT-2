#pragma once
#include "ExpressionEvaluator.h"

// Класс Summator - сумма всех операндов (x1 + x2 + x3 + ...)
class Summator : public ExpressionEvaluator
{
public:
    // Используем конструкторы базового класса
    using ExpressionEvaluator::ExpressionEvaluator;

    // Реализация чисто виртуального метода calculate()
    double calculate() const override;

    // Реализация методов интерфейса ILoggable
    void logToScreen() const override;
    void logToFile(const std::string& filename) const override;
};
