#include <iostream>
#include <stdexcept>
using namespace std;

class Vector {
private:
    int* data; //указатель на массив
    size_t size;

public:
    Vector(size_t size) : size(size) {
        data = new int[size]; //выделяем память для массива
        for (size_t i = 0; i < size; i++) {
            data[i] = 0; //инициализируем элементы массива нулями
        }
    }

    //деструктор
    ~Vector() {
        delete[] data; //освобождаем выделенную память
    }

    //перегрузка оператора индексации
    int& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("индекс вне границ массива"); //выбрасываем исключение при неверном индексе
        }
        return data[index]; //возвращаем ссылку на элемент массива
    }

    //перегрузка префиксного инкремента
    Vector& operator++() {
        for (size_t i = 0; i < size; i++) {
            ++data[i]; //увеличиваем каждый элемент массива
        }
        return *this; //возвращаем текущий объект
    }

    //перегрузка постфиксного инкремента
    Vector operator++(int) {
        Vector temp = *this; //сохраняем текущее состояние объекта
        ++(*this); //вызываем префиксный инкремент
        return temp; //возвращаем сохраненное состояние
    }

    //перегрузка префиксного декремента
    Vector& operator--() {
        for (size_t i = 0; i < size; i++) {
            --data[i]; //уменьшаем каждый элемент массива
        }
        return *this; //возвращаем текущий объект
    }

    //перегрузка постфиксного декремента
    Vector operator--(int) {
        Vector temp = *this; //сохраняем текущее состояние объекта
        --(*this); //вызываем префиксный декремент
        return temp; //возвращаем сохраненное состояние
    }

    //вывод содержимого вектора
    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << data[i] << " "; //выводим элементы массива через пробел
        }
        cout << endl; //переходим на новую строку
    }
};

class Matrix {
private:
    int** data; //указатель на двумерный массив
    size_t rows, cols; //размеры матрицы

public:
    //конструктор
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data = new int* [rows]; //выделяем память для строк
        for (size_t i = 0; i < rows; i++) {
            data[i] = new int[cols]; //выделяем память для столбцов
            for (size_t j = 0; j < cols; j++) {
                data[i][j] = 0; //инициализируем элементы нулями
            }
        }
    }

    //деструктор
    ~Matrix() {
        for (size_t i = 0; i < rows; i++) {
            delete[] data[i]; //освобождаем память каждой строки
        }
        delete[] data; //освобождаем память для указателей строк
    }

    //метод для получения элемента (константный)
    int at(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw out_of_range("индекс вне границ матрицы"); //выбрасываем исключение при неверном индексе
        }
        return data[i][j]; //возвращаем значение элемента
    }

    //метод для установки значения элемента
    void setAt(size_t i, size_t j, int val) {
        if (i >= rows || j >= cols) {
            throw out_of_range("индекс вне границ матрицы"); //выбрасываем исключение при неверном индексе
        }
        data[i][j] = val; //устанавливаем значение элемента
    }

    //вывод содержимого матрицы
    void print() const {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                cout << data[i][j] << " "; //выводим элементы строки через пробел
            }
            cout << endl; //переходим на новую строку после каждой строки матрицы
        }
    }

    //перегрузка префиксного инкремента
    Matrix& operator++() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ++data[i][j]; //увеличиваем каждый элемент матрицы
            }
        }
        return *this; //возвращаем текущий объект
    }

    //перегрузка постфиксного инкремента
    Matrix operator++(int) {
        Matrix temp = *this; //сохраняем текущее состояние объекта
        ++(*this); //вызываем префиксный инкремент
        return temp; //возвращаем сохраненное состояние
    }

    //перегрузка префиксного декремента
    Matrix& operator--() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                --data[i][j]; //уменьшаем каждый элемент матрицы
            }
        }
        return *this; //возвращаем текущий объект
    }

    //перегрузка постфиксного декремента
    Matrix operator--(int) {
        Matrix temp = *this; //сохраняем текущее состояние объекта
        --(*this); //вызываем префиксный декремент
        return temp; //возвращаем сохраненное состояние
    }
};

int main() {
    std::system("chcp 65001 > nul"); //для русской конс
    std::setlocale(LC_ALL, "ru-RU"); 

    //тестирование класса Vector
    cout << "тестирование класса Vector:" << endl;
    Vector vec(5);
    vec[0] = 10;
    vec[1] = 20;
    vec.print();

    ++vec;
    vec.print();

    vec--;
    vec.print();

    //тестирование класса Matrix
    cout << "тестирование класса Matrix:" << endl;
    Matrix mat(3, 3);
    mat.setAt(1, 1, 42);
    mat.print();

    ++mat;
    mat.print();

    mat--;
    mat.print();

    return 0;
}
