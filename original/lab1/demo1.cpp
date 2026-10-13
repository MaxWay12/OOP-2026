#include "lab1.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

// Ввод печатных ASCII-символов. /q означает выход.
bool ReadText(const char* prompt, std::string& text)
{
    const unsigned MAX_LENGTH = 60;
    while (true)
    {
        std::cout << prompt;
        if (!std::getline(std::cin, text) || text == "/q")
            return false;
        bool valid = text.size() <= MAX_LENGTH;
        for (unsigned char symbol : text)
            if (symbol < 32 || symbol > 126) valid = false;
        if (valid) return true;
        std::cout << "Ошибка: до 60 печатных ASCII-символов.\n";
    }
}
// Создает объект из введенного текста методом 8.
STRING MakeString(const std::string& text)
{
    STRING result; // Результирующая строка
    for (char symbol : text) result.Strcat(symbol);
    return result;
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << "Операции над строками. Вариант 23.\n"
              << "Латинские буквы, цифры, пробелы и знаки.\n"
              << "Для выхода при любом вводе: /q.\n";
    try
    {
        std::string first, second, choice, character, line;
        // Тексты строк, команда, символ и строка координат
        while (true)
        {
            if (!ReadText("Первая строка: ", first) ||
                !ReadText("Вторая строка: ", second)) break;
            std::cout << "Введено: [" << first << "] и ["
                      << second << "]\n";
            std::cout << "1 - объединить; 2 - заменить;\n"
                      << "3 - добавить символ; 4 - повторить ввод.\n";
            do
            {
                if (!ReadText("Действие (1-4): ", choice))
                    return 0;
            } while (choice != "1" && choice != "2" &&
                     choice != "3" && choice != "4");
            if (choice == "4") continue;
            STRING left = MakeString(first); // Первая строка
            STRING right = MakeString(second); // Вторая строка
            if (choice == "1") left.Strcat(right);
            if (choice == "2") left.Setstr(right);
            if (choice == "3")
            {
                do
                {
                    if (!ReadText("Один символ: ", character))
                        return 0;
                } while (character.size() != 1);
                left.Strcat(character[0]);
            }
            while (true)
            {
                unsigned x, y; // Координаты вывода результата
                char extra; // Проверка лишних данных
                if (!ReadText("Координаты x y (от 0): ", line))
                    return 0;
                std::istringstream input(line);
                if (!(input >> x >> y) || (input >> extra))
                {
                    std::cout << "Введите два целых числа.\n";
                    continue;
                }
                try
                {
                    left.Print_at(x, y);
                    std::cout << '\n';
                    break;
                }
                catch (const std::out_of_range&)
                {
                    std::cout << "Строка выходит за буфер консоли.\n";
                }
            }
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
