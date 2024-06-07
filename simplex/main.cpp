#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    int numRows, numCols;
    int i = 0, j = 0;
    double** constraintMatrix;

    setlocale(LC_ALL, "Rus");

    printf("������� ���������� �����������: ");
    scanf("%d", &numRows); // ����� �����������
    numRows++; // ����� �����

    printf("������� ���������� �������� ����������: ");
    scanf("%d", &numCols); // ����� ����������
    numCols += numRows; // ����� ��������

    constraintMatrix = (double**)malloc(numRows * sizeof(double*)); // ��������� ������ ��� n-�����

    for (i = 0; i < numRows; i++) {
        constraintMatrix[i] = (double*)malloc(numCols * sizeof(double)); // ��������� ������ ��� ������ ������ �� k-��������
    }

    for (i = 0; i < numRows; i++) {
        if (i < numRows - 1)
            printf("������� ������������ %d-�� �����������\n", i + 1);
        else
            printf("������� ������������ ������� ������� � w-������:\n");

        for (j = 0; j < numCols; j++) {
            printf("A[%d][%d] = ", i, j); // ���� �������
            scanf("%lf", &constraintMatrix[i][j]);
        }
    }

    // ����� �������
    printf("\n/------------------------------------------/\n");
    printf("�������:\n");
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

    // ���������� ������������� �������
    int numPositive = 0;
    for (j = 0; j < numCols; j++) {
        if (constraintMatrix[numRows - 1][j] > 0)
            numPositive++;
    }

    while (numPositive < numBaseVar) {
        numPositive = 0;

        // ����� �������� �������
        iLeadCol = 0;
        for (j = 1; j < numCols - numRows; j++)
            if (constraintMatrix[numRows - 1][j] < constraintMatrix[numRows - 1][iLeadCol])
                iLeadCol = j;
        printf("������� ������� � %lf\n", constraintMatrix[numRows - 1][iLeadCol]);

        // ����� ������� ������
        int iLeadRow = 0;
        double curRatio = 0, minRatio = 0;
        minRatio = (constraintMatrix[iLeadRow][numCols - 1]) / (constraintMatrix[iLeadRow][iLeadCol]);
        for (i = 1; i < numRows - 1; i++) {
            curRatio = (constraintMatrix[i][numCols - 1]) / (constraintMatrix[i][iLeadCol]);
            if (curRatio < minRatio)
                iLeadRow = i;
        }
        printf("������� ������ � %lf (%d)\n", constraintMatrix[iLeadRow][numCols - 1], iLeadRow);
        printf("����� ������� ������ �� %lf (������� �������)\n", constraintMatrix[iLeadRow][iLeadCol]);

        // ������� �� ��������� �������
        double leadEl = 0;
        leadEl = constraintMatrix[iLeadRow][iLeadCol];
        for (j = 0; j < numCols; j++) {
            constraintMatrix[iLeadRow][j] = constraintMatrix[iLeadRow][j] / leadEl;
        }
        printf("\n");

        // ����� ��������
        printf("\n/------------------------------------------/\n");
        printf("\n");
        for (i = 0; i < numRows; i++) {
            for (j = 0; j < numCols; j++) {
                printf(" %lf ", constraintMatrix[i][j]);
            }
            printf("\n");
        }

        // �� ��������� ��������������� ����� �������� �������� ��������� ��� ������
        double divisor = 0;
        for (i = 0; i < numRows; i++) {
            divisor = constraintMatrix[i][iLeadCol];
            if (i != iLeadRow) {
                for (j = 0; j < numCols; j++) {
                    constraintMatrix[i][j] = constraintMatrix[i][j] - constraintMatrix[iLeadRow][j] * divisor;
                }
            }
        }

        // ����� �������� �����
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

        // ���� � ��������� ������� ������������� ����� �������, ������� ���� x, �� �� ����� �������
    }
    printf("F(x) = %lf\n", constraintMatrix[numRows - 1][numCols - 1]);
}