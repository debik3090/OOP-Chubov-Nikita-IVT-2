#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <limits>
#include <windows.h> 

// Исключение для перебора (bust)
class BustException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Перебор! Вы проиграли.";
    }
};

// Перечисление для мастей
enum class Suit {
    Hearts,    // ♥
    Diamonds,  // ♦
    Clubs,     // ♣
    Spades     // ♠
};

// Перечисление для рангов
enum class Rank {
    Two = 2, Three, Four, Five, Six, Seven,
    Eight, Nine, Ten, Jack, Queen, King, Ace
};

// Класс Карта
class Card {
private:
    Rank rank_;
    Suit suit_;

public:
    Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {}

    Rank getRank() const { return rank_; }
    Suit getSuit() const { return suit_; }

    // Дружественная функция для перегрузки оператора вывода
    friend std::wostream& operator<<(std::wostream& os, const Card& card);
};

// Перегрузка оператора вывода для класса Card
std::wostream& operator<<(std::wostream& os, const Card& card) {
    static const std::vector<std::wstring> rankStrings = {
        L"2", L"3", L"4", L"5", L"6", L"7",
        L"8", L"9", L"10", L"J", L"Q", L"K", L"A"
    };

    static const std::vector<std::wstring> suitStrings = {
        L"\u2665", // ♥
        L"\u2666", // ♦
        L"\u2663", // ♣
        L"\u2660"  // ♠
    };

    // Получаем индекс для ранга и масти
    int rankIndex = static_cast<int>(card.rank_) - 2; // Two=2
    int suitIndex = static_cast<int>(card.suit_);

    if (rankIndex >= 0 && rankIndex < rankStrings.size()) {
        os << rankStrings[rankIndex];
    }
    else {
        os << L"?";
    }

    if (suitIndex >= 0 && suitIndex < suitStrings.size()) {
        os << suitStrings[suitIndex];
    }
    else {
        os << L"?";
    }

    return os;
}

// Класс Колода
class Deck {
private:
    std::vector<Card> cards_;

public:
    Deck(int numCards = 52) {
        // Инициализируем колоду стандартными картами
        cards_.reserve(numCards);
        for (int i = 0; i < numCards; ++i) {
            Suit suit;
            if (i < 13) suit = Suit::Hearts;
            else if (i < 26) suit = Suit::Diamonds;
            else if (i < 39) suit = Suit::Clubs;
            else suit = Suit::Spades;

            Rank rank;
            int rankValue = (i % 13) + 2;
            if (rankValue <= 10)
                rank = static_cast<Rank>(rankValue);
            else if (rankValue == 11)
                rank = Rank::Jack;
            else if (rankValue == 12)
                rank = Rank::Queen;
            else if (rankValue == 13)
                rank = Rank::King;

            cards_.emplace_back(rank, suit);
        }

        // Перемешиваем колоду
        shuffle();
    }

    // Перемешивание колоды
    void shuffle() {
        static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
        std::shuffle(cards_.begin(), cards_.end(), rng);
    }

    // Раздача карты
    Card dealCard() {
        if (cards_.empty()) {
            throw std::out_of_range("Колода пуста!");
        }
        Card dealt = std::move(cards_.back());
        cards_.pop_back();
        return dealt;
    }

    // Количество оставшихся карт
    int remainingCards() const { return static_cast<int>(cards_.size()); }
};

// Класс Рука (Hand)
class Hand {
private:
    std::vector<Card> cards_;
    bool isSplit_;

public:
    Hand() : isSplit_(false) {}

    void addCard(const Card& card) { cards_.push_back(card); }

    // Неконстантный геттер для изменения карт
    std::vector<Card>& getCards() { return cards_; }

    // Константный геттер для чтения карт
    const std::vector<Card>& getCards() const { return cards_; }

    // Метод для удаления последней карты
    void removeLastCard() {
        if (!cards_.empty()) {
            cards_.pop_back();
        }
    }

    // Вычисление значения руки
    int getValue() const {
        int sum = 0;
        int aces = 0;

        // Используем std::for_each с лямбда-функцией
        std::for_each(cards_.begin(), cards_.end(), [&](const Card& card) {
            if (card.getRank() >= Rank::Two && card.getRank() <= Rank::Ten) {
                sum += static_cast<int>(card.getRank());
            }
            else if (card.getRank() == Rank::Jack || card.getRank() == Rank::Queen || card.getRank() == Rank::King) {
                sum += 10;
            }
            else if (card.getRank() == Rank::Ace) {
                sum += 11;
                aces++;
            }
            });

        // Если сумма > 21 и есть тузы, считать туз как 1
        while (sum > 21 && aces > 0) {
            sum -= 10;
            aces--;
        }

        return sum;
    }

    // Проверка на Blackjack
    bool isBlackjack() const {
        return cards_.size() == 2 && getValue() == 21;
    }

    // Проверка на возможность сплита
    bool canSplit() const {
        if (cards_.size() != 2)
            return false;
        Rank first = cards_[0].getRank();
        Rank second = cards_[1].getRank();
        return first == second;
    }

    // Установка флага сплита
    void setSplit(bool split) { isSplit_ = split; }

    bool isSplit() const { return isSplit_; }

    // Перегрузка оператора вывода для руки
    friend std::wostream& operator<<(std::wostream& os, const Hand& hand);
};

// Перегрузка оператора вывода для класса Hand
std::wostream& operator<<(std::wostream& os, const Hand& hand) {
    std::for_each(hand.cards_.begin(), hand.cards_.end(), [&](const Card& card) {
        os << card << L" ";
        });
    return os;
}

// Класс Игрок (Player)
class Player {
private:
    Hand hand_;
    double balance_;
    double currentBet_;
    std::vector<Hand> splitHands_;

public:
    Player(double balance = 100000.0) : balance_(balance), currentBet_(0.0) {}

    void placeBet(double bet) {
        if (bet > balance_) {
            throw std::invalid_argument("Недостаточно средств для ставки.");
        }
        currentBet_ = bet;
        balance_ -= bet;
    }

    void winBet(double amount) { balance_ += amount; }

    void loseBet() {} // Ставка уже вычтена при размещении

    double getBalance() const { return balance_; }

    double getCurrentBet() const { return currentBet_; }

    Hand& getHand() { return hand_; }

    const Hand& getHand() const { return hand_; }

    std::vector<Hand>& getSplitHands() { return splitHands_; }

    void addSplitHand(const Hand& hand) { splitHands_.push_back(hand); }

    void resetHands() {
        hand_ = Hand();
        splitHands_.clear();
    }
};

// Класс Дилер (Dealer)
class Dealer {
private:
    Hand hand_;

public:
    Dealer() {}

    void addCard(const Card& card) { hand_.addCard(card); }

    Hand& getHand() { return hand_; }

    const Hand& getHand() const { return hand_; }

    void resetHand() { hand_ = Hand(); }

    // Логика дилера: берет карты до тех пор, пока сумма < 17
    void play(Deck& deck) {
        while (hand_.getValue() < 17) {
            Card newCard = deck.dealCard();
            hand_.addCard(newCard);
            std::wcout << L"Дилер берет карту: " << newCard << L"\n";
        }
    }

    // Перегрузка оператора вывода для дилера
    friend std::wostream& operator<<(std::wostream& os, const Dealer& dealer);
};

// Перегрузка оператора вывода для класса Dealer
std::wostream& operator<<(std::wostream& os, const Dealer& dealer) {
    os << dealer.hand_;
    return os;
}

// Класс Игра (Game)
class Game {
private:
    std::vector<Deck> decks_;
    Player player_;
    Dealer dealer_;

public:
    Game(int numDecks = 4, int cardsPerDeck = 52) {
        decks_.reserve(numDecks);
        for (int i = 0; i < numDecks; ++i) {
            decks_.emplace_back(cardsPerDeck);
        }
    }

    // Получение колоды с наибольшим количеством карт
    Deck& getActiveDeck() {
        auto it = std::max_element(decks_.begin(), decks_.end(),
            [](const Deck& a, const Deck& b) {
                return a.remainingCards() < b.remainingCards();
            });
        return *it;
    }

    void start() {
        bool continuePlaying = true;
        while (continuePlaying) {
            try {
                playRound();
            }
            catch (const BustException& e) {
                std::wcerr << e.what() << std::endl;
                // Перебор уже обработан в evaluateHand, можно продолжить
            }
            catch (const std::exception& e) {
                std::wcerr << L"Ошибка: " << e.what() << std::endl;
            }

            if (player_.getBalance() <= 0) {
                std::wcout << L"Ваш баланс равен нулю. Игра окончена." << std::endl;
                break;
            }

            std::wcout << L"Хотите сыграть ещё? (y/n): ";
            wchar_t choice;
            std::wcin >> choice;
            if (choice != L'y' && choice != L'Y') {
                continuePlaying = false;
            }
        }
        std::wcout << L"Спасибо за игру! Ваш баланс: " << player_.getBalance() << std::endl;
    }

    void playRound() {
        player_.resetHands();
        dealer_.resetHand();

        // 1. Ввод ставки
        double bet;
        std::wcout << L"Ваша ставка? ";
        std::wcin >> bet;
        player_.placeBet(bet);

        // 2. Раздача начальных карт
        Hand& playerHand = player_.getHand();
        playerHand.addCard(getActiveDeck().dealCard());
        dealer_.addCard(getActiveDeck().dealCard());
        playerHand.addCard(getActiveDeck().dealCard());
        dealer_.addCard(getActiveDeck().dealCard());

        // 3. Вывод текущего состояния
        displayStatus();

        // 4. Проверка на Blackjack
        if (playerHand.isBlackjack()) {
            std::wcout << L"У вас Blackjack! Вы выиграли 1.5x ставки." << std::endl;
            player_.winBet(player_.getCurrentBet() * 1.5); // 3:2 выплаты
            return;
        }

        // 5. Ход игрока
        playerTurn(playerHand);

        // Обработка сплитов
        for (auto& splitHand : player_.getSplitHands()) {
            playerTurn(splitHand);
        }

        // 6. Ход дилера
        dealer_.play(getActiveDeck());

        // 7. Вывод рук дилера
        std::wcout << L"Дилер: " << dealer_ << L" (Сумма: " << dealer_.getHand().getValue() << L")" << std::endl;

        // 8. Вывод рук игрока
        std::wcout << L"Ваша рука: " << player_.getHand() << L" (Сумма: " << player_.getHand().getValue() << L")" << std::endl;
        for (size_t i = 0; i < player_.getSplitHands().size(); ++i) {
            std::wcout << L"Ваша сплит-рука " << i + 1 << L": " << player_.getSplitHands()[i] << L" (Сумма: " << player_.getSplitHands()[i].getValue() << L")" << std::endl;
        }

        // 9. Определение результатов
        determineResults();
    }

    void displayStatus() const {
        // Вывод количества оставшихся карт в каждой колоде
        std::wcout << L"Колоды: ";
        for (const auto& deck : decks_) {
            std::wcout << L"[" << deck.remainingCards() << L"] ";
        }
        std::wcout << std::endl;

        // Вывод карты дилера (первая карта видна, вторая скрыта)
        if (!dealer_.getHand().getCards().empty()) {
            std::wcout << L"Дилер: " << dealer_.getHand().getCards()[0] << L" ??" << std::endl;
        }
        else {
            std::wcout << L"Дилер: ?? ??" << std::endl;
        }

        // Вывод руки игрока
        std::wcout << L"Вы: " << player_.getHand() << std::endl;
    }

    void playerTurn(Hand& hand) {
        while (true) {
            std::wcout << L"1. Хватит\n2. Еще";
            if (hand.canSplit() && player_.getBalance() >= player_.getCurrentBet()) {
                std::wcout << L"\n3. Сплит";
            }
            std::wcout << L"\nВаш выбор: ";
            int choice;
            std::wcin >> choice;

            if (choice == 1) {
                break; // Стоп
            }
            else if (choice == 2) {
                // Еще (Hit)
                Card newCard = getActiveDeck().dealCard();
                hand.addCard(newCard);
                std::wcout << L"Вы получили: " << newCard << L"\n";
                std::wcout << L"Вы: " << hand << L" (Сумма: " << hand.getValue() << L")" << std::endl;

                // Проверка на перебор
                if (hand.getValue() > 21) {
                    throw BustException();
                }
            }
            else if (choice == 3 && hand.canSplit() && player_.getBalance() >= player_.getCurrentBet()) {
                // Сплит
                player_.placeBet(player_.getCurrentBet()); // Ставка на вторую руку
                Hand newHand = hand; // Создаем копию текущей руки
                newHand.removeLastCard(); // Удаляем последнюю карту из новой руки
                hand.removeLastCard(); // Удаляем последнюю карту из текущей руки

                // Добавляем по одной карте к каждой руке
                hand.addCard(getActiveDeck().dealCard());
                newHand.addCard(getActiveDeck().dealCard());

                // Добавляем новую руку в список сплитов
                player_.addSplitHand(newHand);

                std::wcout << L"Сплит выполнен.\n";
                std::wcout << L"Вы: " << hand << L" (Сумма: " << hand.getValue() << L")" << std::endl;
                std::wcout << L"Вторая рука: " << newHand << L" (Сумма: " << newHand.getValue() << L")" << std::endl;
            }
            else {
                std::wcout << L"Неверный выбор или недостаточно средств для сплита.\n";
            }
        }
    }

    void determineResults() {
        int dealerValue = dealer_.getHand().getValue();
        bool dealerBust = dealerValue > 21;

        // Основная рука игрока
        evaluateHand(player_.getHand(), dealerValue, dealerBust, player_.getCurrentBet());

        // Сплит руки
        for (auto& splitHand : player_.getSplitHands()) {
            evaluateHand(splitHand, dealerValue, dealerBust, player_.getCurrentBet());
        }
    }

    void evaluateHand(Hand& hand, int dealerValue, bool dealerBust, double bet) {
        int playerValue = hand.getValue();

        std::wcout << L"Ваша рука: " << hand << L" (Сумма: " << playerValue << L")" << std::endl;

        if (playerValue > 21) {
            std::wcout << L"Вы перебрали. Ставка потеряна.\n";
            // Ставка уже вычтена при размещении
        }
        else if (hand.isBlackjack() && !dealer_.getHand().isBlackjack()) {
            std::wcout << L"У вас Blackjack! Вы выиграли 1.5x ставки.\n";
            player_.winBet(bet * 1.5); // 3:2 выплаты
        }
        else if (dealer_.getHand().isBlackjack() && !hand.isBlackjack()) {
            std::wcout << L"У дилера Blackjack! Вы проиграли.\n";
            // Ставка уже вычтена
        }
        else if (dealerBust) {
            std::wcout << L"Дилер перебрал. Вы выиграли!\n";
            player_.winBet(bet * 2); // Возвращаем ставку и добавляем выигрыш
        }
        else if (playerValue > dealerValue) {
            std::wcout << L"Вы набрали больше, чем дилер. Вы выиграли!\n";
            player_.winBet(bet * 2);
        }
        else if (playerValue < dealerValue) {
            std::wcout << L"Вы набрали меньше, чем дилер. Вы проиграли.\n";
            // Ставка уже вычтена
        }
        else {
            std::wcout << L"Ничья. Ставка возвращена.\n";
            player_.winBet(bet); // Возвращаем ставку
        }
        std::wcout << L"Ваш баланс: " << player_.getBalance() << L"\n" << std::endl;
    }
};

int main() {
    // Установка кодовой страницы консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Установка локали на стандартную (для поддержки Unicode)
    std::locale::global(std::locale(""));

    // Настройка std::wcout для использования глобальной локали
    std::wcout.imbue(std::locale());

    // Создаем игру с 4 колодами по 52 карты
    Game game(4, 52);
    game.start();

    return 0;
}
