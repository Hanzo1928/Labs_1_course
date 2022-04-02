#!/bin/bash 

# Сравнение указанного файла со всеми другими файлами,
# имеющими такой же суффикс, с удалением совпадающих файлов.

if [ $# -eq 0 ]
then
    while [ -z $fl ]
    do
 echo -n "Не был указан файл и суффикс. Введите название файла и суффикс: "
 read  fl suf
    done
fi
if [ $# -le 1 -a "$1" != "?" ]
then
    while [ -z $suf ]
    do
 echo -n "Файл был указан, но суффикс неизвестен. Введите суффикс: "
 read suf
    done
fi
if [ $# -gt 2 ]
then
    while [ -z $suf ]
    do
 echo -n "Неверное количество аргументов. Введите корректное число аргументов: "
 read  fl suf
 done
fi
if [ "$1" = "?" ]
then
    echo "Формат ввода: $0 имя_файла суффикс(расширение файла без точки)"
fi

if [ -z $fl ]
then
    fl=$1
fi
if [ -z $suf ]
then
    suf=$2
fi

rm -r -f lab21

if [ "$fl" != "?" ]
then
    echo "Заданный файл: " $fl
    echo "Заданный суффикс: " ".$suf"
    echo
 
    mkdir -p $pwd lab21
    mkdir -p $pwd del
 
    find . -type f -name "*.$suf" 2>/dev/null -exec cp {} $pwd lab21 \;

    for var in $(ls lab21)
    do
 if cmp -s $fl $var
 then
     cp $pwd lab21/$var $pwd del
     rm -f $pwd lab21/$var
 fi
    done

    cp $fl $pwd lab21
    rm -f $pwd del/$fl

    for file in $(ls del)
    do
 echo "Совпадающий с заданным файл, который был удален: " $file
    done
       
    echo
       
    for object in $(ls lab21)
    do
 echo "Заданный файл/Уникальный файл, имеющий заданный суффикс: " $object
    done
       
    echo
    echo "Папка, содержащая уникальные файлы: lab21"
       
    rm -r -f $pwd del
fi
