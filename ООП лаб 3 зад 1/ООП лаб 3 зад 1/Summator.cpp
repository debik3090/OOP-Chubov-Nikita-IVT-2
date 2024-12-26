#include "Summator.h"
#include <iostream>   // для вывода в консоль
#include <fstream>    // для работы с файловым потоком

// Метод calculate() вычисляет сумму всех операндов: (x1 + x2 + x3 + ...)
double Summator::calculate() const
{
    double result = 0.0;
    // Проходим по массиву operands_ и накапливаем сумму.
    for (size_t i = 0; i < numOperands_; ++i)
    {
        result += operands_[i];
    }
    return result;
}

// Метод logToScreen() выводит строку вида: "Summator expression: x1 + x2 + x3 + ..."
void Summator::logToScreen() const
{
    std::cout << "Summator expression: ";

    // Перебираем все операнды и выводим их в форматеOperand()
    // который оборачивает отрицательные числа в скобки
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);
        // Между операндами вставляем знак "+".
        if (i < numOperands_ - 1) std::cout << " + ";
    }
    std::cout << std::endl;
}

// Метод logToFile() — аналог logToScreen() 
// только вывод идёт не в консоль а в указанный файл (filename)
void Summator::logToFile(const std::string& filename) const
{
    // Открываем файл в режиме добавления (append)
    std::ofstream ofs(filename, std::ios::app);

    // Проверяем, удалось ли открыть файл
    if (!ofs.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    // Записываем в файл описание выражения и операнды, разделяя их знаком "+"
    ofs << "Summator expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << " + ";
    }
    ofs << std::endl;

    // Закрываем файл по завершении записи
    ofs.close();
}
