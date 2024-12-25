
#include <iostream>
#include <iomanip>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

//функция инита одномерного массива
void initializeArray(double* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i * sin(M_PI * i / 25);
    }
}

//функция вывода одномерного массива
void print1DArray(double* array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << setw(10) << fixed << setprecision(4) << array[i];
        if ((i + 1) % 5 == 0) cout << endl; //переход на новую строку каждые 5 эл
    }
}

//функция преобразования 1D массива в 2D массив
double** transformArray(double* array, int rows, int cols) {
    double** matrix = new double* [rows]; //выделяем память под двумерный массив
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
    }

    int index = 0;
    for (int i = 0; i < rows; ++i) {
        double sum = 0.0;
        for (int j = 1; j < cols; ++j) { //вропускаем первый эл
            matrix[i][j] = array[index++];
            sum += matrix[i][j];
        }
        matrix[i][0] = sum; //1-ый эл строки — сумма остальных
    }

    return matrix;
}

//функция вывода двумерного массива
void print2DArray(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(10) << fixed << setprecision(4) << matrix[i][j];
        }
        cout << endl;
    }
}

//функция освобождения памяти двумерного массива
void free2DArray(double** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    std::system("chcp 65001 > nul"); // насройки консоли для русского языка
    std::setlocale(LC_ALL, "ru-RU");
    const int size = 25; //размер одномерного массива
    const int rows = 5, cols = 5; //размеры двумерного массива

    //выделяем память под одномерный массив
    double* array1D = new double[size];

    //инит и вывод одномерного массива
    cout << "Одномерный массив:" << endl;
    initializeArray(array1D, size);
    print1DArray(array1D, size);

    //1D -> 2D
    double** array2D = transformArray(array1D, rows, cols);

    //вывод двумерного массива
    cout << "\nДвумерный массив:" << endl;
    print2DArray(array2D, rows, cols);

    //освобождение памяти
    delete[] array1D;
    free2DArray(array2D, rows);

    return 0;
}

