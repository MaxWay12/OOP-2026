#include <iostream>
#include <fstream>
#include <iomanip>
#include <clocale>
 
using namespace std;
 
void PrintFloat(ostream& output, float value)
{
    const int precision[3] = { 2, 0, 0 };
 
    for (int i = 0; i < 3; i++)
    {
        output << fixed << setprecision(precision[i])
               << setfill('*') << setw(9)
               << value << endl;
    }
}
 
void PrintResult(ostream& output, int i, float f1,
                 char c2, char c1, float f2)
{
    output << c2 << endl;
    PrintFloat(output, f1);
 
    output << uppercase << hex << setfill('*')
           << setw(9) << i << dec << nouppercase << endl;
 
    PrintFloat(output, f2);
    output << c1 << endl;
}
 
int main()
{
    setlocale(LC_ALL, "Russian");
 
    int i;
    float f1;
    float f2;
    char c1;
    char c2;
 
    cout << "Введите i, f1, c2, c1, f2: ";
    cin >> i >> f1 >> c2 >> c1 >> f2;
 
    if (!cin)
    {
        cout << "Ошибка ввода." << endl;
        return 1;
    }
 
    ofstream file("formatted_output.txt");
    if (!file)
    {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }
 
    cout << "\nРезультат:" << endl;
    PrintResult(cout, i, f1, c2, c1, f2);
    PrintResult(file, i, f1, c2, c1, f2);
 
    cout << "Результат записан в файл "
         << "formatted_output.txt" << endl;
    return 0;
}
