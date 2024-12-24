
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cmath> // Для std::round
using namespace std;

class Fraction {
private:
    int numerator;   // Числитель
    int denominator; // Знаменатель
    static int count; // Счетчик созданных объектов

public:
    // Конструкторы
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) {
            throw invalid_argument("Знаменатель не может быть равен нулю");
        }
        reduce(); // Сокращаем дробь при создании
        ++count;  // Увеличиваем счетчик объектов
    }

    Fraction(int numerator) : numerator(numerator), denominator(1) {
        ++count; // Увеличиваем счетчик объектов
    }

    Fraction() : numerator(0), denominator(1) {
        ++count; // Увеличиваем счетчик объектов
    }

    ~Fraction() {
        --count; // Уменьшаем счетчик объектов
    }

    // Статический метод для получения счетчика объектов
    static int getCount() {
        return count;
    }

    // Метод для сокращения дроби
    void reduce() {
        int gcdValue = gcd(abs(numerator), abs(denominator));
        numerator /= gcdValue;
        denominator /= gcdValue;

        // Убираем отрицание из знаменателя
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Статический метод для нахождения НОД
    static int gcd(int n, int m) {
        while (m != 0) {
            int temp = m;
            m = n % m;
            n = temp;
        }
        return n;
    }

    // Перегрузка операторов
    Fraction operator+(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(
            numerator * other.numerator,
            denominator * other.denominator
        );
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Деление на ноль недопустимо");
        }
        return Fraction(
            numerator * other.denominator,
            denominator * other.numerator
        );
    }

    // Вывод дроби
    void print() const {
        cout << numerator << "/" << denominator << endl;
    }

    // Статический метод для вывода десятичной дроби как обыкновенной
    static void printAsFraction(double decimal_fraction) {
        const int precision = 1000000; // Для точности преобразования
        int numerator = round(decimal_fraction * precision);
        int denominator = precision;
        int gcdValue = gcd(abs(numerator), abs(denominator));
        numerator /= gcdValue;
        denominator /= gcdValue;
        cout << numerator << "/" << denominator << endl;
    }

    // Перегрузка метода для строковой десятичной дроби
    static void printAsFraction(const char* decimal_fraction) {
        double value = atof(decimal_fraction); // Преобразуем строку в double
        printAsFraction(value);
    }
};

// Инициализация статического члена
int Fraction::count = 0;

// Тестирование класса Fraction
int main() {
    std::system("chcp 65001 > nul"); // Переключаем консоль в UTF-8
    std::setlocale(LC_ALL, "ru-RU"); // Устанавливаем русскую локаль
    try {
        // Создаем объекты дробей
        Fraction f1(3, 4);
        Fraction f2(5, 6);
        Fraction f3(7, 8);

        // Вывод объектов
        cout << "Дроби:" << endl;
        f1.print();
        f2.print();
        f3.print();

        // Операции с дробями
        cout << "\nРезультаты операций:" << endl;
        Fraction sum = f1 + f2;
        sum.print();

        Fraction diff = f1 - f2;
        diff.print();

        Fraction prod = f1 * f2;
        prod.print();

        Fraction quot = f1 / f2;
        quot.print();

        // Пример сокращения дробей
        Fraction reducible(10, 20);
        reducible.print();

        // Пример работы статических методов
        cout << "\nДесятичная дробь как обыкновенная:" << endl;
        Fraction::printAsFraction(0.43);
        Fraction::printAsFraction("0.25");

        // Счетчик объектов
        cout << "\nКоличество созданных объектов Fraction: " << Fraction::getCount() << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}