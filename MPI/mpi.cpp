#include <iostream>
#include "mpi.h"

using namespace std;

// Создание матрицы на raw строк, column столбцов
int** create_matrix(int raw, int column, int code = 0, int a = 0)
{
    int** matrix = new int* [raw];
    for (int i = 0; i < raw; i++)
    {
        matrix[i] = new int[column];
    }

    if (code == 1)
    {
        // Заполнение рандомными числами
        srand(time(0));
        for (int i = 0; i < raw; i++)
        {
            for (int j = 0; j < column; j++)
            {
                matrix[i][j] = 0 + rand() % 100;
            }
        }
    }
    if (code == 2)
    {
        // Заполнение определенным числом
        for (int i = 0; i < raw; i++)
        {
            for (int j = 0; j < column; j++)
            {
                matrix[i][j] = a;
            }
        }
    }

    return matrix;
}

// Вывод матрицы
void print_matrix(int** array, int raw, int column)
{
    for (int i = 0; i < raw; i++)
    {
        cout << "x[" << i << "] = ";
        for (int j = 0; j < column; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}


// Подсчет суммы диагональных значений матрицы
int get_result(int** matrix, int n)
{
    int result = 0;

    for (int i = 0; i < n; i++)
    {
        result += (matrix[i][i] + matrix[i][n - i - 1]);
    }

    return result;
}

void mpi_get_result(int** matrix, int n, int rank, int size)
{
    int count = n / size;
    int start = rank * count;
    int stop;
    int loc = 0;
    int glob = 0;
    double st = MPI_Wtime();
    
    if (rank < size - 1)
        stop = start + count;
    else if (rank == size - 1)
        stop = n;

    for (int i = start; i < stop; i++)
        loc += (matrix[i][i] + matrix[i][n - i - 1]);

    MPI_Reduce(&loc, &glob, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        double end = MPI_Wtime();
        double time = end - st;
        cout << "result = " << glob << "; time = " << time << endl;
    }
}

int main(int* argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
    int size, rank;
    int n = 3000;
    int** matrix = create_matrix(n, n, 1);


    MPI_Init(argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        cout << "Практическая работа №4" << endl;
        cout << "Распределенное программирование с использованием основ технологии MPI" << endl;
        cout << "Петрушинин Михаил" << endl;
    }

    

    if (rank == 1)
    {
        cout << endl;
        cout << "Последовательный метод вычисления:" << endl;
        cout << "n = " << n << endl;
        clock_t start = clock();

        int result = get_result(matrix, n);

        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "result = " << result << "; time = " << time << endl;
        cout << endl;
    }
    else
    {
        mpi_get_result(matrix, n, rank, size);
    }

    MPI_Finalize();

    return 0;
}