#include "lab1.h"
#include <windows.h>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

STRING::STRING() : buf(new char[1]), len(0)
{
    buf[0] = '\0';
}

STRING::STRING(char what) : buf(new char[2]), len(0)
{
    buf[0] = what;
    len = (what == '\0') ? 0 : 1;
    buf[len] = '\0';
}

STRING::STRING(const STRING& what)
    : buf(new char[what.len + 1]), len(what.len)
{
    std::memcpy(buf, what.buf, len + 1);
}

// Вход: исходная строка. Результат: ссылка на себя.
STRING& STRING::operator=(const STRING& what)
{
    if (this != &what)
    {
        char* copy = new char[what.len + 1]; // Новый буфер
        std::memcpy(copy, what.buf, what.len + 1);
        delete[] buf;
        buf = copy;
        len = what.len;
    }
    return *this;
}

STRING::~STRING()
{
    delete[] buf;
}

// Вход: добавляемая строка. Изменяет текущий объект.
// Возвращает независимую копию полученной строки.
STRING STRING::Strcat(STRING what)
{
    if (what.len > (std::numeric_limits<unsigned>::max)()
                   - len - 1)
        throw std::length_error("String is too long");
    unsigned size = len + what.len; // Новая длина
    char* joined = new char[size + 1]; // Новый буфер
    std::memcpy(joined, buf, len);
    std::memcpy(joined + len, what.buf, what.len + 1);
    delete[] buf;
    buf = joined;
    len = size;
    return *this;
}

// Вход: новая строка. Результат: копия текущей строки.
STRING STRING::Setstr(STRING what)
{
    *this = what;
    return *this;
}

// Вход: символ. Нулевой символ не увеличивает строку.
// Результат: копия строки после добавления символа.
STRING STRING::Strcat(char what)
{
    return Strcat(STRING(what));
}

// x, y: координаты буфера консоли, начиная с нуля.
// Выводит строку без переноса; возвращаемого значения нет.
void STRING::Print_at(unsigned x, unsigned y)
{
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info; // Размеры буфера
    if (!GetConsoleScreenBufferInfo(screen, &info))
        throw std::runtime_error("Windows console required");
    if (x >= static_cast<unsigned>(info.dwSize.X) ||
        y >= static_cast<unsigned>(info.dwSize.Y) ||
        len > static_cast<unsigned>(info.dwSize.X) - x)
        throw std::out_of_range("Text outside console buffer");
    COORD position = {static_cast<SHORT>(x),
                      static_cast<SHORT>(y)};
    std::cout.flush();
    if (!SetConsoleCursorPosition(screen, position))
        throw std::runtime_error("Cannot move cursor");
    std::cout << buf << std::flush;
}
