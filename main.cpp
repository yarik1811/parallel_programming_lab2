#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
#include <omp.h>

using namespace std;


int main()
{
    int** a, ** b, ** c;
    const char* path_1 = "C:\\Users\\User\\PycharmProjects\\parallel\\matrix1.txt";
    const char* path_2 = "C:\\Users\\User\\PycharmProjects\\parallel\\matrix2.txt";
    const char* res = "C:\\Users\\User\\PycharmProjects\\parallel\\res.txt";

    //-------------1 матрица---------------
    int col1;
    int row1;

    ifstream matrix_1;
    matrix_1.open(path_1);
    if (!matrix_1.is_open())
    {
        cout << "Error open [Matrix 1]" << endl;
    }
    else {

        matrix_1 >> row1;
        matrix_1 >> col1;

        // Память под элементы первой матрицы
        a = new int* [row1];
        for (int i = 0; i < row1; i++)
        {
            a[i] = new int[col1];
        }

        // Считывание элементов
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col1; j++)
            {
                matrix_1 >> a[i][j];
            }
        }
    }
    matrix_1.close();


    //-------------2 матрица---------------
    int col2;
    int row2;

    ifstream matrix_2;
    matrix_2.open(path_2);
    if (!matrix_2.is_open())
    {
        cout << "Error open [Matrix 2]" << endl;
    }
    else {

        matrix_2 >> row2;
        matrix_2 >> col2;

        // Память под элементы второй матрицы
        b = new int* [row2];
        for (int i = 0; i < row2; i++)
        {
            b[i] = new int[col2];
        }

        // Считывание элементов
        for (int i = 0; i < row2; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                matrix_2 >> b[i][j];
            }
        }
    }
    matrix_2.close();




    //-----------------------------------
    cout << "Matrix 1 ["<< row1 << " " << col1 << "]: " << endl;
    // Вывод элементов первой матрицы
    //for (int i = 0; i < row1; i++)
    //{
    //    for (int j = 0; j < col1; j++)
    //        cout << a[i][j] << " ";
    //    cout << endl;
    //}


    cout << "Matrix 2 ["<< row2 << " " << col2 << "]: " << endl;
    // Вывод элементов второй матрицы
    //for (int i = 0; i < row2; i++)
    //{
    //    for (int j = 0; j < col2; j++)
    //        cout << b[i][j] << " ";
    //    cout << endl;
    //}


    if (col1 != row2)
    {
        cout << "Cannot multiply matrices of specified sizes! ["<< row1 << " " << col1 << "] x [" << row2 << " " << col2 << "]: " << endl;
        return 0;
    }




    clock_t start;
    start  = clock();
    // Умножение матриц
    c = new int* [row1];
    for (int i = 0; i < row1; i++)
    {
        c[i] = new int[col2];
    }

    int threads;
    #pragma omp parallel shared(threads)
    {
        threads = omp_get_num_threads();

        #pragma for
        for (int i = 0; i < col2; i++) {
            for (int j = 0; j < col2; j++) {
                c[i][j] = 0;
                for (int k = 0; k < col1; k++)
                    c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    cout << endl << "Calculation time: " << double(clock() - start)/CLOCKS_PER_SEC << " seconds" << endl;

    // Вывод матрицы произведения
    ofstream out;
    out.open(res);
    if (out.is_open())
    {
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                out << c[i][j] << " ";
            }
            out << "\n";
        }
    }
    out.close();

    return 0;
}
