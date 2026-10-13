#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>
#include <clocale>

namespace lab4 {





 
using namespace std;
 
class STRING
{
private:
    char* buf;
    unsigned len;
 
public:
    STRING()
    {
        len = 0;
        buf = new char[1];
        buf[0] = '\0';
    }
 
    STRING(char symbol)
    {
        len = 1;
        buf = new char[2];
        buf[0] = symbol;
        buf[1] = '\0';
    }
 
    STRING(const STRING& other)
    {
        len = other.len;
        buf = new char[len + 1];
        strcpy_s(buf, len + 1, other.buf);
    }
 
    STRING& operator=(const STRING& other)
    {
        if (this != &other)
        {
            delete[] buf;
            len = other.len;
            buf = new char[len + 1];
            strcpy_s(buf, len + 1, other.buf);
        }
 
        return *this;
    }
 
    virtual STRING Strcat(STRING other)
    {
        char* result = new char[len + other.len + 1];
        strcpy_s(result, len + other.len + 1, buf);
        strcat_s(result, len + other.len + 1, other.buf);
 
        delete[] buf;
        buf = result;
        len = len + other.len;
 
        return *this;
    }
 
    virtual STRING Setstr(STRING other)
    {
        *this = other;
        return *this;
    }
 
    virtual STRING Strcat(char symbol)
    {
        STRING oneSymbol(symbol);
        return STRING::Strcat(oneSymbol);
    }
 
    virtual void Print_at(unsigned x, unsigned y)
    {
        HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD position;
        position.X = static_cast<SHORT>(x);
        position.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(screen, position);
        cout << buf;
    }
 
    virtual ~STRING()
    {
        delete[] buf;
    }
};
 
class CHILD_STRING : public STRING
{
public:
    STRING Strcat(STRING other) override
    {
        cout << "CHILD_STRING::Strcat(STRING)" << endl;
        return STRING::Strcat(other);
    }
 
    STRING Setstr(STRING other) override
    {
        cout << "CHILD_STRING::Setstr" << endl;
        return STRING::Setstr(other);
    }
 
    STRING Strcat(char symbol) override
    {
        cout << "CHILD_STRING::Strcat(char)" << endl;
        return STRING::Strcat(symbol);
    }
 
    void Print_at(unsigned x, unsigned y) override
    {
        cout << "CHILD_STRING::Print_at" << endl;
        STRING::Print_at(x, y);
    }
};
 
STRING MakeString(const string& text)
{
    STRING result;
 
    for (char symbol : text)
    {
        result.Strcat(symbol);
    }
 
    return result;
}
 
int run()
{

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
 
    string firstText;
    string secondText;
    char symbol;
    unsigned x;
    unsigned y;
 
    cout << "Введите первую строку: ";
    getline(cin, firstText);
 
    cout << "Введите вторую строку: ";
    getline(cin, secondText);
 
    cout << "Введите добавляемый символ: ";
    cin >> symbol;
 
    cout << "Введите координаты x и y: ";
    cin >> x >> y;
 
    STRING first = MakeString(firstText);
    STRING second = MakeString(secondText);
    STRING* text = new CHILD_STRING;
 
    text->Setstr(first);
    text->Strcat(second);
    text->Strcat(symbol);
    text->Print_at(x, y);
 
    cout << endl;
    delete text;
    return 0;
}
}
