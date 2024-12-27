#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

// -----------------------------------------------------------
//ФАЙЛ С ПЬЕССОЙ 2.txt
// -----------------------------------------------------------

// Функция для преобразования строки в нижний регистр
std::string toLowerCase(const std::string& str) {
    std::string lowerStr;
    lowerStr.reserve(str.size());
    for (char ch : str) {
        lowerStr += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return lowerStr;
}

// Функция для разбивки строки на слова по заданным разделителям
std::vector<std::string> splitWords(const std::string& line, const std::string& delimiters) {
    std::vector<std::string> words;
    std::string word;
    for (char ch : line) {
        if (delimiters.find(ch) != std::string::npos) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }
    // Добавляем последнее слово, если оно существует
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

int main() {
    std::system("chcp 65001 > nul");
    std::setlocale(LC_ALL, "ru-RU");

    // Имя файла для чтения
    std::string filename;
    std::cout << "Введите имя текстового файла: ";
    std::getline(std::cin, filename);

    // Открытие файла
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
        return 1;
    }

    // Контейнер для хранения слов и их частот
    std::map<std::string, int> wordCount;

    // Заданные разделители
    std::string delimiters = " ., -:!;";

    std::string line;
    while (std::getline(infile, line)) {
        // Разбиваем строку на слова
        std::vector<std::string> words = splitWords(line, delimiters);
        for (const auto& word : words) {
            // Преобразуем слово в нижний регистр
            std::string lowerWord = toLowerCase(word);
            // Проверяем длину слова
            if (lowerWord.length() > 3) {
                // Увеличиваем счетчик для слова
                ++wordCount[lowerWord];
            }
        }
    }

    infile.close();

    // Вектор для хранения слов, удовлетворяющих условиям
    std::vector<std::pair<std::string, int>> filteredWords;

    for (const auto& pair : wordCount) {
        if (pair.second >= 7) {
            filteredWords.emplace_back(pair);
        }
    }

    // Проверка, есть ли слова, удовлетворяющие условиям
    if (filteredWords.empty()) {
        std::cout << "Нет слов, длина которых более 3 букв и встречающихся не менее 7 раз." << std::endl;
        return 0;
    }

    // Сортировка слов по убыванию частоты
    std::sort(filteredWords.begin(), filteredWords.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool {
            if (a.second != b.second)
                return a.second > b.second; // Сортировка по убыванию частоты
            return a.first < b.first;       // Если частоты равны, сортировка по алфавиту
        });

    // Вывод результатов
    std::cout << "\nСлова длиной более 3 букв, встречающиеся не менее 7 раз:\n";
    for (const auto& pair : filteredWords) {
        std::cout << pair.first << " : " << pair.second << " раз(а)" << std::endl;
    }

    return 0;
}
