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
    // Сначала выводим количество операндов
    std::cout << "Operands: " << numOperands_ << std::endl;

    // Затем выводим запись выражения
    // Пример: 5.6-(-2.1)-3.2-1.5
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) std::cout << "-";
    }
    std::cout << std::endl;

    // Можно сразу вывести результат, если нужно в том же методе:
    double result = calculate();
    std::cout << "Result = " << result << std::endl;
}

void Subtractor::logToFile(const std::string& filename) const
{
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    ofs << "Operands: " << numOperands_ << std::endl;

    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << "-";
    }
    ofs << std::endl;

    // Аналогично, можно прописать (или не прописать) вывод результата
    double result = calculate();
    ofs << "Result = " << result << std::endl;

    ofs.close();
}


// Произвольное перемешивание всех операндов
void Subtractor::shuffle()
{
    // Меняем местами первый и последний операнд,
    // затем меняем знак у обоих.
    if (numOperands_ > 1)
    {
        size_t first = 0;
        size_t last = numOperands_ - 1;

        // Сохраним во временную переменную
        double temp = operands_[first];
        operands_[first] = operands_[last];
        operands_[last] = temp;

        // Меняем знак у обоих (теперь уже после swap).
        operands_[first] = -operands_[first];
        operands_[last] = -operands_[last];
    }
}

void Subtractor::shuffle(size_t i, size_t j)
{
    // Меняем местами i-ый и j-ый операнд, 
    // затем меняем знак у обоих.
    if (i < numOperands_ && j < numOperands_)
    {
        double temp = operands_[i];
        operands_[i] = operands_[j];
        operands_[j] = temp;

        // Меняем знак
        operands_[i] = -operands_[i];
        operands_[j] = -operands_[j];
    }
}

