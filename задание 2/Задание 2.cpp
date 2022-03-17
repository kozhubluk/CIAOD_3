// Разработайте программу согласно задаче варианта, 
// используя для представления обрабатываемого в программе текста строку string, 
// стандартной библиотеки шаблонов. и возможности класса для выполнения действий со строкой.
// 
// Дано предложение, составленное из слов и групп цифр (считать тоже словами), 
// определяющих целые числа. Слова разделены запятой или одним или несколькими пробелами.
// Удалить из него слова, которые встретились там более одного раза и сформировать массив из чисел, встретившихся в тексте

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool it_digit(string a);
vector <int> num_digit(string a);
int word_count(string a, string b);
void del(string& a);
void print_arr(vector <int> arr, int n);

int main()
{
	string stroka;
	vector <int> numbers;
	cout << "Vvtdite predlozhenie, ispol`zuya v kachestve razdeliteley probely i zapyatye:\n";
	getline(cin, stroka);
	cout << "Massiv iz chisel, vstrechayushchihsya v preglozhenii:\n";
	numbers = num_digit(stroka);
	print_arr(numbers, numbers.size());
	cout << "Udalenie slov, kotorye vstrechayutsya bolee odnogo raza:\n";
	del(stroka);
	cout << stroka;
	return 0;
}


bool it_digit(string a) // Проверяет, является ли подстрока числом
{
	int n = a.size();
	for (int i = 0; i < n; i++)
	{
		if (!(int(a[i]) <= int('9') && int(a[i]) >= int('0')))
		{
			return false;
		}
	}
	return true;
}
vector <int> num_digit(string a) // Создает массив состоящих из числе, втсречающихся в предложении
{
	int n = a.length();
	vector <int> arr;
	int temp;
	string w = "";
	for (int i = 0; i < n; i++)
	{
		if (a[i] == ' ' || a[i] == ',' || a[i] == '.')
		{
			if (w.length() != 0 && it_digit(w) == true)
			{
				temp = stoi(w, 0, 10);
				arr.push_back(temp);
			}
			w = "";
		}
		else
		{
			w += a[i];
			if (i == n - 1 && it_digit(w) == true)
			{
				temp = stoi(w, 0, 10);
				arr.push_back(temp);
			}
		}
	}
	return arr;
}
int word_count(string a, string b) // Подсчитывает, сколько раз слово всречается в предложении
{
	int n = a.length();
	string w = "";
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == ' ' || a[i] == ',' || a[i] == '.')
		{
			if (w == b && w.size() != 0)
			{
				k++;
			}
			w = "";
		}
		else
		{
			w += a[i];
			if (i == n - 1 && w == b)
			{
				k++;
			}
		}
	}
	return k;
}
void del(string& a) // Удалаение повторяющихся слов из предложения 
{
	int n = a.length();
	string w = "";
	string new_a = "";
	for (int i = 0; i < n; i++)
	{
		if (a[i] == ' ' || a[i] == ',' || a[i] == '.')
		{
			if (!(word_count(a, w) > 1))
			{
				new_a += w;
			}
			new_a += a[i];
			w = "";
		}
		else
		{
			w += a[i];
			if (i == n - 1 && !(word_count(a, w) > 1))
			{
				new_a += w;
			}
		}
	}
	a = new_a;
}
void print_arr(vector <int> arr, int n) // Функция для вывода массива чисел
{
	for (int i = 0; i < n; i++)
	{
		cout << "arr[" << i + 1 << "] = " << arr[i] << endl;
	}
}