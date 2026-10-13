#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <clocale>

namespace lab7a {





 
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
 
    STRING(const char* text)
    {
        len = static_cast<unsigned>(strlen(text));
        buf = new char[len + 1];
        strcpy_s(buf, len + 1, text);
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
 
    STRING Strcat(const STRING& other) const
    {
        char* result = new char[len + other.len + 1];
        strcpy_s(result, len + other.len + 1, buf);
        strcat_s(result, len + other.len + 1, other.buf);
 
        STRING newString(result);
        delete[] result;
        return newString;
    }
 
    STRING Strcat(char symbol) const
    {
        char text[2] = { symbol, '\0' };
        return Strcat(STRING(text));
    }
 
    friend istream& operator>>(istream& input,
                               STRING& text)
    {
        string value;
        getline(input >> ws, value);
        text = STRING(value.c_str());
        return input;
    }
 
    friend ostream& operator<<(ostream& output,
                               const STRING& text)
    {
        output << text.buf;
        return output;
    }
 
    ~STRING()
    {
        delete[] buf;
    }
};
 
int run()
{

 
    STRING first;
    STRING second;
 
    cout << "Введите первую строку: ";
    cin >> first;
 
    cout << "Введите вторую строку: ";
    cin >> second;
 
    STRING result = first.Strcat(' ').Strcat(second);
 
    cout << "Объединенная строка: " << result << endl;
 
    ofstream file("string_result.txt");
    if (file)
    {
        file << result << endl;
        cout << "Результат записан в файл "
             << "string_result.txt" << endl;
    }
    else
    {
        cout << "Не удалось открыть файл." << endl;
    }
 
    return 0;
}
}
