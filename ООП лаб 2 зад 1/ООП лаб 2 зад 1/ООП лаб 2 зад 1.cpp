
#include <iostream>
#include <stdexcept> // Для обработки исключений
using namespace std;

class Vector {
private:
    int* data;  // Указатель на массив
    size_t size; // Размер массива

public:
    // Конструктор
    Vector(size_t size) : size(size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = 0; // Инициализируем нулями
        }
    }

    // Деструктор
    ~Vector() {
        delete[] data; // Освобождаем память
    }

    // Перегрузка оператора индексации
    int& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Индекс вне границ массива");
        }
        return data[index];
    }

    // Перегрузка префиксного инкремента
    Vector& operator++() {
        for (size_t i = 0; i < size; i++) {
            ++data[i];
        }
        return *this;
    }

    // Перегрузка постфиксного инкремента
    Vector operator++(int) {
        Vector temp = *this; // Сохраняем текущее состояние
        ++(*this); // Используем префиксный инкремент
        return temp;
    }

    // Перегрузка префиксного декремента
    Vector& operator--() {
        for (size_t i = 0; i < size; i++) {
            --data[i];
        }
        return *this;
    }

    // Перегрузка постфиксного декремента
    Vector operator--(int) {
        Vector temp = *this; // Сохраняем текущее состояние
        --(*this); // Используем префиксный декремент
        return temp;
    }

    // Вывод содержимого вектора
    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

class Matrix {
private:
    int** data;  // Указатель на двумерный массив
    size_t rows, cols; // Размеры матрицы

public:
    // Конструктор
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data = new int* [rows];
        for (size_t i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (size_t j = 0; j < cols; j++) {
                data[i][j] = 0; // Инициализируем нулями
            }
        }
    }

    // Деструктор
    ~Matrix() {
        for (size_t i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data; // Освобождаем память
    }

    // Метод для получения элемента (константный)
    int at(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw out_of_range("Индекс вне границ матрицы");
        }
        return data[i][j];
    }

    // Метод для установки значения элемента
    void setAt(size_t i, size_t j, int val) {
        if (i >= rows || j >= cols) {
            throw out_of_range("Индекс вне границ матрицы");
        }
        data[i][j] = val;
    }

    // Вывод содержимого матрицы
    void print() const {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Перегрузка префиксного инкремента
    Matrix& operator++() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ++data[i][j];
            }
        }
        return *this;
    }

    // Перегрузка постфиксного инкремента
    Matrix operator++(int) {
        Matrix temp = *this; // Сохраняем текущее состояние
        ++(*this); // Используем префиксный инкремент
        return temp;
    }

    // Перегрузка префиксного декремента
    Matrix& operator--() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                --data[i][j];
            }
        }
        return *this;
    }

    // Перегрузка постфиксного декремента
    Matrix operator--(int) {
        Matrix temp = *this; // Сохраняем текущее состояние
        --(*this); // Используем префиксный декремент
        return temp;
    }
};

int main() {
    std::system("chcp 65001 > nul"); // Переключаем консоль в UTF-8
    std::setlocale(LC_ALL, "ru-RU"); // Устанавливаем русскую локаль

    // Тестирование класса Vector
    cout << "Тестирование класса Vector:" << endl;
    Vector vec(5);
    vec[0] = 10;
    vec[1] = 20;
    vec.print();

    ++vec;
    vec.print();

    vec--;
    vec.print();

    // Тестирование класса Matrix
    cout << "Тестирование класса Matrix:" << endl;
    Matrix mat(3, 3);
    mat.setAt(1, 1, 42);
    mat.print();

    ++mat;
    mat.print();

    mat--;
    mat.print();

    return 0;
}
