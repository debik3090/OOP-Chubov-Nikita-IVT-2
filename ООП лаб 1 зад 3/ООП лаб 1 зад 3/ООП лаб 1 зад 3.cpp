
#include <iostream>
#include <cstring> 
#include <stdexcept> 

using namespace std;

//собственная версия функции strchr
char* customStrchr(char* s, char c) {
    if (s == nullptr) {
        throw invalid_argument("строка не должна быть null"); //выбрасываем исключение если строка пустая
    }

    //идем по строке посимвольно
    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c) {
            return &s[i]; //возвращаем указатель на первый найденный символ
        }
    }
    return nullptr; //символ не найден
}

int main() {
    std::system("chcp 65001 > nul"); //настройка дял ком стр на русский язык
    std::setlocale(LC_ALL, "ru-RU"); 

    //тестовые данные
    char testString[] = "Привет, мир!";
    char testChar = 'м'; //символ для поиска

    //результат работы стандартной функции strchr
    char* standardResult = strchr(testString, testChar);

    //результат работы собственной функции customStrchr
    char* customResult = nullptr;
    try {
        customResult = customStrchr(testString, testChar); //вызываем собственную функцию
    }
    catch (const invalid_argument& e) {
        cerr << "ошибка: " << e.what() << endl; //выводим сообщение об ошибке
        return 1; //завершаем программу с кодом ошибки
    }

    //вывод результатов
    cout << "тестовая строка: " << testString << endl; //выводим исходную строку
    cout << "символ для поиска: " << testChar << endl; //выводим символ для поиска
    cout << "результат стандартной функции: "
        << (standardResult ? standardResult : "символ не найден") << endl; //результат стандартной strchr
    cout << "результат собственной функции: "
        << (customResult ? customResult : "символ не найден") << endl; //результат customStrchr

    return 0;
}
