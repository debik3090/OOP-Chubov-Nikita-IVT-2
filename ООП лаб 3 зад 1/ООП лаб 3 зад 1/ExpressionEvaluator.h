#pragma once
#include "ILoggable.h"
#include <cstddef>   // size_t

class ExpressionEvaluator : public ILoggable
{
protected:
    double* operands_;      // динамический массив операндов
    size_t numOperands_;    // текущее кол-во операндов (элементов в массиве)

public:
    // Конструктор без параметров - 20 операндов, инициализируем нулями
    ExpressionEvaluator();

    // Конструктор с параметром n - n операндов, инициализируем нулями
    ExpressionEvaluator(size_t n);

    // Виртуальный деструктор
    virtual ~ExpressionEvaluator();

    // Присвоить значение value одному операнду на позиции pos
    void setOperand(size_t pos, double value);

    // Заполнить сразу группу из n операндов массивом значений ops
    void setOperands(double ops[], size_t n);

    // Чисто виртуальный метод для вычисления выражения
    virtual double calculate() const = 0;

    // Методы интерфейса ILoggable 
    virtual void logToScreen() const override = 0;
    virtual void logToFile(const std::string& filename) const override = 0;

    // Геттер для количества операндов
    size_t getNumOperands() const { return numOperands_; }

protected:
    std::string formatOperand(double value) const;
};
