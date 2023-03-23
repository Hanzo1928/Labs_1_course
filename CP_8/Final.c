#include <stdio.h>
#include <stdlib.h>

typedef enum _kInd
{
    END = -1
} kInd;

typedef int LIST_TYPE;

typedef struct _Item
{
    LIST_TYPE _data;
    int _next;
} Item;

typedef struct _List
{
    Item *_arr;
    int _first;
    int _hole;
    int _capacity;      // заданный размер
    int _size;          // текущий размер
} List;

typedef struct _Iterator    // барьерный элемент с указателем на начало
{
    Item *_begin;
    int _index;
} Iterator;

LIST_TYPE itFetch(const Iterator *it)
{
    return it->_begin[it->_index]._data;
}

void listCreate(List *list, const int size)         // Функция создания списка
{
    int i;

    if (size < 1)                                   // Если допустимая длина списка меньше 1, то
        return;

    list->_arr = (Item *)malloc(sizeof(Item) * (size + 1)); // выделение памяти

    for (i = 0; i < size; i++)
    {
        list->_arr[i]._data = ' ';
        list->_arr[i]._next = i + 1;
    }

    list->_arr[size]._data = ' ';
    list->_arr[size]._next = END;
    list->_first = 0;
    list->_hole = 0;
    list->_size = 0;
    list->_capacity = size;
}   // функция создания списка

int findPrev(List *list, const int index)           // Поиск элемента в списке с введенным порядковым номером
{
    int i, prev = list->_first;

    if (index == 0)
        return END;

    for (i = 0; i < index - 1; i++)
        prev = list->_arr[prev]._next;

    return prev;
}

void listInsert(List *list, const int index, const LIST_TYPE value)     // Добавление элемента в список
{
    int prev, nextHole;

    if (list->_size == list->_capacity)
    {
        printf("Ошибка. Список полон\n");

        return;
    }

    if (list->_size)
    {
        if (index < 0 || index > list->_size)
        {
            printf("Ошибка. Позиция не найдена\n");

            return;
        }
    }
    else if (index != 0)
    {
        printf("Ошибка. Позиция не найдена\n");

        return;
    }

    nextHole = list->_arr[list->_hole]._next;   //Смещение пустоты на один элемент вправо

    if (index == 0)
    {
        list->_arr[list->_hole]._next = list->_first;   //Смещение пустоты на один элемент вправо
        list->_first = list->_hole;
    }
    else
    {
        prev = findPrev(list, index);
        list->_arr[list->_hole]._next = list->_arr[prev]._next;
        list->_arr[prev]._next = list->_hole;
    }

    list->_arr[list->_hole]._data = value;
    list->_hole = nextHole;
    list->_size++;

    printf("Элемент %s вставлен в список\n", value == 1 ? "true" : "false");
}

int listEmpty(const List *list)                 // Функция проверки списка на пустоту
{
    return list->_size == 0;
}

void listRemove(List *list, const int index)    // Функция удаления элемента из списка
{
    int prev, cur;

    if (listEmpty(list))
    {
        printf("Список пуст\n");

        return;
    }
    else if (index < 0 || index >= list->_size)
    {
        printf("Ошибка. Позиция не найдена\n");

        return;
    }

    if (index == 0)
    {
        cur = list->_first;
        list->_first = list->_arr[list->_first]._next;
    }
    else
    {
        prev = findPrev(list, index);
        cur = list->_arr[prev]._next;
        list->_arr[prev]._next = list->_arr[cur]._next;
    }

    printf("Элемент %s удален из списка\n", list->_arr[cur]._data == 1 ? "true" : "false");

    list->_arr[cur]._data = ' ';
    list->_arr[cur]._next = list->_hole;
    list->_hole = cur;
    list->_size--;
}

int listSize(const List *list)      // Число элементов в списке
{
    return list->_size;
}

void listPrint(const List *list)    // печать списка
{
    int i, cur = list->_first;

    if (listEmpty(list))
    {
        printf("Список пуст\n");

        return;
    }

    for (i = 0; i < list->_size; i++)
    {
        printf("%s ", list->_arr[cur]._data == 1 ? "true" : "false");

        cur = list->_arr[cur]._next;
    }

    printf("\n");
}

void listDestroy(List *list)        // Уничтожение списка
{
    if (list->_arr == NULL)
        return;

    free(list->_arr);

    list->_arr = NULL;
}

Iterator itFirst(const List *list)
{
    Iterator it;

    it._begin = list->_arr;
    it._index = list->_first;

    return it;
}

void itNext(Iterator *it)
{
    it->_index = it->_begin[it->_index]._next;
}

int main(void)
{
    const int N = 10;
    int i, isFound, action, pos, arg;
    char c;
    List list;
    Iterator it;

    listCreate(&list, N);

    while ((c = getchar()) != EOF)
    {
        printf("Меню:\n");
        printf("1) Вставить элемент\n");
        printf("2) Удалить элемент\n");
        printf("3) Печать списка\n");
        printf("4) Размер списка\n");
        printf("5) Выполнить задание над списком\n");
        printf("6) Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &action);

        switch (action)
        {
            case 1:
            {
                printf("Введите позицию элемента: ");
                scanf("%d", &pos);
                printf("Введите значение элемента (1 - true, 0 - false): ");
                scanf("%d", &arg);

                if (arg != 0 && arg != 1)
                    printf("Ошибка. Введено недопустимое значение\n");
                else
                    listInsert(&list, pos - 1, arg);

                break;
            }

            case 2:
            {
                printf("Введите номер элемента: ");
                scanf("%d", &pos);

                listRemove(&list, pos - 1);

                break;
            }

            case 3:
            {
                listPrint(&list);

                break;
            }

            case 4:
            {
                printf("Длина списка: %d\n", listSize(&list));

                break;
            }
            case 5:
            {
                printf("Введите значение: ");
                scanf("%d", &arg);

                if (arg != 0 && arg != 1)
                    printf("Ошибка. Введено недопустимое значение\n");
                else
                {
                    it = itFirst(&list);

                    isFound = 0;

                    for (i = 0; i < listSize(&list); i++)
                    {
                        if (itFetch(&it) == arg)
                        {
                            while (!listEmpty(&list))
                                listRemove(&list, 0);

                            isFound = 1;

                            break;
                        }

                        itNext(&it);
                    }

                    if (isFound)
                        printf("Список был очищен, так как в нем было найдено введенное значение\n");
                    else
                        printf("Список не был очищен, так как в нем не найдено введенное значение\n");
                }

                break;
            }

            case 6:
                return 0;

            default:
            {
                printf("Ошибка. Такого пункта меню не существует\n");

                break;
            }
        }
    }
    listDestroy(&list);

    return 0;
}
