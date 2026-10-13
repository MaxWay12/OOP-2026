#include "labs.h"
#include <windows.h>
#include <iostream>
#include <limits>
#include <string>
#include <exception>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    using Runner = int (*)();
    const Runner runners[] = {lab1::run, lab2::run, lab3a::run,
        lab3b::run, lab4::run, lab5::run, lab6::run, lab7a::run, lab7b::run};
    while (true)
    {
        std::cout << "\nЛабораторные работы по ООП\n"
            "1 — ЛР 1: класс STRING (вариант 23)\n"
            "2 — ЛР 2: указатели (вариант 10)\n"
            "3 — ЛР 3, задание А: динамический объект Text\n"
            "4 — ЛР 3, задание Б: массив (вариант 12)\n"
            "5 — ЛР 4: наследование (вариант 23)\n"
            "6 — ЛР 5: перегрузка операций (вариант 23)\n"
            "7 — ЛР 6: шаблоны (вариант 25)\n"
            "8 — ЛР 7, задание А: потоки и строки\n"
            "9 — ЛР 7, задание Б: форматирование (вариант 16)\n"
            "0 — Выход\nВыберите пункт: ";
        std::string choice;
        if (!std::getline(std::cin, choice) || choice == "0") return 0;
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '9')
        {
            std::cout << "Введите номер от 0 до 9.\n";
            continue;
        }
        const int index = choice[0] - '1';
        const auto flags = std::cout.flags();
        const auto precision = std::cout.precision();
        const auto fill = std::cout.fill();
        bool failed = false;
        bool ended = false;
        try
        {
            // Stop on invalid input before report code can use unread values.
            std::cin.exceptions(std::ios::failbit | std::ios::badbit);
            if (runners[index]() != 0) std::cout << "Работа завершилась с ошибкой.\n";
        }
        catch (const std::exception& error)
        {
            failed = true;
            ended = std::cin.eof();
            std::cout << "Выполнение прервано: " << error.what() << '\n';
        }
        std::cin.exceptions(std::ios::goodbit);
        ended = ended || std::cin.eof();
        std::cin.clear();
        std::cout.flags(flags);
        std::cout.precision(precision);
        std::cout.fill(fill);
        if (ended) return 0;
        if (failed || index == 3 || index == 4 || index == 6 || index == 8)
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}
