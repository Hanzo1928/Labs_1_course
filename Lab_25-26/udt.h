#ifndef UDT_H
#define UDT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Item                			// Описание структуры элемента очереди
{
    int _key;                    				// Номер элемента очереди
    char _val[81];                  			// Содержимое элемента очереди
} Item;

typedef Item UDT_TYPE;

typedef struct _Udt                 			// Описание структуры непосредственно очереди
{
    UDT_TYPE *_data;                			// Ссылка на структуру, содержащую номер и значение элемента очереди
    int _first;                     			// Первый элемент очереди
    int _size;                     				// Размер очереди (реальное количество элементов)
    int _capacity;                  			// Размер очереди (заранее определенное количество элементов (10))
} Udt;

void udtCreate(Udt *udt, const int size);		// Функция создания очереди
int udtSize(const Udt *udt);					// Функция определения реального размера очереди
int udtCapacity(const Udt *udt);				// Функция определения формального размера очереди
int udtEmpty(const Udt *udt);					// Проверка пустоты реального размера очереди
int udtPush(Udt *udt, const UDT_TYPE value);	// Операция постановки в очередь
UDT_TYPE udtFront(const Udt *udt);				// Функция, определяющая первый (самый старый) элемент
void udtPop(Udt *udt);							// Функция извлечения из очереди
void udtPrint(Udt *udt);						// Функция печати очереди
void udtDestroy(Udt *udt);						// Функция удаления ВСЕЙ очереди

#endif