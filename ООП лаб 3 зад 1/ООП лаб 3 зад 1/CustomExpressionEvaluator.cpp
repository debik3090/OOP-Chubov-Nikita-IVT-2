#include "CustomExpressionEvaluator.h"
#include <iostream>
#include <fstream>

double CustomExpressionEvaluator::calculate() const
{
    // Формат: x1 + x2/2 + x3/3 + x4/4 + ...
    // Если операндов нет — результат 0.
    if (numOperands_ == 0)
        return 0.0;

    double result = 0.0;

    // Каждый операнд делим на его индекс + 1 (если это не x1):
    // x1 идёт как есть (т.е. x1 / 1), x2/2, x3/3 и т.д.
    for (size_t i = 0; i < numOperands_; ++i)
    {
        // Так как i начинается с 0, а мы делим на (i+1):
        double term = operands_[i] / static_cast<double>(i + 1);
        result += term;
    }

    return result;
}

void CustomExpressionEvaluator::logToScreen() const
{
    std::cout << "Custom expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void CustomExpressionEvaluator::logToFile(const std::string& filename) const
{
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    ofs << "Custom expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << ", ";
    }
    ofs << std::endl;
    ofs.close();
}
