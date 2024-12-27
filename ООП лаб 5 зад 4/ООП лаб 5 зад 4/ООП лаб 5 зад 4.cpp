#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional> // Для std::greater<>, std::bind2nd

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
};

// Функтор для сравнения года издания книги с заданным значением
struct CompareYearWithValue : std::binary_function<Book, int, bool> {
    bool operator()(const Book& book, int year) const {
        return book.getYear() > year;
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
    library.emplace_back("The Road", "Cormac McCarthy", 2006);
    library.emplace_back("The Goldfinch", "Donna Tartt", 2013);
    library.emplace_back("The Fault in Our Stars", "John Green", 2012);
    library.emplace_back("The Girl on the Train", "Paula Hawkins", 2015);
    library.emplace_back("Gone Girl", "Gillian Flynn", 2012);

    // Подсчет количества книг, изданных новее 2009 года
    int targetYear = 2009;
    int count = std::count_if(
        library.begin(),
        library.end(),
        std::bind2nd(CompareYearWithValue(), targetYear)
    );

    // Вывод результата
    std::cout << "Количество книг, изданных новее " << targetYear << " года: " << count << std::endl;

    return 0;
}
