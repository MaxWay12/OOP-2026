#include <iostream>
#include <cstring>
#include <string>
#include <locale>
 
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
        STRING oneSymbol(symbol);
        return Strcat(oneSymbol);
    }
 
    STRING operator+(const STRING& other) const
    {
        return Strcat(other);
    }
 
    bool operator==(const STRING& other) const
    {
        return strcmp(buf, other.buf) == 0;
    }
 
    void Print() const
    {
        cout << buf;
    }
 
    ~STRING()
    {
        delete[] buf;
    }
};
 
int main()
{
    setlocale(LC_ALL, "Russian");
 
    string folderText;
    string fileNameText;
    string extensionText;
    string controlPathText;
 
    cout << "Введите папку без завершающего \\: ";
    getline(cin, folderText);
 
    cout << "Введите имя файла без расширения: ";
    getline(cin, fileNameText);
 
    cout << "Введите расширение без точки: ";
    getline(cin, extensionText);
 
    cout << "Введите полный путь для проверки: ";
    getline(cin, controlPathText);
 
    STRING folder(folderText.c_str());
    STRING fileName(fileNameText.c_str());
    STRING extension(extensionText.c_str());
    STRING controlPath(controlPathText.c_str());
    STRING separator('\\');
 
    STRING fileWithExtension =
        fileName.Strcat('.').Strcat(extension);
    STRING fullPath =
        folder + separator + fileWithExtension;
 
    cout << "\nСформированный путь: ";
    fullPath.Print();
 
    if (fullPath == controlPath)
        cout << "\nПуть указан правильно." << endl;
    else
        cout << "\nВведенный путь не совпадает "
             << "с результатом." << endl;
    return 0;
}
