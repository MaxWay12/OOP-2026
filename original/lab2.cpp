#include <iostream>
#include <clocale>
 
class Text
{
private:
    char value[256];
 
public:
    Text()
    {
        value[0] = '\0';
    }
 
    void read()
    {
        std::cout << "Введите текст: ";
        std::cin.getline(value, 256);
    }






    void removeExtraA()
    {
        char* source = value;
        char* result = value;
        bool previousA = false;
 
        while (*source != '\0')
        {
            if (*source != 'a' || !previousA)
            {
                *result = *source;
                ++result;
            }
 
            previousA = (*source == 'a');
            ++source;
        }
 
        *result = '\0';
    }
 
    void print() const
    {
        std::cout << "Результат: " << value << '\n';
    }
};
 
int main()
{
    std::setlocale(LC_ALL, "Russian");
 
    Text text;
    text.read();
    text.removeExtraA();
    text.print();
    return 0;
}
