#include <iostream>
#include <time.h>
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

void do_test(int** matrix, int n, int threads)
{
    int result = 0;
    double st = omp_get_wtime();
#pragma omp parallel num_threads(threads)
    {
        result = 0;

    #pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            result += (matrix[i][i] + matrix[i][n - i - 1]);
        }

    }
    double end = omp_get_wtime();
    double sec = (end - st);
    cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "; Количество потоков = " << threads << endl;
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    int n = 1000;
    int** matrix = create_matrix(n, n);


    int threads = 1;
    do_test(matrix, n, threads);
    threads = 2;
    do_test(matrix, n, threads);

    system("pause");

    return 0;
}