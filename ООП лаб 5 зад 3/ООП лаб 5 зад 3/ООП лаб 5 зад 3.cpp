#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

// Класс Книга
class Book {
private:
    std::string title;
    std::string author;
    int year;

public:
    // Конструктор
    Book(const std::string& title_, const std::string& author_, int year_)
        : title(title_), author(author_), year(year_) {}

    // Геттеры
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }

    // Перегрузка оператора вывода для удобства
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

// Перегрузка оператора вывода для класса Book
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Автор: " << book.author
        << ", Название: \"" << book.title
        << "\", Год издания: " << book.year;
    return os;
}

// Функтор для сортировки книг по автору и названию
struct CompareBooks {
    bool operator()(const Book& a, const Book& b) const {
        if (a.getAuthor() < b.getAuthor())
            return true;
        if (a.getAuthor() > b.getAuthor())
            return false;
        // Если авторы одинаковы, сортируем по названию
        return a.getTitle() < b.getTitle();
    }
};

// Функтор для поиска книг в заданном диапазоне годов
struct FindBooksInYearRange {
    int startYear;
    int endYear;

    FindBooksInYearRange(int start, int end) : startYear(start), endYear(end) {}

    bool operator()(const Book& book) const {
        return book.getYear() >= startYear && book.getYear() <= endYear;
    }
};

int main() {
    std::system("chcp 65001 > nul"); 
    std::setlocale(LC_ALL, "ru-RU");
    // Создание коллекции книг
    std::vector<Book> library;

    // Добавление книг в коллекцию
    library.emplace_back("Война и мир", "Лев Толстой", 1869);
    library.emplace_back("Преступление и наказание", "Фёдор Достоевский", 1866);
    library.emplace_back("Мастер и Маргарита", "Михаил Булгаков", 1967);
    library.emplace_back("Анна Каренина", "Лев Толстой", 1877);
    library.emplace_back("Братья Карамазовы", "Фёдор Достоевский", 1880);
    library.emplace_back("Идиот", "Фёдор Достоевский", 1869);
    library.emplace_back("Собачье сердце", "Михаил Булгаков", 1925);
    library.emplace_back("Горе от ума", "Александр Грибоедов", 1823);
    library.emplace_back("Евгений Онегин", "Александр Пушкин", 1833);
    library.emplace_back("Лолита", "Владимир Набоков", 1955);
    library.emplace_back("Унесённые ветром", "Маргарет Митчелл", 1936);
    library.emplace_back("1984", "Джордж Оруэлл", 1949);
    library.emplace_back("Хоббит", "Джон Р. Р. Толкин", 1937);
    library.emplace_back("Моби Дик", "Герман Мелвилл", 1851);
    library.emplace_back("Дюна", "Фрэнк Герберт", 1965);

    // Вывод исходной коллекции
    std::cout << "Исходная коллекция книг:\n";
    for (const auto& book : library) {
        std::cout << book << "\n";
    }

    // Сортировка книг по автору и названию
    std::sort(library.begin(), library.end(), CompareBooks());

    // Вывод отсортированной коллекции
    std::cout << "\nОтсортированная коллекция книг (по автору и названию):\n";
    for (const auto& book : library) {
        std::cout << book << "\n";
    }

    // Задание диапазона годов издания для поиска
    int startYear, endYear;
    std::cout << "\nВведите диапазон годов издания (начало и конец): ";
    std::cin >> startYear >> endYear;

    // Поиск книг в заданном диапазоне
    FindBooksInYearRange finder(startYear, endYear);
    std::vector<Book> foundBooks;

    // Используем std::copy_if для копирования подходящих книг в foundBooks
    std::copy_if(library.begin(), library.end(), std::back_inserter(foundBooks), finder);

    // Вывод найденных книг
    if (!foundBooks.empty()) {
        std::cout << "\nНайденные книги в диапазоне " << startYear << " - " << endYear << ":\n";
        for (const auto& book : foundBooks) {
            std::cout << book << "\n";
        }
    }
    else {
        std::cout << "\nКниг в указанном диапазоне не найдено.\n";
    }

    return 0;
}
