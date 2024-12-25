#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cmath> 
using namespace std;

class Fraction {
private:
    int numerator; //числитель
    int denominator; //знаменатель
    static int count; //счетчик созданных объектов

public:
    //конструкторы
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) {
            throw invalid_argument("знаменатель не может быть равен нулю"); //проверка на ноль
        }
        reduce(); //сокращаем дробь при создании
        ++count; //увелсчетчик
    }

    Fraction(int numerator) : numerator(numerator), denominator(1) {
        ++count; //увел счетчи
    }

    Fraction() : numerator(0), denominator(1) {
        ++count; //увел счетчик 
    }

    ~Fraction() {
        --count; //уменьшаем счетчик 
    }

    //статический метод для получения счетчика объектов
    static int getCount() {
        return count; //возвращаем количество созданных объектов
    }

    //метод для сокращения дроби
    void reduce() {
        int gcdValue = gcd(abs(numerator), abs(denominator)); //вычисляем нод
        numerator /= gcdValue;
        denominator /= gcdValue;

        if (denominator < 0) { //убираем отрицание из знаменателя
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    //статический метод для нахождения нод
    static int gcd(int n, int m) {
        while (m != 0) {
            int temp = m;
            m = n % m;
            n = temp;
        }
        return n;
    }

    //перегрузка операторов
    Fraction operator+(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        ); //сложение дробей
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        ); //вычитание дробей
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(
            numerator * other.numerator,
            denominator * other.denominator
        ); //умножение дробей
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("деление на ноль недопустимо"); //проверка деления на ноль
        }
        return Fraction(
            numerator * other.denominator,
            denominator * other.numerator
        ); //деление дробей
    }

    //вывод дроби
    void print() const {
        cout << numerator << "/" << denominator << endl; //вывод дроби в формате числитель/знаменатель
    }

    //статический метод для вывода десятичной дроби как обыкновенной
    static void printAsFraction(double decimal_fraction) {
        const int precision = 1000000; //точность преобразования
        int numerator = round(decimal_fraction * precision); //вычисляем числитель
        int denominator = precision; //задаем знаменатель
        int gcdValue = gcd(abs(numerator), abs(denominator)); //сокращаем дробь
        numerator /= gcdValue;
        denominator /= gcdValue;
        cout << numerator << "/" << denominator << endl;
    }

    //перегрузка метода для строковой десятичной дроби
    static void printAsFraction(const char* decimal_fraction) {
        double value = atof(decimal_fraction); //преобразуем строку в double
        printAsFraction(value); //вызываем метод с double
    }
};

//инициализация статического члена
int Fraction::count = 0;

//тестирование класса Fraction
int main() {
    std::system("chcp 65001 > nul"); 
    std::setlocale(LC_ALL, "ru-RU"); 
    try {
        //создаем объекты дробей
        Fraction f1(3, 4);
        Fraction f2(5, 6);
        Fraction f3(7, 8);

        //вывод объектов
        cout << "дроби:" << endl;
        f1.print();
        f2.print();
        f3.print();

        //операции с дробями
        cout << "\nрезультаты операций:" << endl;
        Fraction sum = f1 + f2;
        sum.print();

        Fraction diff = f1 - f2;
        diff.print();

        Fraction prod = f1 * f2;
        prod.print();

        Fraction quot = f1 / f2;
        quot.print();

        //пример сокращения дробей
        Fraction reducible(10, 20);
        reducible.print();

        //пример работы статических методов
        cout << "\nдесятичная дробь как обыкновенная:" << endl;
        Fraction::printAsFraction(0.43);
        Fraction::printAsFraction("0.25");

        //счетчик объектов
        cout << "\nколичество созданных объектов Fraction: " << Fraction::getCount() << endl;

    }
    catch (const exception& e) {
        cerr << "ошибка: " << e.what() << endl; //вывод сообщения об ошибке
    }

    return 0;
}
