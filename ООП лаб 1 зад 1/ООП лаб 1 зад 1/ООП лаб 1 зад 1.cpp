
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>



const int n = 15; // Размер входного массива

// Функция для обработки массива
int processArray(double inputArray[], double outputArray[], double a, double b) {
    int negativeCount = 0;
    

    // Обработка массива
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) { // Элементы с четными индексами
            double randomValue = a + static_cast<double>(rand()) / RAND_MAX * (b - a); // Генерация нового случайного числа
            inputArray[i] *= randomValue;
        }
        if (inputArray[i] < 0) { // Если элемент отрицательный
            outputArray[negativeCount] = inputArray[i];
            ++negativeCount;
        }
    }


    return negativeCount;
}

int main() {
    std::system("chcp 65001 > nul");
    std::setlocale(LC_ALL, "ru-RU");

    double inputArray[n]; // Входной массив
    double outputArray[n]; // Выходной массив (максимальный размер)
    double a, b;

    // Инициализация входного массива
    for (int i = 0; i < n; ++i) {
        inputArray[i] = 1.0; // Заполнение единицами
    }

    // Ввод значений a и b
    printf("Введите знач a и b (a < 0): ");
    std::cin >> a >> b;
    if (a >= 0 || a > b) {
        printf("Ошибка: a должно быть меньше 0 и a < b.\n");
        return 1;
    }

    srand(static_cast<unsigned>(time(0))); // Инициализация генератора случайных чисел

    // Вызов функции обработки массива
    int negativeCount = processArray(inputArray, outputArray, a, b);

    // Вывод входного массива
    printf("Входной массив: [ ");
    for (int i = 0; i < n; ++i) {
        printf("%.2f ", inputArray[i]);
    }
    printf("]\n");

    // Вывод выходного массива
    printf("Выходной массив: [ ");
    for (int i = 0; i < negativeCount; ++i) {
        printf("%.2f ", outputArray[i]);
    }
    printf("]\n");

    // Вывод количества отрицательных элементов
    printf("Количество отрицательных элементов: %d\n", negativeCount);

    return 0;
}
