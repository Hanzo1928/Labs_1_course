#include <stdio.h>
#include "sort.h"

void getLine(char *str, const int size)         // Функция добавления ЗНАЧЕНИЯ элемента в очередь
{
    int cnt = 0, ch;                            // Переменная, определяющая число элементов во введенной строке

    while ((ch = getchar()) != '\n' && cnt < size - 1)  // Пока считанный символ != '\n' и количество элементов меньше допустимого
        str[cnt++] = ch;                                // Строка от cnt-символа равна считанному символу

    str[cnt] = '\0';
}


void print_menu() {                                             // Функция вывода меню
    printf("\nВыберите действие: \n");
    printf("1) Добавить элемент\n");
    printf("2) Удалить элемент\n");
    printf("3) Размер очереди\n");
    printf("4) Сортировка\n");
    printf("5) Печать\n");
    printf("0) Выход\n");
}


int main(void)
{
    const int N = 10;                            // Размер очереди (число элементов)
    int action;                                  // Аргумент конечного автомата
    char tmpCh;                                  // Используется для добавления элемента в очередь
    Udt udt;                                     // Структура очереди
    Item item;                                   // Структура элемента очереди

    udtCreate(&udt, N);                 // Функция создания очереди

    printf("Welcome to the program for processing queue!\n");
    print_menu();

    while ((action = getchar()) != EOF) {                            // Чтение символа из потока ввода
        if (action == '\n') continue;
        switch (action) {
            case '1':                                 // Случай с добавлением элемента
                printf("Введите ключ: ");
                scanf("%d", &item._key);           // Считывание ключа элемента очереди
                scanf("%c", &tmpCh);                // Хороший вопрос, что это за переменная
                printf("Введите Строку: ");
                getLine(item._val, sizeof(item._val));  // Считывание значение элемента (строки) очереди

                if (udtPush(&udt, item))              // Если постановка элемента в очередь прошло успешно, то вывод
                    printf("Элемент с ключом %d и строкой '%s' добавлен успешно\n", item._key, item._val);
                else
                    printf("Очередь заполнена\n");
                break;
            case '2':                                 // Случай с удалением элемента
                if (udtSize(&udt) > 0)          // Проверка, что очередь не пуста
                {
                    item = udtFront(&udt);      // Приравниваем item первый (самый старый) элемент очереди

                    udtPop(&udt);               // Функция извлечения из очереди первого элемента

                    printf("Элемент с ключом %d и строкой '%s' удален успешно\n", item._key, item._val);   // Вывод
                }
                else
                    printf("Очередь пуста\n");
            case '3':                                  // Случай с определением размера очереди
                printf("Размер очереди: %d (Реальный размер: %d)\n", udtSize(&udt), N);     // Функция определения реального размера
                break;
            case '4':                                     // Случай с сортировкой очереди
                if (udtSize(&udt) > 0) {            // Проверка, что очередь не пуста
                    udtSort(&udt);                  // Функция сортировки очереди
                }
                else
                    printf("Очередь пуста\n");
                break;
            case '5':                                 // Случай печати очереди
                if (udtSize(&udt) > 0)          // Проверка, что очередь не пуста
                {
                    printf("Очередь:\n");

                    udtPrint(&udt);             // Функция печати очереди
                }
                else
                    printf("Очередь пуста\n");
                break;
            case '0':
                printf("\nHave a nice day!\n");
                printf("                                                       \\   \\|'\n");
                printf("                                                        -\\  -|   |/\n");
                printf("                                                       _  \\/'|/ \\/.\n");
                printf("                                                        `--\\o|o)/_/--\n");
                printf("                                                            \\^ /\n");
                printf("                    ._                                 \\__` }v\\{   |/_\n");
                printf("               _   / /                                    \\_{\\/}---'\n");
                printf("            ('o_o)/_/               'Oo                     }  {\n");
                printf("               \\ /              (\\/   .-)                   {  }\n");
                printf("              / \\               `   .-\\`\\                  //|`\\\\\n");
                printf("\n");
                return 0;
            default:
                printf("The number you entered isn't in the menu :(\nPlease try again, in case you made a mistake\n");
                break;
        }
        print_menu();
    }
    udtDestroy(&udt);                           // Функция уничтожения ВСЕЙ очереди
    return 0;
}
