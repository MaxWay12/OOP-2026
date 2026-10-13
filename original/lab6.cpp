#include <iostream>
#include <limits>
#include <locale>
 
using namespace std;
 
template <class T>
class ElementArray
{
private:
    T* data;
    int size;
    T allowed[7];
 
    bool IsAllowed(T value) const
    {
        for (int i = 0; i < 7; i++)
        {
            if (value == allowed[i])
                return true;
        }
 
        return false;
    }
 
public:
    ElementArray(int n, const T allowedValues[7])
    {
        size = n;
        data = new T[size];
 
        for (int i = 0; i < 7; i++)
            allowed[i] = allowedValues[i];
    }
 
    void Read()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Элемент [" << i << "]: ";
 
            while (!(cin >> data[i]) || !IsAllowed(data[i]))
            {
                cout << "Ошибка. Повторите ввод: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
 
    void Print() const
    {
        for (int i = 0; i < size; i++)
            cout << data[i] << ' ';
 
        cout << endl;
    }
 
    void PrintRarest() const
    {
        int count[7] = { 0 };
 
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (data[i] == allowed[j])
                    count[j]++;
            }
        }
 
        int minimum = size + 1;
 
        for (int i = 0; i < 7; i++)
        {
            if (count[i] > 0 && count[i] < minimum)
                minimum = count[i];
        }
 
        cout << "Наиболее редко встречается: ";
 
        for (int i = 0; i < 7; i++)
        {
            if (count[i] == minimum)
                cout << allowed[i] << ' ';
        }
 
        cout << "(" << minimum << " раз)" << endl;
    }
 
    ~ElementArray()
    {
        delete[] data;
    }
};
 
int ReadSize(const char* message)
{
    int size;
    cout << message;
 
    while (!(cin >> size) || size <= 0)
    {
        cout << "Ошибка. Повторите ввод: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
 
    return size;
}
 
int main()
{
    setlocale(LC_ALL, "Russian");
 
    const int allowedNumbers[7] = { 0, 1, 2, 3, 4, 5, 6 };
    const char allowedSymbols[7] =
        { '0', '1', '2', 'A', 'B', 'C', 'D' };
 
    cout << "Работа с целыми числами" << endl;
    int numberCount = ReadSize("Введите количество элементов: ");
    ElementArray<int> numbers(numberCount, allowedNumbers);
    numbers.Read();
 
    cout << "Массив: ";
    numbers.Print();
    numbers.PrintRarest();
 
    cout << "\nРабота с символами" << endl;
    int symbolCount = ReadSize("Введите количество элементов: ");
    ElementArray<char> symbols(symbolCount, allowedSymbols);
    symbols.Read();
 
    cout << "Массив: ";
    symbols.Print();
    symbols.PrintRarest();
 
    return 0;
}
