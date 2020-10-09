#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#define itmax 100


float c[itmax], x0[itmax], x0s[itmax], average_x[itmax];


// Функции
float f1(float x)
{
    return 3 * exp(x) - 5 * x - 3 - cos(exp(x));
}
float df1(float x)
{
    return 3 * exp(x) + exp(x) * sin(exp(x)) - 5;
}
float d2f1(float x)
{
    return exp(x) * (sin(exp(x)) + exp(x) * cos(exp(x)) + 3);
}

float f(float x)
{
    return pow(x, 6) + 12 * pow(x, 2) - 3 * x - 7;
}
float df(float x)
{
    return 6 * pow(x, 5) + 24 * x - 3;
}
float d2f(float x)
{
    return 30 * pow(x, 4) + 24;
}

//Запись с файла
void sourceDataRead(float *a, float *b, float *eps)
{
    setlocale(LC_ALL, "Rus");
    FILE  *data_file_1;

    char filename[] = "Data.txt";

    if ((data_file_1 = fopen(filename, "r")) == NULL)
    {
        printf("Не удалось открыть файл для чтения данных. Проверьте названия файла.\n");
        getchar();
        return 0;
    }

    printf("Файл успешно открыт. Чтение данных с файла...\n");

    data_file_1 = fopen("Data.txt", "rt");
    fscanf(data_file_1, "%f%f%f%d", a, b, eps);
    fclose(data_file_1);
}

//Вывод в консоль Data.txt
void sourceDataPrint(float a, float b, float eps) {
    printf("\n");
    printf("................................................................................\n");
    printf("Исходные данные: \n");
    printf("Граница a:     %f\n", a);
    printf("Граница b:     %f\n", b);
    printf("Точность eps:  %f\n", eps);
    printf("................................................................................\n");
    printf("\n");
}


void bisection_method(float a, float b, float eps, float* c)
{
    setlocale(LC_ALL, "Rus");

    int i = 0;
    if (f(a) * f(b) > 0) {
        printf("В методе половинного деления произошла ошибка: \n");
        printf("Условия не удовлятворяют теореме\n");
    }
    if (f(a) == f(b)) {
        printf("Корень найден.");
    }
    while (fabs(b - a) > 2 * eps) {
        i++;
        c[i - 1] = 0.5*(a + b);
        printf("%d.  x = %f\n", i, c[i - 1]);
        if (f(a) * f(c[i - 1]) < 0)
        {
            b = c[i - 1];
        }
        else
        {
            a = c[i - 1];
        }
    }
    printf("................................................................................\n");
}

void combined_method(float a, float b, float eps, float* x0, float* x0s, float* average_x)
{
    setlocale(LC_ALL, "Rus");

    int k = 0;


    x0[0] = a - ((b - a) * f(a) / (f(b) - f(a)));

    if (f(a) * d2f(a) > 0) {
        x0s[0] = a - f(a) / df(a);
        printf("Выполнено условие f(a)f''(a)>0\n");
    }
    if (f(b) * d2f(b) > 0) {
        x0s[0] = b - f(b) / df(b);
        printf("Выполнено условие f(b)f''(b)>0\n");
    }

    while ((fabs(x0[k] - x0s[k]) > 2 * eps)) {
        k++;

        x0[k] = x0[k - 1] - (x0s[k - 1] - x0[k - 1]) * f(x0[k - 1]) / (f(x0s[k - 1]) - f(x0[k - 1]));
        x0s[k] = x0s[k - 1] - f(x0s[k - 1]) / df(x0s[k - 1]);
        average_x[k] = (x0[k] + x0s[k]) / 2;

        printf("%d. x = %f ; x' = %f ; <x> = %f\n", k, x0[k], x0s[k], average_x[k]);
    }
    printf("................................................................................\n");
}


void SaveToFileBisection(float array[], int itcount)
{
    setlocale(LC_ALL, "Rus");

    int j;
    FILE* bisection;
    bisection = fopen("Bisection Results.txt", "w");
    for (j = 0; j <= itcount; j++)
    {
        fprintf(bisection, "%d. x = %f,   f(x) = %f  \n", j, array[j], f(array[j]));
    }
    fclose(bisection);
}

void SaveToFileCombined(float array[], int itcount)
{
    setlocale(LC_ALL, "Rus");

    int j;
    FILE* combined;
    combined = fopen("Combined Results.txt", "w");
    for (j = 0; j <= itcount; j++)
    {
        fprintf(combined, "%d. <x> = %f,   f(<x>) = %f  \n", j, array[j], f(array[j]));
    }
    fclose(combined);
}

main() {
    setlocale(LC_ALL, "Rus");

    float a, b, eps;
    float* x0, x0s;
    int i, k;

    sourceDataRead(&a, &b, &eps);
    sourceDataPrint(a, b, eps);
    
        printf("Метод:     1)  КАСАТЕЛЬНЫХ\n");
        bisection_method(a, b, eps, *&c, &i);
        SaveToFileBisection(c, i);

        printf("           2)  КОМБИНИРОВАННЫЙ\n");
        combined_method(a, b, eps, &x0, &x0s, &average_x, &k);
        SaveToFileCombined(average_x, k);

    getchar();
    return 0;
}