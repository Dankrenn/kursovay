#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Monoblocks {
    char fabricator[10];
    char OS[10];
    int RAM;
    char CPU[20];
    float screenDiagonal;
} monoblock_t;

monoblock_t* fill_monoblocks(monoblock_t* monoblocks, int size) {
    for (int i = 0; i < size; i++) {
        printf("������������� ���������: ");
        scanf("%9s", monoblocks[i].fabricator);
        getchar();

        printf("������������ �������: ");
        scanf("%9s", monoblocks[i].OS);
        getchar();

        printf("����������� ������(� ��): ");
        scanf("%d", &monoblocks[i].RAM);
        getchar();

        printf("������ ����������: ");
        fgets(monoblocks[i].CPU, sizeof(monoblocks[i].CPU), stdin);
        monoblocks[i].CPU[strcspn(monoblocks[i].CPU, "\n")] = 0;

        printf("��������� ������(� ������): ");
        scanf("%f", &monoblocks[i].screenDiagonal);
        getchar();
        printf("\n");
    }
    return monoblocks;
}

void print_monoblock(monoblock_t monoblocks) {
    printf("������������� ���������: %s\n", monoblocks.fabricator);
    printf("������������ �������: %s\n", monoblocks.OS);
    printf("����������� ������(� ��): %d\n", monoblocks.RAM);
    printf("������ ����������: %s\n", monoblocks.CPU);
    printf("��������� ������(� ������): %f\n", monoblocks.screenDiagonal);
    printf("\n");
}

int* search_monoblock(monoblock_t* monoblocks, int SIZE, char* OS, int RAM) {
    int* countOfSeeked = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        countOfSeeked[i] = -1;
    }
    if (OS[0] != '\0' && RAM != -1) {
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(monoblocks[i].OS, OS) == 0 && monoblocks[i].RAM == RAM) countOfSeeked[i] = i;
        }
    }
    else if (OS[0] != '\0' && RAM == -1) {
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(monoblocks[i].OS, OS) == 0) countOfSeeked[i] = i;
        }
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            if (monoblocks[i].RAM == RAM) countOfSeeked[i] = i;
        }
    }
    return countOfSeeked;
}

int compare_fabricator(const void* a, const void* b) {
    const monoblock_t* monoblock1 = (const monoblock_t*)a;
    const monoblock_t* monoblocks2 = (const monoblock_t*)b;
    return strcmp(monoblock1->fabricator, monoblocks2->fabricator);
}

int compare_CPU(const void* a, const void* b) {
    const monoblock_t* monoblock1 = (const monoblock_t*)a;
    const monoblock_t* monoblock2 = (const monoblock_t*)b;
    return strcmp(monoblock1->CPU, monoblock2->CPU);
}

monoblock_t* sort_monoblocks(monoblock_t* monoblocks, int size, int criteria) {
    if (criteria == 1) {
        qsort(monoblocks, size, sizeof(monoblock_t), compare_fabricator);
    }
    else if (criteria == 2) {
        qsort(monoblocks, size, sizeof(monoblock_t), compare_CPU);
    }
    else if (criteria == 3) {
        qsort(monoblocks, size, sizeof(monoblock_t), compare_fabricator);
        qsort(monoblocks, size, sizeof(monoblock_t), compare_CPU);
    }
    else {
        printf("������: �������� �������� ����������\n");
    }
    return monoblocks;
}

char* WriteFile(monoblock_t* monoblocks, int size) {
    FILE* fp = fopen("Coursework.txt", "w");
    if (fp == NULL) {
        return "������ �������� ����� ��� ������";
    }

    for (int i = 0; i < size; i++) {
        if (fprintf(fp, "������������� ���������: %s\n", monoblocks[i].fabricator) < 0 ||
            fprintf(fp, "������������ �������: %s\n", monoblocks[i].OS) < 0 ||
            fprintf(fp, "����������� ������(� ��): %d\n", monoblocks[i].RAM) < 0 ||
            fprintf(fp, "������ ����������: %s\n", monoblocks[i].CPU) < 0 ||
            fprintf(fp, "��������� ������(� ������): %f\n\n", monoblocks[i].screenDiagonal) < 0) {
            fclose(fp);
            return "������ ������ ������ � ����";
        }
    }

    fclose(fp);
    return NULL;
}

char* ReadFile(monoblock_t* monoblocks, int size) {
    FILE* fp = fopen("Coursework.txt", "r");
    if (fp == NULL) {
        return "�� ������� ������� ����";
    }


    for (int i = 0; i < size; i++) {
        if (fscanf(fp, "������������� ���������: %9s\n", monoblocks[i].fabricator) != 1 ||
            fscanf(fp, "������������ �������: %9s\n", monoblocks[i].OS) != 1 ||
            fscanf(fp, "����������� ������(� ��): %d\n", &monoblocks[i].RAM) != 1 ||
            fscanf(fp, "������ ����������: %19[^\n]\n", monoblocks[i].CPU) != 1 ||
            fscanf(fp, "��������� ������(� ������): %f\n\n", &monoblocks[i].screenDiagonal) != 1) 
        {
            fclose(fp);
            return "������ ��� ������ ������ �� �����";
        }
    }

    fclose(fp);
    return NULL;
}

monoblock_t* AddChangeNotes(monoblock_t* monoblocks, int num) {
    printf("������������� ���������: ");
    scanf("%9s", monoblocks[num].fabricator);
    getchar();

    printf("������������ �������: ");
    scanf("%9s", monoblocks[num].OS);
    getchar();

    printf("����������� ������(� ��): ");
    scanf("%d", &monoblocks[num].RAM);
    getchar();

    printf("������ ����������: ");
    fgets(monoblocks[num].CPU, sizeof(monoblocks[num].CPU), stdin);
    monoblocks[num].CPU[strcspn(monoblocks[num].CPU, "\n")] = 0;

    printf("��������� ������(� ������): ");
    scanf("%f", &monoblocks[num].screenDiagonal);
    getchar();
    printf("\n");
    return monoblocks;
}

monoblock_t* DeleteNotes(monoblock_t* monoblocks, int num, int SIZE)
{
    int n = num - 1;
    int size = SIZE - 1;
    monoblock_t* temp = malloc(size * sizeof(monoblock_t));
    if (temp == NULL) {
        printf("������ ��������� ������\n");
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        if (i < n) {
            temp[i] = monoblocks[i];
        }
        else if (i > n) {
            temp[i - 1] = monoblocks[i];
        }
    }
    monoblocks = realloc(monoblocks, size * sizeof(monoblock_t));
    for (int i = 0; i < size; i++) {
        monoblocks[i] = temp[i];
    }
    return monoblocks;
}

void main() {
    setlocale(LC_ALL, "Rus");
    int SIZE = 0;

    printf("������� ���������� �������: ");
    scanf("%d", &SIZE);
    int* countOfSeeked = malloc(SIZE * sizeof(int));
    monoblock_t* monoblocks = malloc(SIZE * sizeof(monoblock_t));
    monoblock_t* temp;
    int num = 0;
    char searchOS[20];
    char* error = NULL;
    int a = 1;
    while (a) {
        ReadFile(monoblocks, SIZE);
        printf("**********************************************\n");
        printf("*                     Menu                   *\n");
        printf("**********************************************\n");
        printf("* 1. ������� ������ �����.                   *\n");
        printf("* 2. ��������� ����� �� �����.               *\n");
        printf("* 3. ������ � ������ �����.                  *\n");
        printf("* 4. ����������� ������ �����.               *\n");
        printf("* 5. ��������� ������                        *\n");
        printf("**********************************************\n");
        scanf("%d", &num);
        switch (num) {
        case 1:
            num = 0;
            fill_monoblocks(monoblocks, SIZE);
            error = WriteFile(monoblocks, SIZE);
            if (error) {
                printf("������: %s\n", error);
            }
            else {
                printf("���� ������� �������\n");
            }
            break;
        case 2:
            num = 0;
            error = ReadFile(monoblocks, SIZE);
            if (error) {
                printf("������: %s\n", error);
                break;
            }
            int searchRAM;
            printf("**********************************************\n");
            printf("*                    ����� ��                *\n");
            printf("**********************************************\n");
            printf("* 1. ������������ �������.                   *\n");
            printf("* 2. ����������� ������.                     *\n");
            printf("* 3. ���������� � ����������� ������.        *\n");
            printf("* 4. ��������� � ����.                       *\n");
            printf("**********************************************\n");
            scanf("%d", &num);
            switch (num) {
            case 1:
                printf("������� �������� ������������ �������: ");
                getchar();
                fgets(searchOS, sizeof(searchOS), stdin);
                searchOS[strcspn(searchOS, "\n")] = 0; 
                searchRAM = -1;
                break;
            case 2:
                printf("������� ����� ����������� ������: ");
                scanf("%d", &searchRAM);
                searchOS[0] = '\0';
                break;
            case 3:
                getchar();
                printf("������� �������� ����������� �������: ");
                fgets(searchOS, sizeof(searchOS), stdin);
                searchOS[strcspn(searchOS, "\n")] = 0;
                printf("������� ����� ����������� ������: ");
                scanf("%d", &searchRAM);
                break;
            case 4:
                break;
            }
            countOfSeeked = search_monoblock(monoblocks, SIZE, searchOS, searchRAM);
            for (int i = 0; i < SIZE; i++) {
                if (countOfSeeked[i] != -1) print_monoblock(monoblocks[i]);
            }
            break;
        case 3:
            num = 0;
            printf("**********************************************\n");
            printf("*             ������ � ������ �����          *\n");
            printf("**********************************************\n");
            printf("* 1. �������� ������.                        *\n");
            printf("* 2. �������� ������.                        *\n");
            printf("* 3. ������� ������.                         *\n");
            printf("* 4. ������ �����.                           *\n");
            printf("* 5. ��������� � ����.                       *\n");
            printf("**********************************************\n");
            scanf("%d", &num);
            switch (num) {
            case 1:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                    break;
                }
                printf("������� ������� ������� �� ������ ��������: ");
                num = 0;
                scanf("%d", &num);
                SIZE += num;
                temp = malloc(SIZE * sizeof(monoblock_t));
                if (temp == NULL) {
                    printf("������ ��������� ������\n");
                    continue;

                }
                for (int i = 0; i < SIZE - num; i++) {
                    temp[i] = monoblocks[i];
                }
                for (int i = SIZE - num; i < SIZE; i++)
                {
                    AddChangeNotes(temp, i);
                }
                monoblocks = malloc(SIZE * sizeof(monoblock_t));
                for (int i = 0; i < SIZE; i++) {
                    monoblocks[i] = temp[i];
                }
                error = WriteFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                }
                else {
                    printf("������ ��������� � ���� �������\n");
                }
                break;
            case 2:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                    break;
                }
                num = 0;
                printf("������� ����� ������(%d) ��� � ���������:", SIZE);
                scanf("%d", &num);
                AddChangeNotes(monoblocks, num - 1);
                error = WriteFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                }
                else {
                    printf("������ ��������� � ���� �������\n");
                }
                break;
            case 3:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                    break;
                }
                num = 0;
                printf("������� ����� ������(%d) ��� � ��������:", SIZE);
                scanf("%d", &num);
                DeleteNotes(monoblocks, num, SIZE);
                SIZE -= 1;
                error = WriteFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                }
                else {
                    printf("������ ������� � ���� �������\n");
                }
                break;
            case 4:
                error = ReadFile(monoblocks, SIZE);
                if (error) {
                    printf("������: %s\n", error);
                }
                else {
                    printf("���� ������� ��������\n");
                    printf("\n");

                }
                for (int i = 0; i < SIZE; i++) print_monoblock(monoblocks[i]);
                break;
            case 5:
                break;
            }
            break;
        case 4:
            num = 0;
            printf("**********************************************\n");
            printf("*             ����������� ��                 *\n");
            printf("**********************************************\n");
            printf("* 1. �������������.                          *\n");
            printf("* 2. ���������.                              *\n");
            printf("* 3. ������������� � ���������� �������.   *\n");
            printf("* 4. ��������� � ����.                       *\n");
            printf("**********************************************\n");
            scanf("%d", &num);
            ReadFile(monoblocks, SIZE);
            switch (num) {
            case 1:
                sort_monoblocks(monoblocks, SIZE, num);
                WriteFile(monoblocks, SIZE);
                break;
            case 2:
                sort_monoblocks(monoblocks, SIZE, num);
                WriteFile(monoblocks, SIZE);
                break;
            case 3:
                sort_monoblocks(monoblocks, SIZE, num);
                WriteFile(monoblocks, SIZE);
                break;
            case 4:
                break;
            }

            break;
        case 5:
            a = 0;
            break;
        default:
            printf("�������� �����. ���������� �����.\n");
        }
    }
    free(monoblocks);
    free(countOfSeeked);
}