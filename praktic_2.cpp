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

    return array;
}

// Заполнение матрицы рандомными числами от 0 до 20
int** rand_matrix(int** matrix, int n, int m)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = 0 + rand() % 20;
        }
    }

    return matrix;
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

// Подсчет суммы диагональных значений матрицы
int get_result(int** matrix, int n, int threads)
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
    cout << "Практическая работа №2" << endl;
    cout << "Параллельное программирование с использованием технолгии OpenMP" << endl;
    cout << "Петрушинин Михаил\n" << endl;
    int choose;
    cout << "1 - Заполнить матрицу в ручную.\n2 - Заполнить матрицу автоматически\n> ";
    cin >> choose;
    int** matrix;
    int result = 0;
    int threads = 0;

    if (choose == 1)
    {
        int n;
        cout << "\nВведите размер квадратной матрицы:\n> ";
        cin >> n;
        matrix = create_matrix(n, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << "Введите x" << i << "y" << j << "\n> ";
                cin >> matrix[i][j];
            }
        }

        threads = 1;
        double start = clock();
        result = get_result(matrix, n, threads);
        double end = clock();
        double sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 2;
        start = clock();
        result = get_result(matrix, n, threads);
        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 4;
        start = clock();
        result = get_result(matrix, n, threads);
        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 8;
        start = clock();
        result = get_result(matrix, n, threads);
        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 16;
        start = clock();
        result = get_result(matrix, n, threads);
        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 32;
        start = clock();
        result = get_result(matrix, n, threads);
        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;
    }
    else if (choose == 2)
    {
        int n;
        cout << "\nВведите размер квадратной матрицы:\n> ";
        cin >> n;
        matrix = create_matrix(n, n);
        matrix = rand_matrix(matrix, n, n);

        threads = 1;
        double start = clock();

        result = get_result(matrix, n, threads);

        double end = clock();
        double sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 2;
        start = clock();

        result = get_result(matrix, n, threads);

        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 4;
        start = clock();

        result = get_result(matrix, n, threads);

        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 8;
        start = clock();

        result = get_result(matrix, n, threads);

        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 16;
        start = clock();

        result = get_result(matrix, n, threads);

        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;

        threads = 32;
        start = clock();

        result = get_result(matrix, n, threads);

        end = clock();
        sec = (end - start);
        cout << "Сумма диагональныйх элементов = " << result << "; Время = " << sec << "ms; Количество потоков = " << threads << endl;
    }

    system("pause");
    return 0;
}
