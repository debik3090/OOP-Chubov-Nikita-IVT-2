#include "Divisor.h"
#include <iostream>   
#include <fstream>    
#include <algorithm>  // std::swap
#include <cstdlib>    // std::rand()

// Метод calculate() отвечает за вычисление результата выражения типа "частное":
// (x1 / x2 / x3 / ...).
// По условию: если среди операндов (начиная со второго) встретится ноль, то 
// результат выражения присваивается 0
double Divisor::calculate() const
{
    // Если вообще нет операндов (numOperands_ == 0), возвращаем 0
    if (numOperands_ == 0)
        return 0.0;

    // Начинаем результат с первого операнда
    double result = operands_[0];

    // Делим на последующие операнды
    for (size_t i = 1; i < numOperands_; ++i)
    {
        // Если встретили ноль,
        // в условии сказано — результат = 0
        if (operands_[i] == 0.0)
        {
            return 0.0;
        }
        // Если нуля нет, продолжаем деление
        result /= operands_[i];
    }
    return result;
}

// Метод logToScreen() реализует интерфейс ILoggable и выводит 
// выражение на экран. Формат: "Divisor expression: x1 / x2 / x3 / ...
void Divisor::logToScreen() const
{
    std::cout << "Divisor expression: ";

    // Перебираем все операнды и выводим их
    // используя вспомогательный метод formatOperand()
    // который оборачивает отрицательные числа в скобки
    for (size_t i = 0; i < numOperands_; ++i)
    {
        std::cout << formatOperand(operands_[i]);

        // Между операндами ставим знак /
        // После последнего операнда символ  / не ставим
        if (i < numOperands_ - 1) std::cout << " / ";
    }
    std::cout << std::endl;
}

// Метод logToFile() — аналог logToScreen(), но запись идёт в файл
// Параметр filename задаёт имя файла. Запись добавляется в конец файла (std::ios::app)
void Divisor::logToFile(const std::string& filename) const
{
    // Открываем файл в режиме append.
    std::ofstream ofs(filename, std::ios::app);

    // Проверяем, успешно ли открыли файл.
    if (!ofs.is_open())
    {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    // Аналогично logToScreen() — пишем в файл строку с разделителем / между операндами
    ofs << "Divisor expression: ";
    for (size_t i = 0; i < numOperands_; ++i)
    {
        ofs << formatOperand(operands_[i]);
        if (i < numOperands_ - 1) ofs << " / ";
    }
    ofs << std::endl;

    // Закрываем файл.
    ofs.close();
}

// Реализация метода shuffle() интерфейса IShuffle — 
// случайное перемешивание всех операндов в массиве operands_
void Divisor::shuffle()
{
    // Перебираем все индексы массива и меняем элемент 
    // местами со случайно выбранным элементом
    for (size_t i = 0; i < numOperands_; ++i)
    {
        // j — случайный индекс от 0 до numOperands_ - 1
        size_t j = static_cast<size_t>(std::rand() % numOperands_);
        std::swap(operands_[i], operands_[j]);
    }
}

// Перегрузка метода shuffle(), позволяющая перемешивать 
// операнды только на указанных позициях i и j
void Divisor::shuffle(size_t i, size_t j)
{
    // Проверяем, чтобы оба индекса не выходили за границы
    if (i < numOperands_ && j < numOperands_)
    {
        std::swap(operands_[i], operands_[j]);
    }
}