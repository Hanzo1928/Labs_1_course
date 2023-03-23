// gcc main.c stack.c -o laba24 -lm && ./laba24
// как надо читать этот код? Сначала идешь в main и там по строчке разбираешь. Смотришь в main какие он функции вызывает и бежишь к функции глядишь че она там творит
#include <stdio.h>
#include <string.h>
#include <math.h>
// в массиве ты обращаешься к элементам по индексу
// очередь ты обращаешься только к самому нижнему элементу. Ты его достаешь и следующий приходит. Самый первый пришел и самый первый ушел ты можешь пополнять но в конец очереди
// стек стопка тарелок.  Сначала достаешь достаешь верхнюю тарелку

#include <stdlib.h>
// описание структуры стека
// Обычно все члены структуры связаны друг с другом. Например, информация об имени и адресе, находящаяся в списке рассылки, обычно представляется в виде структуры.
typedef struct _Token // токен содержин либо букву либо число соответственно данным ниже
{
    char _varOp;
    double _num;
} Token;

typedef Token STACK_TYPE;

typedef struct _ItemStack
// элемент стека
{
    STACK_TYPE _data;
    // какие то данные которые записываются в каждый элемент стека. Как в дереве мы записываем в узел ноду, так и тут
    // STACK_TYPE это тип
    struct _ItemStack *_prev;
    // ссылка на предыдущий элемент prev с перевода предыдущий
} ItemStack;

typedef struct _Stack
// сам стек
{
    int _size;
    // size – это количество элементов
    struct _ItemStack *_top;
    // ссылка на верхний элемент стека
} Stack;

typedef struct _Node
{
    char _varOp;	// _var0p это символ
    double _num;	// _num это число видимо
    struct _Node *_left;
    struct _Node *_right;
} Node;

// описание функций работы со стеком
/*
теория по стэку
Изначально стек пуст. Вершина стека – указатель на первый элемент, никуда не указывает. В случае си она может быть равна NULL.
Push 3
Теперь стек состоит из одного элемента, числа 3. Вершина стека указывает на число 3.
Push 5
Стек состоит из двух элементов, 5 и 3, при этом вершина стека указывает на 5.
Push 7
Стек состоит из трёх элементов, вершина стека указывает на 7.
Pop
Вернёт значение 7, в стеке останется 5 и 3. Вершина будет указывать на следующий элемент – 5.
Pop
Вернёт 5, в стеке останется всего один элемент, 3, на который будет указывать вершина стека.
Pop
Вернёт 3, стек станет пуст.
*/
void stackCreate(Stack *s)
// s -  стэк. А Stack * это тип. Почему у нас стэк в качестве адреса? Так как самой переменной s у нас не в функции. Мы ее не объявляли. А чтобы менять ее не объйявляя по правилу ее нужно менять по адресу
{
    s->_size = 0;
    s->_top = NULL;
}

int stackEmpty(const Stack *s)
// проверяет пустой ли стак
// в верхнем элементе стэка есть указатель на нижний элемент первый. Если сломать указатель на верхний то стек поломается
{
    return s->_top == NULL;
}

int stackPush(Stack *s, const STACK_TYPE value)
// добавление элемента в стек
// в качестве аргументов функции у нас выступает адрес стека s и value - данные внутри каждого элемента стека
{
    ItemStack *item = (ItemStack *)malloc(sizeof(ItemStack));

    if (!item)
        // if (!a)можно переписать как if (a==0)
        return 0;
    // записываем значения value введенные с клавиатуры в элемент стека item. value имеет структурный тип включая _varOp и _num
    item->_data = value;
    // у стека есть ссылка на верхний элемент
    // item это элемент что только содлаи и поместили наверх
    // item указывает на бывший топовый элемент то есть на предпоследний
    // стек с указателями сверху вниз
    // что делается в следующих двух строках
    // мы добавили наверх стэка новый элемент item. Нужно сказать, что теперь это топовый элемент и поставить туда указатели
    // s->top это указатель на старый топовый элемент
    // item->_prev это указатель на предыдущий элемент. item это новый элемент который мы положили наверх
    // то есть мы item->_prev = s->_top; мы сказали что указатель на топовый элемент неактуален. И мы поменяем его с указателем на предтоповый элемент
    item->_prev = s->_top;
    // стек теперь указывает на новый топовый элемент item
    s->_top = item;
    // размер стека увеличиваетмя
    s->_size++;

    return 1;
}

int stackPop(Stack *s)
// удаление вер[него элемента
{
    ItemStack *item = NULL;

    if (!s->_size)
        return 0;

    item = s->_top; // присваиваем топовому элементу имя item
    // меняем ссылку с топового элемента ведь у нас удаление идет
    s->_top = s->_top->_prev;
    s->_size--;

    free(item);

    return 1;
}

STACK_TYPE stackTop(const Stack *s)
{
    // произвольные данные верхнего элемента. Мы можем поместить какие то данные внутри каждого элемента. Это как с нодами в деревьях где мы числа вставляли Но тут данные могут быть не только числа но любые. Даже массивы
    return s->_top->_data;
}

void stackDestroy(Stack *s)
{
    ItemStack *item = NULL;

    while (s->_top)
    {
        item = s->_top;
        s->_top = s->_top->_prev;

        free(item);
    }

    s->_size = 0;
    s->_top = NULL;
}



Node *treeNodeCreate(void){
    // Node * это возвращаемый тип данных
    Node *tmpNode = malloc(sizeof(Node));

    tmpNode->_varOp = '\0';
    // '\0' это нуль-символ Строковая константа — это последовательность символов, заключенная в кавычки, например: «Это строковая константа». В конце каждой строковой константы компилятор помещает ‘\0’ (нуль-символ), чтобы программе было возможно определить конец строки.
    tmpNode->_num = 0.0;
    tmpNode->_left = NULL;
    tmpNode->_right = NULL;

    return tmpNode;
}

Node *treeCopy(Node **node){ // root2 = treeCopy(&root); а root мы взяли из treeBuild(&root, &stPost);
    // что за node? Мы потом в case1 вызываем treecopy($root) то есть вместо node у нас буит root
    Node *tmpNode = NULL;

    if (*node == NULL)
        return NULL;

    tmpNode = treeNodeCreate();
    tmpNode->_varOp = (*node)->_varOp;
    tmpNode->_num = (*node)->_num;
    tmpNode->_left = treeCopy(&((*node)->_left));  //мы должны сначала рызыменовать node конструкцией *node тем самым получив адрес node (два раза разыменуешь и получишь само node. Ведь у нас **node). После первого разыменования мы сможем обратиться к left (не забываем что node-> тож самое что (*node). это значит что стрелочкой мы еще раз разыменуем и наконец дойдем до самого значения node) А после обращения мы опять берем адрес, только уже от (*node->left) чтобы поместить в функцию. Ведь аргумент данной функции требует двойной адресации. Или как это назвать. Там де Node **node
    tmpNode->_right = treeCopy(&((*node)->_right));
    return tmpNode; // а как это раюотает? когда дойдет до return
    /*
    tmpNode->_left = treeCopy(&((*node)->_left));
    как работает эта штука и с следующей строчкой
    лучше всего это понять когда сам увидишь через debug
    сначала мы перешли от корня к левой ноде. Потом мы смотрим есть ли у нее сосед слева. Если есть. То снова идем к левой ноде поддерева. Если нет. То идем к правой ноде поддерева. И то же самое. Сначала чекаем левую, у левой_1 еще раз левую_2 правую_2 потом правую_1. Потом. Когда закончим работать с изначальным левым поддеревом, мы перейдем от корня к правому поддереву и также будет все работать
    Вопрос. А что же в конце программы вернет return?
    Ответ. Это как то хитро работает. И в конце работы treeCope возвращается КОРЕНЬ дерева. Хз как это работает. Но вот
    Вопрос. Куда мы сохраняем дерево?
    Ответ. Никуда скорее всего. Мы оставляем указатели от каждой ноды к следующей ноде. И вот так все сохраняется. Чтобы как в массиве числа сохранялось дерево. Вроде такого нет
    опять же. Чтобы лучше понять, стоит самому програть этот цикл через debug
    */
}

int CheckLeftNode(Node **node){// проверяет пустой ли левый потомок
    if (*node == NULL)	// ВНИМАНИЕ
        return 0;

    if ((*node)->_left == NULL || (*node)->_right == NULL)
        return 0;

    return ((*node)->_left->_varOp == '\0' && (*node)->_left->_num == 0.0);
}

int isOp(const char ch){
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
}

int stackSize(const Stack *s)
{
    return s->_size;
}

void treeBuild(Node **node, Stack *st){// построение дерева ( http://algolist.manual.ru/syntax/revpn.php )
    Token token;

    if (stackEmpty(st)) // если стек st пустой
        return; // завершить работу функции treeBuild

    token = stackTop(st); // token это верхний элемент стека

    stackPop(st);// удаление верхнего элемента стека st

    (*node) = treeNodeCreate(); // создание одной ноды
    (*node)->_varOp = token._varOp; // запись в нолу сивола
    (*node)->_num = token._num; // запись в ноду числа

    if (isOp((*node)->_varOp)){ // если в _varOp у нас операция была, то мы создаем справа и слева ноды. Вдруг так букавки к в ( http://algolist.manual.ru/syntax/revpn.php ) или еще операции
        treeBuild(&(*node)->_right, st); // возвращаем эту же функцию. Но в лей будет следующий элемент в стэке, ведь предыдущий мы удалили
        treeBuild(&(*node)->_left, st); // получается node это двойной адрес? зачем
    } // мы вызывали treeBuild(&root, &stPost); значит в качестве node у нас будет &root
}

void treeDestroy(Node **node){
    if (*node == NULL)
        return;

    if ((*node)->_left != NULL)
        treeDestroy(&(*node)->_left);

    if ((*node)->_right != NULL)
        treeDestroy(&(*node)->_right);

    free(*node);

}

void PKL(Node **node, const int level){ // печать исходного дерева
    if (*node == NULL)
        return;

    if ((*node)->_right != NULL)
        PKL(&(*node)->_right, level + 1);

    if ((*node)->_varOp != '\0')
        printf("%*s%c\n", level * 4, "", (*node)->_varOp);
    else
        printf("%*s%f\n", level * 4, "", (*node)->_num);

    if ((*node)->_left != NULL)
        PKL(&(*node)->_left, level + 1);
}
// вопрос к LKP. Как она работает. А именно. Почему когда цикл LKP(&(*node)->_left); у нас заканчивается то якобы нода левая у нас удаляется. Хотя нигде она к нулю не приравнивается
// страшный цикл. Без дебага и рисунка сюда не лезть ни в коем случае. Сожрет нахуй
void LKP(Node **node){ // печать преобразованного выражения. Из уже готового дерева
    if (*node == NULL) // LKP(&root2); где root2 это корень преобразованного дерева
        return;

    if ((*node)->_left != NULL && !CheckLeftNode(node)){
        // if выше. Если левый потомок ненулевой(нахуя?) и в ноде НЕ "-"
        if ((*node)->_left->_left != NULL) // это по логике. Надо нарисовать дерево чтобы понять
            printf("(");
        /*для уравнения a+4*a
                  +
            +          *
          i   4     4     +
                        i   4
        Если левый подпотомой ненулевой. А это i то мы пишем скобочку. Если подпотомок ненулевой то потомок это точно операция. Операция между двумя числами. Значи там точно нужна скобочка в начале
        */


        LKP(&(*node)->_left); //  спускаемся в левый низ пока не дойдем до нуля
        /* LKP работает хитро. Он как бы рекурсивно вызывается. Как матрешка. Самая большая матрешка это самая последняя. То есть в данном случае это i самое левое. После того как с ней мы разобрались, для нее функция перестает работать и мы возвращаемся к поменьше матрешке. Это к +. Это очень хорошо видно в дебаге
        LKP(+)
            LKP(+)
                LKP(i)
        как только закончил работу LKP(i) мы возвращаемся к LKP(+) что на уровень выше. То есть к ноде с + на втором уровне. Вот так хитро
        */
        if ((*node)->_left->_left != NULL) // после того как мы спустились в самый левый низ то данный if пропускается потому что (*node)->_left == NULL. Мы пробегаемся по другим if, а после возвращаемся к LKP(+) уровнем выше и бежим к этому if что я сейчас комменчу
            printf(")");
    }

    if ((*node)->_varOp != '\0') // спустились в самый левый низ. Пишем буковку
        printf("%c", (*node)->_varOp);
    else // а если не буковка то пишем циферку. Смотря че тама
        printf("%f", (*node)->_num);

    if ((*node)->_right != NULL){
        if ((*node)->_right->_left != NULL)
            printf("(");

        LKP(&(*node)->_right);// ищем левый лист

        if ((*node)->_right->_left != NULL)
            printf(")");
    }

}
int isLetter(const char ch){
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

int isNumber(const char ch){
    return (ch >= '0' && ch <= '9');
}

int opPrior(const char op){
    if (op == '^')
        return 4;

    if (op == '*' || op == '/')
        return 3;

    if (op == '+' || op == '-')
        return 2;

    return 1;
}
int isOpHigh(const char op1, const char op2){
    if (op1 == '(' || op2 == '(' || op2 == ')')
        return 0;

    if (op1 == op2 && op2 == '^')
        return 0;

    return (opPrior(op1) >= opPrior(op2));
}

void postOrder(const char *str, Stack *st){
// postOrder(expr, &stPost);
    // где expr это выражение с клавиатуры а stPost это структура

    int i = 0, isBracket = 0;	// isBracket это скобка;  i данный читаемый элемент
    // Token tk это структура с числом и букавками
    Token tk; // tk это имя переменной структуры. По которой можно обращаться к структуре по точке
    Stack stOp; // у нас два стека. st и st0p. st это стек вывода уже. А st0p он собирает элементы и сравнивает

    stackCreate(&stOp);

    tk._varOp = '\0'; 	// var0p это символ
    tk._num = 0.0;

    while (str[i] != '\0'){	// пока строка не дошла до конца
        // что такое конструкция else if. if(key=2) else if(key = 3) else{}...  звучит так. Если ключ равно 2... если ключ равно 3... и во всех остальных случаях, то есть когда на 2 ни 3
        if (isLetter(str[i])){ // если условие выполнено
            // записываем в токен(var0p) значение: букву
            // функция isLetter: return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
            tk._varOp = str[i];
            stackPush(st, tk); 			// добавление элемента tk в стэк st
        }
        else if (isNumber(str[i])){
            // записываем в токен(num) значение: число
            tk._varOp = '\0';
            // str[i] - '0'преобразует символ в позиции i в числовую цифру. Подробнее тут https://stackoverflow.com/questions/36942227/what-is-the-purpose-of-using-stri-0-where-str-is-a-string
            tk._num = tk._num * 10.0 + str[i] - '0';

            if (!isNumber(str[i + 1])){ // !isNumber(str[i + 1] в данном случае означанет что функиця должна выдать нулик. Тогда сработает if.
                stackPush(st, tk);
                tk._num = 0.0;
            }
        }
        else if (isOp(str[i])){// Пока непонятно. для операций + - ... Кажись это пошла Дейкстра
            tk._varOp = str[i];

            if (str[i] == ')')
                isBracket = 1; // is Bracket переводится как скобочка
            /*
            else if (str[i] == '-' && (i == 0 || str[i - 1] == '(')){// бесполезный цикл
                tmpCh = tk._varOp;
                tk._varOp = '\0';
                tk._num = 0.0;
                stackPush(st, tk);
                tk._varOp = tmpCh;

            } */

            while (!stackEmpty(&stOp) && (isOpHigh(stackTop(&stOp)._varOp, str[i]) || isBracket)){// пока( стек не пустой && ( по приоритету элемент в стэке stOp больше элемента что считываем || b != 0) )
                // !stackEmpty(&stOp) в данном случае ! распространяется только на эту функцию. !stackEmpty(&stOp) озачаем, что пока эта функция не выполняется. Эта функция проверяет пустой ли стек. Получается с ! функция проверяет невыполнение этого условия
                // теперь про || isBracket. Почему мы вкинули просто переменную в цикл ни к чемц не приравняв? Если кидаешь просто переменную в цикл, например, if(b){...}, то на нее накладывается условие !=0. То есть конструкция if(b) равноправна if(b != 0)
                if (stackTop(&stOp)._varOp == '(') // бесполезный цикл потому что никто не ставил ( и сразу )
                    isBracket = 0;
                else
                    stackPush(st, stackTop(&stOp));// добавление в вывод элемента с приоритетом большим чем в элемента строчке

                stackPop(&stOp); // удаление верхнего элемента
            }

            if (str[i] != ')')  // вот это не совсем понял зачем
                stackPush(&stOp, tk);
        }

        i++;
    }

    while (!stackEmpty(&stOp)){ // если строчка закончилась но элементы в стеке st0p еще остались (данный вариант описан внизу в картинке в http://algolist.manual.ru/syntax/revpn.php) то мы добавляем этот элемент в выходную строку
        stackPush(st, stackTop(&stOp));
        stackPop(&stOp);
    }

    stackDestroy(&stOp);
}
Node *Zamena1(Node **node, int l, double k){
    if ((*node)!= NULL){
        if (l == 0) {
            (*node)->_num = (*node)->_num / sqrt(k);
        }
        if(((*node)->_left!=NULL) && ((*node)->_varOp !='^')) {
            (*node)->_left->_num =(*node)->_left->_num / sqrt(k);
        }
        if(((*node)->_right!=NULL) && ((*node)->_varOp !='^')) {
            (*node)->_right->_num = (*node)->_right->_num / sqrt(k);
        }


        if (((*node)->_left!=NULL)  && ((*node)->_right!=NULL) && ((*node)->_varOp =='*')) {
            (*node)->_left->_num = (*node)->_left->_num / sqrt(k); // так как у нас замена a = i + 4
        } else if ((*node)->_varOp =='x') {

            (*node)->_varOp ='*';

            Node *tmpNode = NULL;
            tmpNode = treeNodeCreate();// пустой узел дерева
            tmpNode->_num = 1.0 / k;
            (*node)->_left=tmpNode;

            Node *tmpNode1 = NULL;
            tmpNode1 = treeNodeCreate();
            tmpNode1->_varOp = 'x';
            (*node)->_right=tmpNode1;
        }
        else{ // в противном случае спускаемся вниз и ищем a
            Zamena1(&(*node)->_left, l, k);
            Zamena1(&(*node)->_right, l, k);
        }
    }
}


int main(void)
{
    int action;
    char expr[255];
    Node *root = NULL, *root2 = NULL;
    Stack stPost;
    while (1)
    {
        printf("Меню:\n");
        printf("1) Ввести выражение\n");
        printf("2) Печать исходного выражения\n");
        printf("3) Печать преобразованного выражения\n");
        printf("4) Печать исходного дерева\n");
        printf("5) Печать преобразованного дерева\n");
        printf("6) Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &action);

        switch (action)
        {
            case 1:
            {
                printf("Введите выражение: ");
                scanf("%s", expr);
                // если мы только начали работу программы. Вводим первое выражение. То следующие две функции закончатся сразу же т.к. root = root2 = NULL
                // две функции ниже предназначены если ты одно выражение преобразовал и решил преобразовать еще одно другое выражение не выходя из программы
                treeDestroy(&root);
                treeDestroy(&root2);
                // stackCreate находится в подпрограмме stack.c
                stackCreate(&stPost);
                //int l = stackSize(&stPost);
                postOrder(expr, &stPost);
                treeBuild(&root, &stPost); // node в качестве &root
                stackDestroy(&stPost);  // удаляем  пустой стек чтобы не занимал место. Пустой он потому что мы из него построили дерево
                root2 = treeCopy(&root);
                //Zamena1(&root2, l);
                break;
            }

            case 2:
            {
                printf("Исходное выражение: %s\n", expr);

                break;
            }

            case 3:
            {
                int l = stackSize(&stPost);
                float k;
                printf("Введите число k: ");
                scanf("%f", &k);
                Zamena1(&root2, l, k);
                LKP(&root2);

                printf("\n");

                break;
            }

            case 4:
            {
                if (root != NULL)
                {
                    printf("Дерево исходного выражения\n");
                    PKL(&root, 0);
                }
                else
                    printf("Дерево исходного выражения пусто\n");

                break;
            }

            case 5:
            {
                if (root2 != NULL)
                {
                    printf("Дерево преобразованного выражения\n");
                    PKL(&root2, 0);
                }
                else
                    printf("Дерево преобразованного выражения пусто\n");

                break;
            }

            case 6: break;

            default:
            {
                printf("Ошибка. Такого пункта меню не существует\n");

                break;
            }
        }

        if (action == 6)
            break;
    }

    treeDestroy(&root);
    treeDestroy(&root2);

    return 0;
}
