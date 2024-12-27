#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cctype>
#include <stdexcept>

// Шаблонный класс DataManager<T>
template<typename T>
class DataManager {
private:
    std::vector<T> data_;        // Внутренний контейнер для хранения данных
    const size_t capacity_ = 64; // Максимальная вместимость
    const std::string dumpFile_; // Имя файла для сохранения данных

public:
    // Конструктор
    DataManager(const std::string& dumpFile = "dump.dat") : dumpFile_(dumpFile) {}

    // Метод для добавления одного элемента
    void push(T elem) {
        if (data_.size() < capacity_) {
            data_.push_back(elem);
        }
        else {
            dumpToFile();
            data_.clear();
            data_.push_back(elem);
        }
    }

    // Метод для добавления массива элементов
    void push(T elems[], size_t n) {
        if (n > capacity_) {
            throw std::invalid_argument("Количество добавляемых элементов превышает максимальную вместимость набора.");
        }

        if (data_.size() + n <= capacity_) {
            for (size_t i = 0; i < n; ++i) {
                data_.push_back(elems[i]);
            }
        }
        else {
            dumpToFile();
            data_.clear();
            for (size_t i = 0; i < n; ++i) {
                data_.push_back(elems[i]);
            }
        }
    }

    // Метод для чтения предпоследнего элемента без извлечения
    T peek() const {
        if (data_.size() < 2) {
            return T(); // Возвращает значение по умолчанию для типа T
        }
        return data_[data_.size() - 2];
    }

    // Метод для извлечения среднего элемента
    T pop() {
        if (data_.empty()) {
            throw std::out_of_range("Набор пуст. Невозможно выполнить pop().");
        }

        size_t size = data_.size();
        size_t mid;

        if (size % 2 == 0) {
            mid = size / 2 - 1; // Для четного числа элементов
        }
        else {
            mid = size / 2; // Для нечетного числа элементов
        }

        T removedElement = data_[mid];
        data_.erase(data_.begin() + mid);

        // Если удаляется последний элемент, загружаем данные из файла
        if (mid == size - 1 && !loadFromFile()) {
            // Файл пуст или не существует, ничего не делаем
        }

        return removedElement;
    }

    // Метод для получения всех элементов (для вывода)
    const std::vector<T>& getData() const {
        return data_;
    }

private:
    // Метод для сохранения данных в файл
    void dumpToFile() const {
        std::ofstream ofs(dumpFile_, std::ios::app);
        if (!ofs.is_open()) {
            std::cerr << "Ошибка: Не удалось открыть файл для записи: " << dumpFile_ << std::endl;
            return;
        }

        for (const auto& elem : data_) {
            ofs << elem << "\n";
        }

        ofs.close();
    }

    // Метод для загрузки данных из файла
    bool loadFromFile() {
        std::ifstream ifs(dumpFile_);
        if (!ifs.is_open()) {
            // Файл не существует или не открыт
            return false;
        }

        std::vector<T> tempData;
        std::string line;
        size_t count = 0;

        while (std::getline(ifs, line) && count < capacity_) {
            std::istringstream iss(line);
            T elem;
            if constexpr (std::is_same<T, char>::value) {
                if (!line.empty()) {
                    elem = line[0];
                    tempData.push_back(elem);
                    count++;
                }
            }
            else {
                iss >> elem;
                if (!iss.fail()) {
                    tempData.push_back(elem);
                    count++;
                }
            }
        }

        ifs.close();

        // Очистить файл после загрузки
        std::ofstream ofs(dumpFile_, std::ios::trunc);
        ofs.close();

        // Загрузить данные в набор
        data_ = tempData;
        return !tempData.empty();
    }
};

// Явная специализация шаблонного класса для типа char
template<>
class DataManager<char> {
private:
    std::vector<char> data_;        // Внутренний контейнер для хранения данных
    const size_t capacity_ = 64;    // Максимальная вместимость
    const std::string dumpFile_;     // Имя файла для сохранения данных

public:
    // Конструктор
    DataManager(const std::string& dumpFile = "dump.dat") : dumpFile_(dumpFile) {}

    // Метод для добавления одного символа с заменой пунктуации
    void push(char elem) {
        if (std::ispunct(static_cast<unsigned char>(elem))) {
            elem = '_';
        }

        if (data_.size() < capacity_) {
            data_.push_back(elem);
        }
        else {
            dumpToFile();
            data_.clear();
            data_.push_back(elem);
        }
    }

    // Метод для добавления массива символов с заменой пунктуации
    void push(char elems[], size_t n) {
        if (n > capacity_) {
            throw std::invalid_argument("Количество добавляемых элементов превышает максимальную вместимость набора.");
        }

        if (data_.size() + n <= capacity_) {
            for (size_t i = 0; i < n; ++i) {
                char elem = elems[i];
                if (std::ispunct(static_cast<unsigned char>(elem))) {
                    elem = '_';
                }
                data_.push_back(elem);
            }
        }
        else {
            dumpToFile();
            data_.clear();
            for (size_t i = 0; i < n; ++i) {
                char elem = elems[i];
                if (std::ispunct(static_cast<unsigned char>(elem))) {
                    elem = '_';
                }
                data_.push_back(elem);
            }
        }
    }

    // Метод для чтения предпоследнего элемента без извлечения
    char peek() const {
        if (data_.size() < 2) {
            return '\0'; // Возвращает нулевой символ, если элементов меньше 2
        }
        return data_[data_.size() - 2];
    }

    // Метод для извлечения среднего символа
    char pop() {
        if (data_.empty()) {
            throw std::out_of_range("Набор пуст. Невозможно выполнить pop().");
        }

        size_t size = data_.size();
        size_t mid;

        if (size % 2 == 0) {
            mid = size / 2 - 1; // Для четного числа элементов
        }
        else {
            mid = size / 2; // Для нечетного числа элементов
        }

        char removedElement = data_[mid];
        data_.erase(data_.begin() + mid);

        // Если удаляется последний элемент, загружаем данные из файла
        if (mid == size - 1 && !loadFromFile()) {
            // Файл пуст или не существует, ничего не делаем
        }

        return removedElement;
    }

    // Метод для извлечения среднего символа и приведения его к верхнему регистру
    char popUpper() {
        char elem = pop();
        return std::toupper(static_cast<unsigned char>(elem));
    }

    // Метод для извлечения среднего символа и приведения его к нижнему регистру
    char popLower() {
        char elem = pop();
        return std::tolower(static_cast<unsigned char>(elem));
    }

    // Метод для получения всех символов (для вывода)
    const std::vector<char>& getData() const {
        return data_;
    }

private:
    // Метод для сохранения данных в файл
    void dumpToFile() const {
        std::ofstream ofs(dumpFile_, std::ios::app);
        if (!ofs.is_open()) {
            std::cerr << "Ошибка: Не удалось открыть файл для записи: " << dumpFile_ << std::endl;
            return;
        }

        for (const auto& elem : data_) {
            ofs << elem << "\n";
        }

        ofs.close();
    }

    // Метод для загрузки данных из файла
    bool loadFromFile() {
        std::ifstream ifs(dumpFile_);
        if (!ifs.is_open()) {
            // Файл не существует или не открыт
            return false;
        }

        std::vector<char> tempData;
        std::string line;
        size_t count = 0;

        while (std::getline(ifs, line) && count < capacity_) {
            if (line.empty()) continue;
            char elem = line[0]; // Предполагается, что в файле по одному символу на строку
            tempData.push_back(elem);
            count++;
        }

        ifs.close();

        // Очистить файл после загрузки
        std::ofstream ofs(dumpFile_, std::ios::trunc);
        ofs.close();

        // Загрузить данные в набор
        data_ = tempData;
        return !tempData.empty();
    }
};

// Функция для вывода данных с помощью std::ostream_iterator
template<typename T>
void displayData(const DataManager<T>& manager) {
    const std::vector<T>& data = manager.getData();
    std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    try {
        // Демонстрация с типом int
        DataManager<int> intManager;
        int elems_int[] = { 1, 2, 3, 4, 5 };
        intManager.push(elems_int, 5);
        std::cout << "IntManager elements: ";
        displayData(intManager);

        // Демонстрация с типом double
        DataManager<double> doubleManager;
        double elems_double[] = { 1.1, 2.2, 3.3, 4.4 };
        doubleManager.push(elems_double, 4);
        std::cout << "DoubleManager elements: ";
        displayData(doubleManager);

        // Демонстрация с типом char
        DataManager<char> charManager;
        char elems_char[] = { 'a', 'b', 'c', '!', '@', 'd' };
        charManager.push(elems_char, 6);
        std::cout << "CharManager elements: ";
        displayData(charManager);

        // Использование метода peek()
        std::cout << "IntManager peek: " << intManager.peek() << std::endl;
        std::cout << "DoubleManager peek: " << doubleManager.peek() << std::endl;
        std::cout << "CharManager peek: " << charManager.peek() << std::endl;

        // Использование метода pop()
        std::cout << "IntManager pop: " << intManager.pop() << std::endl;
        std::cout << "DoubleManager pop: " << doubleManager.pop() << std::endl;
        std::cout << "CharManager pop: " << charManager.pop() << std::endl;

        // Специфические методы для char
        std::cout << "CharManager popUpper: " << charManager.popUpper() << std::endl;
        std::cout << "CharManager popLower: " << charManager.popLower() << std::endl;

        // Вывод данных после pop
        std::cout << "IntManager elements after pop: ";
        displayData(intManager);

        std::cout << "DoubleManager elements after pop: ";
        displayData(doubleManager);

        std::cout << "CharManager elements after pop: ";
        displayData(charManager);
    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}
