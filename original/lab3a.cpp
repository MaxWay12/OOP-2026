#include <iostream>
#include <cstring>
#include <clocale>
 
using namespace std;
 
class Text
{
private:
    char value[256];
 
public:
    void read()
    {
        cout << "Введите текст: ";
        cin.getline(value, 256);
    }
 
    void removeExtraA()
    {
        char* source = value;
        char* result = value;
        bool previousWasA = false;
 
        while (*source != '\0')
        {
            if (*source != 'a' || !previousWasA)
            {
                *result = *source;
                result++;
            }
 
            previousWasA = (*source == 'a');
            source++;
        }
 
        *result = '\0';
    }
 
    void print()
    {
        cout << "Результат: " << value << endl;
    }
};
 
int main()
{
    setlocale(LC_ALL, "Russian");
 
    Text* text = new Text;
 
    text->read();
    text->removeExtraA();
    text->print();
 
    delete text;
    return 0;
}
