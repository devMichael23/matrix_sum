#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

// Создание матрицы на n строк, m столбцов
int** create_matrix(int n, int m)
{
    int** array = new int* [n];
    for (int i = 0; i < n; i++)
    {
        array[i] = new int[m];
    }

    // Заполнение рандомными числами от 0 до 20
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            array[i][j] = 0 + rand() % 20;
        }
    }


    return array;
}

// Вывод матрицы
void print_matrix(int** array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



int main() 
{
    int n = 50;
    int m = 50;
    int** matrix = create_matrix(n, m);
    int result = 0;

    for (int i = 0; i < n; i++) 
    {
        result += (matrix[i][i] + matrix[i][n - i - 1]);
    }

    //print_matrix(matrix, n, m);
    cout << endl;
    cout << result << endl;

    system("pause");

    return 0;
}