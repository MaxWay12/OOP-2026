#pragma once

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
