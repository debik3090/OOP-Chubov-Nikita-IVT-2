#pragma once
#include "ExpressionEvaluator.h"
#include "IShuffle.h"

// Класс Subtractor - разность всех операндов (x1 - x2 - x3 - ...)
class Subtractor : public ExpressionEvaluator, public IShuffle
{
public:
    using ExpressionEvaluator::ExpressionEvaluator;

    double calculate() const override;

    void logToScreen() const override;
    void logToFile(const std::string& filename) const override;

    // Реализация интерфейса IShuffle
    void shuffle() override;
    void shuffle(size_t i, size_t j) override;
};
