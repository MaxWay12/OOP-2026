#include <windows.h>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <string>
#include <clocale>

namespace lab1 {


class STRING
{
public:
    STRING();                  // Пустая строка
    STRING(char what);          // Строка из символа
    STRING(const STRING& what); // Независимая копия
    STRING& operator=(const STRING& what);
    ~STRING();                 // Освобождение памяти

    STRING Strcat(STRING what); // 4. Конкатенация
    STRING Setstr(STRING what); // 7. Замена строки
    STRING Strcat(char what);   // 8. Добавление символа
    void Print_at(unsigned x, unsigned y); // 12. Вывод

private:
    char* buf;    // Массив символов с завершающим нулем
    unsigned len; // Длина без завершающего нуля
};







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
int run()
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
}
