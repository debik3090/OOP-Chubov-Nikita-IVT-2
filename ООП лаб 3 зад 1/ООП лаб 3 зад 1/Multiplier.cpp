#include "Multiplier.h"
#include <iostream>   
#include <fstream>    

// Метод calculate() отвечает за вычисление результата выражения вида
// (x1 * x2 * x3 * ...)
double Multiplier::calculate() const
{
    // Если операндов нет логичным будет вернуть 0 (или 1)
    // но здесь выбрали возвращать 0.0 так как множители фактически не заданы
    if (numOperands_ == 0)
        return 0.0;

    // Начинаем результат с 1.0
    double result = 1.0;

    // Перемножаем все операнды, хранящиеся в массиве operands_
    for (size_t i = 0; i < numOperands_; ++i)
    {
        result *= operands_[i];
    }
    return result;
}

// Метод logToScreen() реализует интерфейс ILoggable и выводит 
// выражение на экран в формате: "Multiplier expression: x1 * x2 * x3 * ..."
void Multiplier::logToScreen() const
{
    std::cout << "Multiplier expression: ";

    // Перебираем все операнды и выводим их
    // используя вспомогательный метод formatOperand()
    // который например оборачивает отрицательные числа в скобки
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);

        // Между операндами ставим знак *
        // После последнего операнда символ * не ставим
        if (i < numOperands_ - 1) std::cout << " * ";
    }
    std::cout << std::endl;
}

// Метод logToFile() аналогичен logToScreen() но запись ведётся в файл
// имя которого задаётся параметром filename
void Multiplier::logToFile(const std::string& filename) const
{
    // Открываем файл для записи в конец (append).
    std::ofstream ofs(filename, std::ios::app);

    // Если не удалось открыть файл — выводим сообщение об ошибке
    if (!ofs.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    // Записываем в файл строку с выражением (операнды, разделённые "*")
    ofs << "Multiplier expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << " * ";
    }
    ofs << std::endl;

    // Закрываем файл
    ofs.close();
}
