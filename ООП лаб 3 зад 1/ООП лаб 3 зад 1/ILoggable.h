#pragma once
#include <string>

class ILoggable
{
public:
    virtual ~ILoggable() = default;

    //запись лога всего выражения на консоль
    virtual void logToScreen() const = 0;

    //добавление записи лога всего выражения в файл лога
    virtual void logToFile(const std::string& filename) const = 0;
};

