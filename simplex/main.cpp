#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    int numRows, numCols;
    int i = 0, j = 0;
    double** constraintMatrix;

    setlocale(LC_ALL, "Rus");

    printf("Введите количество ограничений: ");
    scanf("%d", &numRows); // Число ограничений
    numRows++; // Число строк

    printf("Введите количество базисных переменных: ");
    scanf("%d", &numCols); // Число переменных
    numCols += numRows; // Число столбцов

    constraintMatrix = (double**)malloc(numRows * sizeof(double*)); // Выделение памяти под n-строк

    for (i = 0; i < numRows; i++) {
        constraintMatrix[i] = (double*)malloc(numCols * sizeof(double)); // Выделение памяти для каждой строки по k-столбцов
    }

    for (i = 0; i < numRows; i++) {
        if (i < numRows - 1)
            printf("Введите коэффициенты %d-го ограничения\n", i + 1);
        else
            printf("Введите коэффициенты целевой функции в w-строке:\n");

        for (j = 0; j < numCols; j++) {
            printf("A[%d][%d] = ", i, j); // Ввод массива
            scanf("%lf", &constraintMatrix[i][j]);
        }
    }

    // Вывод массива
    printf("\n/------------------------------------------/\n");
    printf("Таблица:\n");
    int iLeadCol;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            printf(" %lf ", constraintMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n/------------------------------------------/\n");

    int numBaseVar = 0;
    numBaseVar = numCols - numRows + 1;

    // Определяем оптимальность решения
    int numPositive = 0;
    for (j = 0; j < numCols; j++) {
        if (constraintMatrix[numRows - 1][j] > 0)
            numPositive++;
    }

    while (numPositive < numBaseVar) {
        numPositive = 0;

        // Поиск ведущего столбца
        iLeadCol = 0;
        for (j = 1; j < numCols - numRows; j++)
            if (constraintMatrix[numRows - 1][j] < constraintMatrix[numRows - 1][iLeadCol])
                iLeadCol = j;
        printf("Ведущий столбец с %lf\n", constraintMatrix[numRows - 1][iLeadCol]);

        // Поиск ведущей строки
        int iLeadRow = 0;
        double curRatio = 0, minRatio = 0;
        minRatio = (constraintMatrix[iLeadRow][numCols - 1]) / (constraintMatrix[iLeadRow][iLeadCol]);
        for (i = 1; i < numRows - 1; i++) {
            curRatio = (constraintMatrix[i][numCols - 1]) / (constraintMatrix[i][iLeadCol]);
            if (curRatio < minRatio)
                iLeadRow = i;
        }
        printf("Ведущая строка с %lf (%d)\n", constraintMatrix[iLeadRow][numCols - 1], iLeadRow);
        printf("Делим ведущую строку на %lf (ведущий элемент)\n", constraintMatrix[iLeadRow][iLeadCol]);

        // Деление на выбранный элемент
        double leadEl = 0;
        leadEl = constraintMatrix[iLeadRow][iLeadCol];
        for (j = 0; j < numCols; j++) {
            constraintMatrix[iLeadRow][j] = constraintMatrix[iLeadRow][j] / leadEl;
        }
        printf("\n");

        // Вывод таблички
        printf("\n/------------------------------------------/\n");
        printf("\n");
        for (i = 0; i < numRows; i++) {
            for (j = 0; j < numCols; j++) {
                printf(" %lf ", constraintMatrix[i][j]);
            }
            printf("\n");
        }

        // Из элементов соответствующих строк вычитаем элементы найденной нам строки
        double divisor = 0;
        for (i = 0; i < numRows; i++) {
            divisor = constraintMatrix[i][iLeadCol];
            if (i != iLeadRow) {
                for (j = 0; j < numCols; j++) {
                    constraintMatrix[i][j] = constraintMatrix[i][j] - constraintMatrix[iLeadRow][j] * divisor;
                }
            }
        }

        // Вывод таблички снова
        printf("\n/------------------------------------------/\n");
        printf("\n");
        for (i = 0; i < numRows; i++) {
            for (j = 0; j < numCols; j++) {
                printf(" %lf ", constraintMatrix[i][j]);
            }
            printf("\n");
        }

        printf("\n/------------------------------------------/\n");
        for (j = 0; j < numCols; j++) {
            if (constraintMatrix[numRows - 1][j] > 0)
                numPositive++;
        }

        // Если в последней строчке положительных чисел столько, сколько было x, то мы нашли решение
    }
    printf("F(x) = %lf\n", constraintMatrix[numRows - 1][numCols - 1]);
}