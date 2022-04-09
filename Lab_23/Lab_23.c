#include <stdio.h>
#include <stdlib.h>

typedef struct                                                  // Описание структуры дерева
{
    int data;                                                   // Целочисленное значение вершины дерева
    struct Tree *left;                                          // Ссылка на левое поддерево вершины
    struct Tree *right;                                         // Ссылка на правое поддерево вершины
    struct Tree* parent;                                        // Ссылка на родителя вершины
} Tree;                                                         // Имя объявленной структуры

Tree *root_create(int value)                                    // Функция создания дерева, которое вызывается в том случае, если Tree = NULL
{
    Tree *tree = (Tree*)malloc(sizeof(Tree));                   // Выделение памяти
    tree->data = value;                                         // В поле структуры data записывается значение вершины
    tree->left = NULL;                                          // Поскольку это функция создания дерева, то указатели на левое, правое поддерево,
    tree->right = NULL;                                         // а также на родителя равны NULL
    tree->parent = NULL;
    return tree;
}

Tree *tree_add_element(Tree *root, int value)                   // Функция добавления вершины в дерево
{
    if (root == NULL) {                                         // Если дерево пусто, то необходимо его создать
        printf("Done!\n");
        return root_create(value);                              // Мы передаем считанное с клавиатуры значение в качестве аргумента для функции
    }                                                           // создания дерева

    Tree *NewTree = (Tree*)malloc(sizeof(Tree));                // Выделение памяти для новой вершины
    NewTree->data = value;                                      // Запоминаем значение вершины
    Tree *tree1 = root;                                         // Указатель на первоначальное дерево
    Tree *tree2 = NULL;                                         // Указатель на дерево 2

    while (tree1 != NULL) {                                     // Пока дерево не пусто мы будем распределять введенную вершину по левому/правому дереву
        tree2 = tree1;                                          // Tree2 присваивается Tree1. Затем Tree2 выступит в роли родителя
        if (value < tree1->data) {                              // Если считанное значение меньше значения вершины, то указатель переходит на левое
            tree1 = tree1->left;                                // поддерево. Рано или поздно поддерево будет пусто и вершина будет записана
        }
        else if (value > tree1->data) {                         // Если считанное значение больше значения вершины, то указатель переходит на правое
            tree1 = tree1->right;                               // поддерево. Рано или поздно поддерево будет пусто и вершина будет записана
        }
        else {
            printf("This value is already exist in tree! Use other values!\n");     // Если введенное значение совпало со значением вершины, то ничего
            return root;
        }
    }
    NewTree->parent = tree2;                                    // Т.к. указатель в tree1 перешел на одно из поддеревьев, в качестве родителя нужно
    NewTree->left = NULL;                                       // использовать tree2, т.к. указатель на него не меняется
    NewTree->right = NULL;
    if (value < tree2->data) {                                  // Если значение вершины меньше значения родителя, то
        tree2->left = NewTree;                                  // в качестве левого поддерева родителя записывается новая вершина
    } else {
        tree2->right = NewTree;
    }
    printf("Done!\n");
    return root;
}

void tree_print(Tree *root, int n)                              // Функция вывода дерева
{
    if (root != NULL) {                                         // Если дерево не пустое, то
        tree_print(root->right, n + 1);                 // Функция рекурсивно будет открывать правое поддерево
        for (int i = 0; i < n; i++) printf("\t");               // в зависимости от глубины вершины, мы будем увеличивать отступы
        printf("%d\n", root->data);                             // печатаем значение вершины
        tree_print(root->left, n + 1);                  // Функция рекурсивно будет открывать левое поддерево
    }
}

Tree *search_in_tree(Tree *root, int value)                     // Функция поиска указателя вершины по ее значению
{
    if (root == NULL) {                                         // Проверка, что дерево не пустое
        return NULL;
    }
    if (root->data == value) {                                  // Если введенное значение совпадает со значением вершины, то
        return root;                                            // вернуть указатель на вершину
    }
    if (value > root->data) {                                   // Если введенное число больше значения вершины, то
        return search_in_tree(root->right,value);          // Рассматриваем правое поддерево
    } else {
        return search_in_tree(root->left, value);          // иначе левое поддерево
    }
}

Tree *minimum(Tree *t)                                          // Функция поиска минимальной вершины дерева
{
    if (t->left == NULL) {                                      // Если левое поддерево вершины равно NULL
        return t;                                               // Возвращаем указатель на саму вершину
    }
    return minimum(t->left);
}

Tree *maximum(Tree *t)                                          // Функция поиска максимальной вершины дерева
{
    if (t->right == NULL) {
        return t;
    }
    return maximum(t->right);
}

Tree *delete_element(Tree *root, int value)                     // Функция удаления вершины
{
    Tree* tree1 = NULL, * tree2 = NULL, *tree3 = root, *tree4 = NULL;

    if (root == NULL) {                                         // Проверка, что дерево не пустое
        printf("Delete error! Your tree isn't exist!\n");
        return root;
    }
    tree1 = search_in_tree(tree3, value);                  // Указатель на введенную с клавиатуры вершину
    if (tree1 == NULL) {                                        // Если указатель пуст, то
        printf("Your element already isn't exist!\n");          // такой вершины не существует
        return root;
    }
    // Первый случай, когда вершина == лист
    if (tree1->left == NULL && tree1->right == NULL) {          // Если у вершины отсутствуют поддеревья, то
        if (tree1->parent == NULL) {                            // Если сама удаляемая вершина является корнем, то
            free(tree1);                                        // Освобождаем память
            tree1 = NULL;                                       // Обнуляем указатель
            printf("Successful deletion\n");
            return NULL;
        }
        tree2 = tree1->parent;                                  // Передаем указатель на родителя удаляемой вершины
        if (tree2->left == tree1) {                             // Если удаляемая вершина - левый потомок, то обнуляем левого потомка
            tree2->left = NULL;                                 // родителя удаляемой вершины
        }
        else {                                                  // Если удаляемая вершина - правый потомок, то обнуляем правого потомка
            tree2->right = NULL;                                // родителя удаляемой вершины
        }
        free(tree1);                                            // Освобождаем память
    }
        // Второй случай - существует одно из поддеревьев
    else if (tree1->left != NULL && tree1->right == NULL) {     // Если у удаляемой вершины существует левый потомок, то
        if (tree1->parent == NULL) {                            // Если сама удаляемая вершина является корнем, то
            tree4 = tree1->left;                                // Запоминаем указатель на левого потомка
            tree4->parent = NULL;                               // Обнуляем указатель на родителя левого потомка удаляемой вершины
            free(tree1);                                        // Освобождаем память
            printf("Successful deletion\n");
            return tree4;
        }
        tree2 = tree1->parent;                                  // Передаем указатель на родителя удаляемой вершины
        if (tree2->left == tree1) {                             // Если левое поддерево родителя удаляемой вершины равно удаляемой вершине
            tree2->left = tree1->left;                          // то левым поддеревом родителя становится левое поддерево удаленной вершины
        }
        else {
            tree2->right = tree1->left;                         // Иначе правым поддеревом родителя становится левое поддерево удаленной вершины
        }
        free(tree1);
    }
    else if (tree1->left == NULL && tree1->right != NULL) {     // Если у удаляемой вершины существует правый потомок, то
        if (tree1->parent == NULL) {                            // Если сама удаляемая вершина является корнем, то
            tree4 = tree1->right;                               // Запоминаем указатель на правого потомка
            tree4->parent = NULL;                               // Обнуляем указатель на родителя левого потомка удаляемой вершины
            free(tree1);                                        // Освобождаем память
            printf("Successful deletion\n");
            return tree4;
        }
        tree2 = tree1->parent;                                  // Передаем указатель на родителя удаляемой вершины
        if (tree2->left == tree1) {                             // Если левое поддерево родителя удаляемой вершины равно удаляемой вершине
            tree2->left = tree1->right;                         // то левым поддеревом родителя становится правое поддерево удаленной вершины
        }
        else {
            tree2->right = tree1->right;                        // Иначе правым поддеревом родителя становится правое поддерево удаленной вершины
        }
        free(tree1);
    }
        // Третий случай - существуют оба поддерева
    else if (tree1->left != NULL && tree1->right != NULL) {     // Если у удаляемой вершины есть оба поддерева, то
        tree2 = minimum(tree1->right);                        // Запоминаем указатель на минимальный элемент правого поддерева удаляемой вершины
        tree1->data = tree2->data;                              // Значение удаляемой вершины равно значению минимального элемента правого поддерева
        tree4 = tree2->parent;                                  // Запоминаем указатель на родителя минимального элемента правого поддерева
        if (tree4->left == tree2) {                             // Если левое поддерево родителя минимального элемента правого поддерева равно мин, то
            free(tree2);                                        // Освобождаем память для мин. элемента
            tree4->left = NULL;                                 // Обнуляем указатель на левого потомка родителя минимального элемента
        }
        if (tree4->right == tree2) {
            free(tree2);
            tree4->right = NULL;
        }
    }
    printf("Successful deletion\n");
    return root;
}

int count_leaf(Tree *root)                                      // Функция подсчета листьев и их вывода
{
    int count = 0;                                              // Число листьев равно 0
    if (root != NULL) {                                         // Пока дерево не пустое, мы будем рассматривать его правое и левое поддерево
        if (root->left == NULL && root->right == NULL) {        // Если правое и левое поддерево 0, то это лист
            printf("%d\t", root->data);                         // Выводим значение листа
            return 1;                                           // возвращаем 1
        }
        if (root->left != NULL && root->right == NULL) {        // Если левое поддерево не пустое, то мы к числу листьев прибавляем результат
            count += count_leaf(root->left);               // работы функции для левого поддерева вершины. Ведь если поддерево - лист, то
        }                                                       // return 1, т.е. к числу листьев мы прибавляем по 1
        if (root->left == NULL && root->right != NULL) {
            count += count_leaf(root->right);
        }
        if (root->left != NULL && root->right != NULL) {
            count += count_leaf(root->left);
            count += count_leaf(root->right);
        }
    }
    return count;                                               // Возвращаем количество листьев
}

void print_menu() {                                             // Функция вывода меню
    printf("\nSelect the desired action by writing the appropriate number:\n");
    printf("1) Add an item to the tree\n");
    printf("2) Print the tree\n");
    printf("3) Remove an item from the tree\n");
    printf("4) Check at the number of leaves of the tree\n");
    printf("5) Search for the minimum tree element\n");
    printf("6) Search for the maximum tree element\n");
    printf("Enter 0 for exit\n");
}

int main(void)                                                  // Главная функция
{
    Tree *t = NULL;                                             // Изначально дерево пустое
    int value;                                                  // Переменная, в которую мы записываем значение считанной вершины
    int out;                                                    // Переменная, в которую записывается количество листьев (для красивого вывода)
    char c;                                                     // Переменная, которая считывает с клавиатуры команды меню
    printf("Welcome to the program for processing binary search trees!\n");
    print_menu();
    while ((c = getchar()) != EOF) {                            // Чтение символа из потока ввода
        value = 0;
        if (c == '\n') continue;
        switch (c) {
            case '1':
                printf("\nEnter the value you want to add to the tree: ");
                scanf("%d", &value);
                t = tree_add_element(t, value);
                break;
            case '2':
                tree_print(t, 1);
                break;
            case '3':
                printf("\nEnter the value you want to delete from the tree: ");
                scanf("%d", &value);
                t = delete_element(t, value);
                break;
            case '4':
                printf("Value leafs: ");
                out = count_leaf(t);
                printf("\n");
                printf("Count leaf: %d\n", out);
                break;
            case '5':
                printf("\nminimum element from your tree is %d\n", minimum(t)->data);
                break;
            case '6':
                printf("\nmaximum element from your tree is %d\n", maximum(t)->data);
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
}