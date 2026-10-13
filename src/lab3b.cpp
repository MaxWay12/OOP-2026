#include <iostream>
#include <clocale>

namespace lab3b {


 
using namespace std;
 
class NumberArray
{
private:
    int size;
    double* numbers;
 
public:
    NumberArray(int n)
    {
        size = n;
        numbers = new double[size];
    }
 
    ~NumberArray()
    {
        delete[] numbers;
    }
 
    void read()
    {
        cout << "Введите " << size << " чисел: ";
 
        for (int i = 0; i < size; i++)
        {
            cin >> numbers[i];
        }
    }
 
    void transform()
    {
        double* result = new double[size];
        int position = 0;
 
        for (int i = 0; i < size; i++)
        {
            if (numbers[i] < 0)
            {
                result[position] = numbers[i];
                position++;
            }
        }
 
        for (int i = size - 1; i >= 0; i--)
        {
            if (numbers[i] >= 0)
            {
                result[position] = numbers[i];
                position++;
            }
        }
 
        for (int i = 0; i < size; i++)
        {
            numbers[i] = result[i];
        }
 
        delete[] result;
    }
 
    void print()
    {
        cout << "Преобразованная последовательность: ";
 
        for (int i = 0; i < size; i++)
        {
            cout << numbers[i] << " ";
        }
 
        cout << endl;
    }
};
 
int run()
{

 
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;
 
    if (n <= 0)
    {
        cout << "Количество должно быть положительным" << endl;
        return 0;
    }
 
    NumberArray* array = new NumberArray(n);
 
    array->read();
    array->transform();
    array->print();
 
    delete array;
    return 0;
}
}
