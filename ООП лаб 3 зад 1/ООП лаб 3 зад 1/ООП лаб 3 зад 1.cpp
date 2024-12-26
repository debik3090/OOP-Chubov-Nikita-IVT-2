#include <iostream>
#include "CustomExpressionEvaluator.h"
#include "Subtractor.h"
#include "Multiplier.h"
#include "ExpressionEvaluator.h"
#include "IShuffle.h"

int main()
{
    std::system("chcp 65001 > nul"); 
    std::setlocale(LC_ALL, "ru-RU"); 

    // 1) CustomExpressionEvaluator
    CustomExpressionEvaluator* customEval = new CustomExpressionEvaluator(6);
    double customOps[] = { 5, 16, -3, 10, 12, 2 };
    customEval->setOperands(customOps, 6);

    // 2) Subtractor
    Subtractor* subtractor = new Subtractor(4);
    double subOps[] = { 5.6, -2.1, 3.2, 1.5 };
    subtractor->setOperands(subOps, 4);

    // 3) Multiplier
    Multiplier* multiplier = new Multiplier(3);
    multiplier->setOperand(0, 1.5);
    multiplier->setOperand(1, -8.0);
    multiplier->setOperand(2, 2.5);

    // Массив указателей
    ExpressionEvaluator* evaluators[3];
    evaluators[0] = customEval;  // базовый указатель на CustomExpressionEvaluator
    evaluators[1] = subtractor;  // базовый указатель на Subtractor
    evaluators[2] = multiplier;  // базовый указатель на Multiplier

    // Выводим их на экран, вычисляем результат
    for (int i = 0; i < 3; ++i)
    {
        evaluators[i]->logToScreen();
        double res = evaluators[i]->calculate();
        std::cout << "Класс " << i << " -> Результат = " << res << "\n" << std::endl;
    }

    // Проверяем, кто поддерживает IShuffle, и делаем shuffle
    for (int i = 0; i < 3; ++i)
    {
        IShuffle* shf = dynamic_cast<IShuffle*>(evaluators[i]);
        if (shf)
        {
            std::cout << "Объект " << i << " поддерживает IShuffle, вызываем shuffle()..." << std::endl;
            shf->shuffle();  // меняем местами первый и последний + инвертируем знак
            evaluators[i]->logToScreen();
            double res = evaluators[i]->calculate();
            std::cout << "Новый результат = " << res << "\n" << std::endl;
        }
        else
        {
            std::cout << "Объект " << i << " НЕ поддерживает IShuffle.\n" << std::endl;
        }
    }

    // Освобождение
    delete customEval;
    delete subtractor;
    delete multiplier;

    return 0;
}
