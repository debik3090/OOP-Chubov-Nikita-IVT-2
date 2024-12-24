
#include <iostream>
#include <cstring> // Для стандартной strchr
#include <stdexcept> // Для обработки исключений

using namespace std;

// Собственная версия функции strchr
char* customStrchr(char* s, char c) {
    if (s == nullptr) {
        throw invalid_argument("Строка не должна быть null");
    }

    // Идем по строке посимвольно
    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c) {
            return &s[i]; // Возвращаем указатель на первый найденный символ
        }
    }
    return nullptr; // Символ не найден
}

int main() {
    std::system("chcp 65001 > nul"); // Переключаем консоль в UTF-8
    std::setlocale(LC_ALL, "ru-RU");
    // Тестовые данные
    char testString[] = "Привет, мир!";
    char testChar = 'м';

    // Результат работы стандартной функции
    char* standardResult = strchr(testString, testChar);

    // Результат работы собственной функции
    char* customResult = nullptr;
    try {
        customResult = customStrchr(testString, testChar);
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    // Вывод результатов
    cout << "Тестовая строка: " << testString << endl;
    cout << "Символ для поиска: " << testChar << endl;
    cout << "Результат стандартной функции: "
        << (standardResult ? standardResult : "Символ не найден") << endl;
    cout << "Результат собственной функции: "
        << (customResult ? customResult : "Символ не найден") << endl;

    return 0;
}
