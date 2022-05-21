#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Key                             // Структура ключа строки
{
    int key;                                    // Ключ строки
} Key;

typedef struct _Val                             // Структура содержания строки
{
    char val[81];                               // Содержание строки
} Val;

int comparator(const Key k1, const Key k2)      // Функция сравнения первого и второго ключа (1 - если второй >= первого, 0 - иначе)
{
    return k2.key >= k1.key;
}

int isEqualKeys(const Key k1, const Key k2)     // Функция проверки эквивалентности (1 - если равны, 0 - иначе)
{
    return k1.key == k2.key;
}

int randomAB(const int a, const int b)                  // Функция генерации случайного числа из диапазона от 0 до реального размера таблицы
{
    return a + rand() % (b - a + 1);
}

int isSorted(const Key *k, const int size)              // Функция проверки таблицы на отсортированность (указатель на структуру ключей и реальный размер)
{
    int i;

    for (i = 0; i < size - 1; i++)                      // Последовательная проверка всех элементов
        if (!comparator(k[i], k[i + 1]))         // Если первый ключ НЕ меньше или равен второму, то 0
            return 0;

    return 1;                                           // Иначе 1
}

void swapRows(Key *k, Val *v, const int a, const int b)     // Функция замены ключей и строк (меняет ключ и строку А на ключ и строку Б)
{
    Key tmpKey;             // Структура ключей
    Val tmpVal;             // Структура строк

    tmpKey = k[a];
    k[a] = k[b];
    k[b] = tmpKey;

    tmpVal = v[a];
    v[a] = v[b];
    v[b] = tmpVal;
}

void getRow(FILE *stream, char *str, const int size)        // Функция записи из потока в строку
{
    int cnt = 0;                                            // Количество считанных символов
    char ch;                                                // Считанный символ

    while ((ch = getc(stream)) != '\n' && cnt < size - 1)   // Пока указатель на символ потока не равен \n и номер элемента в строке меньше длины считанной строки
        str[cnt++] = ch;                                    // записываем в строку значение считанного из потока элемента

    str[cnt] = '\0';                                        // Присваиваем значение символа конца строки
}

void reverse(Key *k, Val *v, const int size)                // Функция построения обратной таблицы
{
    int i, j;

    for (i = 0, j = size - 1; i < j; i++, j--)
        swapRows(k, v, i, j);                         // Замена последней строки на первую и т.д.
}

void scramble(Key *k, Val *v, const int size)               // Функция случайного перемешивания строк в таблице
{
    int i, j, z;

    srand((unsigned int)time(0));                // Инициализация генерации случайных чисел

    for (z = 0; z < size; z++)
    {
        i = randomAB(0, size - 1);
        j = randomAB(0, size - 1);

        swapRows(k, v, i, j);                         // Функция замены местами строк А и Б в таблице
    }
}

void sort(Key *k, Val *v, const int size)
{
    int i;
    int left = 0;
    int right = size - 1;

    while (left < right)
    {
        for (i = right; i > left; i--)
            if (comparator(k[i], k[i-1]))       // возвращает true, если второй аргумент (k[i-1]) >= первого аргумента (k[i])
                swapRows(k, v, i, i-1);          // меняет местами ключи и строки на позициях i и i-1

        left++;

        for (i = left; i < right; i++)
            if (comparator(k[i+1], k[i]))       // возвращает true, если второй аргумент (k[i]) >= первого аргумента (k[i+1])
                swapRows(k, v, i, i+1);          // меняет местами ключи и строки на позициях i и i+1

        right--;
    }
}

int binSearch(const Key *k, const Val *v, const int size, const Key key)            // Функция поиска строки по введенному ключу
{
    int start = 0, end = size - 1, mid;

    if (size <= 0)                  // Если размер <= 0, то ничего
        return -1;

    while (start < end)             // Пока счетчик start меньше (реальный размер - 1)
    {
        mid = start + (end - start) / 2;    // mid = среднее арифметическое между счетчиком start и (реальный размер - 1)

        if (isEqualKeys(k[mid], key))   // Если ключ по среднему арифметическому равен введенному ключу
            return mid;                         // Возвращаем значение среднего арифметического
        else if (comparator(k[mid], key))   // Иначе, если введенный ключ >= среднего арифметического
            start = mid + 1;                        // счетчик старт = среднее арифметическое + 1
        else
            end = mid;                              // Иначе, если введенный ключ <= среднего арифметического, то end = среднее арифметическое
    }

    if (isEqualKeys(k[end], key))           // Если ключ от end равен введенному
        return end;                                // Возвращаем значение ключа end

    return -1;
}

void printTable(const Key *k, const Val *v, const int size)                         // Функция печати таблицы с ключами и значениями строки
{
    int i;

    printf("+--------+------------------------------------------------------------+\n");
    printf("|  Ключ  |                          Значение                          |\n");
    printf("+--------+------------------------------------------------------------+\n");

    for (i = 0; i < size; i++)
        printf("|%8d|%60s|\n", k[i].key, v[i].val);

    printf("+--------+------------------------------------------------------------+\n");
}

int main(void)
{
    const int N = 50;
    int i, cnt, action;
    char ch;
    Key keys[N];                                                    // Структура ключей
    Val values[N];                                                  // Структура значений
    Key key;
    char filename[40];                                              // Название считываемого файла
    printf("Enter the name of the file you want to print:\n");
    scanf("%s", filename);                                          // Считываем название
    FILE *file = fopen(filename, "r");                   // Открываем файл на чтение

    if (file == NULL)                                               // Проверка файла на пустоту
    {
        printf("Ошибка при открытии файла\n");

        return 0;
    }

    i = 0;

    while (i < N && fscanf(file, "%d", &keys[i].key) == 1)          // Пока номер строки меньше максимального (N) и fscanf считала значение (вернула 1)
    {
        fscanf(file, "%c", &ch);                                    // Считываем символ из файла
        getRow(file, values[i].val, sizeof(values[i].val));     // Запись считанных символов строки из потока в строку Val

        i++;                                                        // Увеличиваем счетчик считанных строк
    }

    fclose(file);                                                   // Закрываем файл

    cnt = i;                                                        // Запоминаем количество считанных строк

    do
    {
        printf("Меню\n");
        printf("1) Печать\n");
        printf("2) Двоичный поиск\n");
        printf("3) Сортировка\n");
        printf("4) Перемешивание\n");
        printf("5) Реверс\n");
        printf("6) Выход\n");
        printf("Выберите действие\n");
        scanf("%d", &action);

        switch (action)
        {
            case 1:
            {
                printTable(keys, values, cnt);          // Функция печати таблицы (50 максимально возможных ключей,
                break;                                            // 50 значений и реальное количество строк)
            }

            case 2:
            {
                if (!isSorted(keys, cnt))                         // Если таблица НЕ отсортирована
                    printf("Ошибка. Таблица не отсортирована\n");
                else
                {
                    printf("Введите ключ: ");
                    scanf("%d", &key.key);                                // Считываем ключ, по которому мы хотим найти строку

                    i = binSearch(keys, values, cnt, key);      // Поиск строки по ключу (на вход - структура ключей, строк, реальный размер и введенный ключ)

                    if (i > -1)                                           // Если функция вернула не -1, то нашлась строка по введенному ключу
                        printf("Найдена строка: %s\n", values[i].val);
                    else
                        printf("Строка с таким ключом не найдена\n");     // Иначе не нашлась
                }

                break;
            }

            case 3:
            {
                sort(keys, values, cnt);                        // Функция сортировки таблицы

                break;
            }

            case 4:
            {
                scramble(keys, values, cnt);                    // Функция случайного перемешивания строк в таблице
                                                                          // На вход - структура ключей, строк и реальное количество строк
                break;
            }

            case 5:
            {
                reverse(keys, values, cnt);                     // Функция построения обратной таблицы
                                                                          // На вход - структура ключей, строк и реальное количество строк
                break;
            }

            case 6: break;

            default:
            {
                printf("Ошибка. Такого пункта меню не существует\n");

                break;
            }
        }
    }
    while (action != 6);

    return 0;
}
