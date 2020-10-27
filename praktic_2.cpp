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

// Подсчет суммы последовательной реализации
int get_result(int** matrix,int n)
{
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        result += (matrix[i][i] + matrix[i][n - i - 1]);
    }

    return result;
}


int main() 
{
    int n = 50;
    int** matrix = create_matrix(n, n);
    int result = 0;
    int i;

    omp_set_num_threads(16);
#pragma omp parallel for shared(matrix, result, n) private(i)
        for (i = 0; i < n; i++)
        {
            result += (matrix[i][i] + matrix[i][n - i - 1]);
        }

    int result_seq = get_result(matrix, n);
    cout << result_seq << endl;
    cout << result << endl;

    system("pause");

    return 0;
}