#pragma once

// Интерфейс начислителя суммы оплаты труда
class ISalaryCalculation
{
public:
    virtual ~ISalaryCalculation() = default;

    // Чисто виртуальный метод для расчёта суммы
    virtual double calculate() const = 0;
};