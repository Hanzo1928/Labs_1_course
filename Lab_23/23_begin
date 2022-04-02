#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;                    // значение вершины дерева
    struct node *left;           // Указатель на левое поддерево
    struct node *right;          // Указатель на правое поддерево
    struct node *parent;         // Указатель на родителя
} tree;

tree * tree_create (int value) {               // Функция создания дерева
    tree *node = malloc (sizeof (tree));       // Выделение памяти для структуры *node
    node->data = value;                        // Указатель на поле структуры, запоминающий значение вершины
    node->right = NULL;                        // Указатель на поле структуры, обозначающее правое поддерево
    node->left = NULL;                         // Указатель на поле структуры, обозначающее левое поддерево
    node->parent == NULL;                      // Указатель на поле структуры, обозначающее родительскую вершину
    return node;
}

tree *tree_add(tree *node, int val) {         // Функция добавления вершины
    tree *new = node;                         
    tree *parent = NULL;                      // Указатель на родителя в node приравнивается нулю
    tree *tmp = malloc(sizeof(tree));         // Выделение памяти для вершины
    tmp->data = val;                          // Передача в поле data структуры node значения вершины
    while (new != NULL) {
        parent = new;                         
        if (val < new->data) {                // Распределение вершины в поддеревьях
            new = new->left;
        } else {
            new = new->right;
        }
    }
    tmp->parent = parent;                     // Новая вершина получает указатель на родителя
    tmp->left = NULL;
    tmp->right = NULL;
    if (val < parent->data) {                 
        parent->left = tmp;                   
    } else {                                  
        parent->right = tmp;
    }
    return node;
}

tree* search(tree *node, int val)             // Функция проверки существования вершины по ее значению
{
    if (node == NULL) {                       // Если структура пустая, то вывод об отсутствии вершины
        printf("Не существует вершины со значением %d\n", val);
        return NULL;
    }
    if (node->data == val) {                  // Если значение вершины совпадает с введенным, то выводим значение вершины
        printf("Существует вершины со значением %d\n", val);
        return node;
    }
    if (val < node->data){                    // Если значение введенное значение меньше значения рассмотренной вершины, то рассматриваем левое поддерево
        return search(node->left, val);
    }
    else return search(node->right, val);// Если значение введенное значение меньше значения рассмотренной вершины, то рассматриваем правое поддерево
}

void draw_tree(tree *node) {                // Вывод дерева
    if (node->left != NULL){
        draw_tree(node->left);
    }
    printf("%d\n", node->data);
    if (node->right) {
        draw_tree(node->right);
    }
}

// -------------------------------------------------------------------------------------------------------------

int main()
{
    int m;
    int j;
    scanf("%d", &m);     // Указание числа вводимых вершин
    int X[m];
    int val;
    for (j = 0; j < m; j++) {
        scanf("%d", &X[j]);
    }
    struct node *T = NULL;
    T = tree_create(m);
    draw_tree(T);
    for (j = 0; j < m; j++) {
        T = tree_add(T, X[j]);
    }
    printf("\n");
    draw_tree(T);
    printf("Проверка существования вершины: ");
    scanf("%d", &val);
    search(T, val);
    return 0;
}
