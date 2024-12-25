#include <cstdio>  
#include <cstdlib> 
#include <ctime>   
#include <iostream> 

//размер входного массива
const int n = 15;

//функция для обработки массива
int processArray(double inputArray[], double outputArray[], double a, double b) {
    int negativeCount = 0; //счетчик отриц чисел

    //проходим по всем эл массива
    for (int i = 0; i < n; ++i) {
        //проверяем явл ли индекс четным
        if (i % 2 == 0) {
            //генерируем случ число в диапазоне от а до б
            double randomValue = a + static_cast<double>(rand()) / RAND_MAX * (b - a);
            // умножаем эл массива на случ число
            inputArray[i] *= randomValue;
        }

        //если эл массива отриц
        if (inputArray[i] < 0) {
            //копируем в выходной массив
            outputArray[negativeCount] = inputArray[i];
            //увел счетчик
            ++negativeCount;
        }
    }

    //возвращаем кол отрицательных чисел
    return negativeCount;
}

int main() {
    //настройка консоли для корректного отображения русского текста
    std::system("chcp 65001 > nul");
    std::setlocale(LC_ALL, "ru-RU");

    double inputArray[n]; //входной массив размером n
    double outputArray[n]; //выходной массив с макс размером n
    double a, b; //диапазон

    //инит входного массива 1
    for (int i = 0; i < n; ++i) {
        inputArray[i] = 1.0;
    }

    //Ввод диапазона случ чисел
    printf("Введите значения a и b (a < 0): ");
    std::cin >> a >> b;

    //проверяем корректность ввода
    if (a >= 0 || a > b) {
        printf("Ошибка: a должно быть меньше 0 и a < b.\n");
        return 1;
    }
    srand(static_cast<unsigned>(time(0)));

    //вызываем функцию обработки массива
    int negativeCount = processArray(inputArray, outputArray, a, b);

    //вывод входного массива
    printf("Входной массив: [ ");
    for (int i = 0; i < n; ++i) {
        printf("%.2f ", inputArray[i]); //выводим элементы с 2 знаками после запятой
    }
    printf("]\n");

    //вывод выходного массива
    printf("Выходной массив: [ ");
    for (int i = 0; i < negativeCount; ++i) {
        printf("%.2f ", outputArray[i]); //выводим только отрицательные элементы
    }
    printf("]\n");

    //выводим кол
    printf("Количество отрицательных элементов: %d\n", negativeCount);

    return 0;
}
