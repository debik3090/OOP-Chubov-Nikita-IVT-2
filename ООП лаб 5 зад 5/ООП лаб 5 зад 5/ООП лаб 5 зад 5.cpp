#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

// Шаблонный класс Cache<T>
template <typename T>
class Cache {
private:
    std::vector<T> cache_; // Внутренний контейнер для хранения элементов

public:
    // Метод для добавления элемента в кеш
    void put(const T& elem) {
        cache_.push_back(elem);
    }

    // Оператор += для добавления элемента в кеш
    Cache& operator+=(const T& elem) {
        put(elem);
        return *this;
    }

    // Метод для проверки наличия элемента в кеше
    bool contains(const T& elem) const {
        return std::find(cache_.begin(), cache_.end(), elem) != cache_.end();
    }

    // Метод для вывода содержимого кеша (для демонстрации)
    void display() const {
        std::cout << "Содержимое кеша: ";
        for (const auto& item : cache_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Явная специализация шаблонного класса для типа std::string
template <>
class Cache<std::string> {
private:
    std::vector<std::string> cache_; // Внутренний контейнер для хранения строк
    static const size_t MAX_SIZE = 100; // Максимальная вместимость кеша

public:
    // Метод для добавления строки в кеш с проверкой на переполнение
    void put(const std::string& elem) {
        if (cache_.size() >= MAX_SIZE) {
            throw std::runtime_error("Кеш может содержать не более 100 строк.");
        }
        cache_.push_back(elem);
    }

    // Оператор += для добавления строки в кеш
    Cache& operator+=(const std::string& elem) {
        put(elem);
        return *this;
    }

    // Метод для проверки наличия строки в кеше по первому символу
    bool contains(const std::string& elem) const {
        if (elem.empty()) {
            return false;
        }
        char firstChar = elem[0];
        return std::any_of(cache_.begin(), cache_.end(),
            [firstChar](const std::string& s) -> bool {
                return !s.empty() && s[0] == firstChar;
            });
    }

    // Метод для вывода содержимого кеша (для демонстрации)
    void display() const {
        std::cout << "Содержимое кеша (строки): ";
        for (const auto& item : cache_) {
            std::cout << "\"" << item << "\" ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::system("chcp 65001 > nul");
    std::setlocale(LC_ALL, "ru-RU");
    try {
        // Инстанцирование Cache<int>
        Cache<int> intCache;

        // Добавление элементов с помощью put()
        intCache.put(10);
        intCache.put(20);
        intCache.put(30);

        // Добавление элементов с помощью оператора +=
        intCache += 40;
        intCache += 50;

        // Вывод содержимого кеша intCache
        intCache.display();

        // Проверка наличия элементов в intCache
        std::cout << "intCache содержит 20: " << (intCache.contains(20) ? "Да" : "Нет") << std::endl;
        std::cout << "intCache содержит 60: " << (intCache.contains(60) ? "Да" : "Нет") << std::endl;

        std::cout << "----------------------------------------" << std::endl;

        // Инстанцирование Cache<std::string>
        Cache<std::string> stringCache;

        // Добавление строк с помощью put()
        stringCache.put("Apple");
        stringCache.put("Banana");
        stringCache.put("Cherry");

        // Добавление строк с помощью оператора +=
        stringCache += "Apricot";
        stringCache += "Blueberry";

        // Вывод содержимого кеша stringCache
        stringCache.display();

        // Проверка наличия строк в stringCache по первому символу
        std::cout << "stringCache содержит \"Avocado\" (первый символ 'A'): "
            << (stringCache.contains("Avocado") ? "Да" : "Нет") << std::endl;

        std::cout << "stringCache содержит \"Dragonfruit\" (первый символ 'D'): "
            << (stringCache.contains("Dragonfruit") ? "Да" : "Нет") << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}
