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

int do_test(int** matrix, int n, int threads)
{
    int result = 0;
    omp_set_num_threads(threads);
#pragma omp parallel
    {
        result = 0;

    #pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            result += (matrix[i][i] + matrix[i][n - i - 1]);
        }

    }
    
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n = 1500;
    int** matrix = create_matrix(n, n);
    int result = 0;
    int threads = 32;

    double start = clock();
    result = do_test(matrix, n, threads);
    double end = clock();
    double sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "; Количество потоков = " << threads << endl;

    threads = 16;
    start = clock();
    result = do_test(matrix, n, threads);
    end = clock();
    sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "; Количество потоков = " << threads << endl;

    threads = 8;
    start = clock();
    result = do_test(matrix, n, threads);
    end = clock();
    sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "; Количество потоков = " << threads << endl;

    threads = 4;
    start = clock();
    result = do_test(matrix, n, threads);
    end = clock();
    sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "; Количество потоков = " << threads << endl;

    threads = 1;
    start = clock();
    result = do_test(matrix, n, threads);
    end = clock();
    sec = (end - start) / CLOCKS_PER_SEC;
    cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "; Количество потоков = " << threads << endl;
    system("pause");

    return 0;
}