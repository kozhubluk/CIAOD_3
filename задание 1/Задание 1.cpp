// Разработайте программу согласно задаче варианта, 
// используя для представления нуль терминальную строку. 
// Дано предложение, составленное из слов и групп цифр (считать тоже словами), 
// определяющих целые числа. Слова разделены запятой или одним или несколькими пробелами.
// Удалить из него слова, которые встретились там более одного раза и сформировать массив из чисел, встретившихся в тексте
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

char* get_string(int& len) // Ввод строки
{
    len = 0; 
    int v = 1;
    char* s = (char*)malloc(sizeof(char));
    char c = getchar(); // Переменная 'c', в которую будет записываться каждый новый символ
    while (c != '\n') { // Считываем текст, пока не встретим переход на новую строку
        s[len] = c;
        len++;
        if (len >= v) {
            v *= 2; 
            s = (char*)realloc(s, v * sizeof(char)); // Увеличиваем максимальный размер строки в 2 раза  
        }
        c = getchar();          
    }
    s[len] = '\0'; // Добавляем терминальный 0 в конец строки

    return s;
}
char* copy_str(char s[], int l)
{
    char* new_s = new char[l+1];
    int i = 0;
    while (i < l)
    {
        new_s[i] = s[i];
        i++;
    }
    new_s[l] = '\0';
    return new_s;
}
bool it_digit(char s[]) // Проверяет, является ли подстрока числом
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (!(int(s[i]) <= int('9') && int(s[i]) >= int('0')))
        {
            return false;
        }
    }
    return true;
}
bool check(char s1[], char s2[], int len) // Проверяет встречается ли слово больше 1 раза
{
    char* w = new char[len + 1];
    w[0] = '\0';
    int k = 0;
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (s1[i] == ' ' || s1[i] == ',' || s1[i] == '.')
        {
            if ((strcmp(w, s2) == 0) && w[0] != '\0')
            {
                k++;
            }
            w[0] = '\0';
            j = 0;
        }
        else
        {
            w[j] = s1[i];
            w[j + 1] = '\0';
            j++;
            if (i == (len - 1) && (strcmp(w, s2) == 0))
            {
                k++;
            }
        }
    }
    return k > 1;
}
vector <int> numbers(char str[], int len) // Создает массив состоящих из чисел, втсречающихся в предложении
{
    vector <int> arr;
    char* s = copy_str(str, len); 
    char split[] = " ,.";
    char* w = strtok(s, split);
    while (w != NULL)
    {
        if (it_digit(w))
        {
            arr.push_back(atoi(w));
        }
        w = strtok(NULL, split);	
    }
    delete[] s;
    return arr;
}
void print_arr(vector <int> arr, int n) // Функция для вывода массива чисел
{
    for (int i = 0; i < n; i++)
    {
        cout << "arr[" << i + 1 << "] = " << arr[i] << endl;
    }
}
char* new_stroka(char str[], int& len) // Удаление повторяющихся слов
{
    int k = 0;
    char* s = copy_str(str, len);
    char* new_str = new char[len + 1];
    char split[] = " ,.";
    char* w = strtok(s, split); // Считываем первое cлово предложения 
    int i = 0; // Номер символа в новой строке
    int j = 0; // Номер символа в исходной строке
    while (w != NULL || j < len)
    {   
        if (str[j] == '.' || str[j] == ' ' || str[j] == ',') //При встрече символа-разделителя, записываем его в новую строку
        {
            new_str[i] = str[j];
            i++;
            j++;
        }
        else
        {
            if (check(str, w, len)) // Проверяем, встречается ли >1 раза последнее считываемое слово
            {
                j = j + strlen(w); // Пропускаем слово, перемщаемся к соедующему разделителю
            }
            else // Посимвольно передаем новой строке каждый символ считанного слова
            {
                for (int k = 0; k < strlen(w); k++)
                {
                    new_str[i] = w[k];
                    i++;
                    j++;
                }
            }
            w = strtok(NULL, split); // Считываем очередное слово
        }
    }
    len = i;
    new_str[i] = '\0'; // Добавляем терминальный ноль в конец строки
    delete[] s;
    return new_str;
}

int main() {
    int size;
    char* str = get_string(size);
    cout << "Massiv chisel, vstretivshihsya v texte:\n";
    vector <int> num;
    num = numbers(str, size);
    print_arr(num, num.size());
    cout << endl << "____________________________" << endl;
    cout << "Udalenie povtoryayushchihsya slov iz ishodnogo texta:\n";
    str = new_stroka(str, size);
    cout << str;
    delete[] str;
    return 0;
}
