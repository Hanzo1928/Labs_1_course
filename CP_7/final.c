#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const size_t MIN_CAP = 64;

typedef struct{                                         // Структура векторов
    double *buf;                                        // Ссылка на выделяемую область памяти
    size_t size;
    size_t capacity;
} vector;

typedef struct {                                        // Структура матрицы
    int m;
    int n;
    vector k;                                           // Индекс ненулевого элемента
    vector v;                                           // Значение ненулевого элемента
} matrix;

bool v_init(vector *v) {                                // Функция объявления вектора при создании матрицы
    double *newbuf = malloc(MIN_CAP * sizeof(double));  // Выделение памяти
    if (newbuf != NULL) {                               // При успешном выделении памяти
        v->buf = newbuf;                                // Указатель на выделенную область памяти
        v->size = 0;
        v->capacity = MIN_CAP;
        return true;
    }
    return false;
}

void v_destroy(vector *v) {
    free(v->buf);
    v->buf = NULL;
    v->size = 0;
    v->capacity = 0;
}

double v_get(vector *v, size_t i) {
    return v->buf[i];
}

void v_set(vector *v, size_t i, double val) {           // Добавление введенного значения вектора на позицию i
    v->buf[i] = val;
}

size_t v_get_size(vector *v) {                          // Функция вычисления количества элементов в векторе
    return v->size;
}

bool v_set_size(vector *v, size_t new_size) {           // Функция выделения памяти для нового значения
    if (new_size > v->capacity) {                       // Если новый размер больше выделенного, то
        size_t new_cap = v->capacity * 3 / 2;           // увеличиваем выделенный объем памяти
        if (new_cap < new_size) {
            new_cap = new_size;
        }
        if (new_cap < MIN_CAP) {
            new_cap = MIN_CAP;
        }

        double *new_buf = realloc(v->buf, new_cap * sizeof(double));    // Изменение количества выделяемой памяти
        if (new_buf == NULL) {
            return false;
        }

        v->buf = new_buf;
        v->capacity = new_cap;
    }
    else if (new_size * 3 / 2 < v->capacity) {
        size_t new_cap = new_size * 3 / 2;
        if (new_cap < MIN_CAP) {
            new_cap = MIN_CAP;
        }

        v->buf = realloc(v->buf, new_cap * sizeof(double));
        v->capacity = new_cap;
    }

    for (size_t i = v->size; i < new_size; i++) {
        v_set(v, i, 0);
    }

    v->size = new_size;
    return true;
}

double v_pop_back(vector *v) {
    double res = v_get(v, v_get_size(v) - 1);
    v_set_size(v, v_get_size(v) - 1);
    return res;
}

bool v_push_back(vector *v, double val) {               // Функция запоминания информации о векторе
    if (v_set_size(v, v_get_size(v) + 1)) {
        v_set(v, v_get_size(v) - 1, val);            // Мы запоминаем значение в вектор на позиции
        return true;
    }
    return false;
}

void v_swap(vector *v, size_t i1, size_t i2) {
    double t = v_get(v, i1);
    v_set(v, i1, v_get(v, i2));
    v_set(v, i2, t);
}

void mat_init(matrix *m) {                              // Функция создания матрицы
    v_init(&m->k);
    v_init(&m->v);
}

void mat_destroy(matrix *m) {                           // Функция освобождения памяти для матрицы
    v_init(&m->k);
    v_init(&m->v);
    m->m = 0;
    m->n = 0;
}

void mat_read(matrix *mat, FILE *f) {                           // Функция чтения данных из файла в матрицу
    fscanf(f, "%d %d", &mat->m, &mat->n);                       // Чтение размерности матрицы
    for (int i = 0; i < mat->m; i++) {
        for (int j = 0; j < mat->n; j++) {
            int tmp;
            fscanf(f, "%d", &tmp);
            if (tmp != 0) {                                    // Если число не ноль, то
                v_push_back(&mat->k, i * mat->n + j);   // Вычисление и запоминание позиции, на которой расположен ненулевой элемент (считая с 0, а не с 1)
                v_push_back(&mat->v, (double)tmp);      // Запоминаем значение ненулевого элемента
            }
        }
    }
}

void mat_print_vec(matrix *mat) {                               // Функция печати векторов
    fprintf(stdout, "(Вектор индексации) LB:  ");
    for (int i = 0; i < v_get_size(&mat->k); i++) {
        fprintf(stdout, "%3d ", (int)v_get(&mat->k, i));
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "(Вектор значений) YE:    ");
    for (int i = 0; i < v_get_size(&mat->v); i++) {
        fprintf(stdout, "%3d ", (int)v_get(&mat->v, i));
    }
    fprintf(stdout, "\n");
}

void print_zeros (int *prev_i, int *prev_j, int border_i, int border_j, int n) {        // Функция печати нулей в матрице
    while (*prev_i != border_i || *prev_j != border_j) {
        int x = 0;
        fprintf(stdout, "%3d ", x);
        if (*prev_j == n - 1) {
            *prev_j = 0;
            *prev_i += 1;
            fprintf(stdout, "\n");
        }
        else{
            *prev_j += 1;
        }
    }
}

void mat_print(matrix *mat) {                               // Функция печати матрицы
    if (mat->n == 0 || mat->m == 0) {                       // Если размерность 0, то ничего
        return;
    }
    int prev_i = 0;
    int prev_j = 0;
    for (int t = 0; t < v_get_size(&mat->k); t++) {
        int ind = (int)v_get(&mat->k, t);
        int val = (int)v_get(&mat->v, t);
        int i = ind / mat->n;
        int j = ind % mat->n;
        print_zeros(&prev_i, &prev_j, i, j, mat->n);
        fprintf(stdout, "%3d ", val);
        prev_i = i;
        prev_j = j + 1;
        if (prev_j == mat->n) {
            fprintf(stdout, "\n");
            prev_i++;
            prev_j = 0;
        }
    }
    print_zeros(&prev_i, &prev_j, mat->m, 0, mat->n);
}

int v_binarysearch(vector *v, double val) {
    int l = 0;
    int r = v_get_size(v);
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (val < v_get(v, m)) {
            r = m;
        }
        else if (val > v_get(v, m)) {
            l = m;
        }
        else{
            return m;
        }
    }
    return (l + r) / 2;
}

int mat_get(matrix *mat, int i, int j) {
    int ind = v_binarysearch(&mat->k, i * mat->n + j);
    if (v_get(&mat->k, ind) == i * mat->n + j) {
        return v_get(&mat->v, ind);
    }
    return 0;
}

void mat_trans_diag(matrix *a, matrix *ans) {
    ans->m = a->m;
    ans->n = a->n;
    int b[a->n*a->n];
    for (int i = 0; i < a->n * a->n; i++) {
        b[i] = 0;
    }
    ans->m = a->m;
    ans->n = a->n;
    int j2 = 0, i2 = 0;
    for (int i = a->n - 1; i >= 0; i--) {
        for (int j = a->n - 1; j >= 0; j--) {
            int tmp = (int)mat_get(a, i, j);
            int ind = j2 * a->n + i2;
            j2++;
            b[ind] = tmp;
        }
        i2++;
        j2 = 0;
    }
    for (int i = 0; i < a->n * a->n; i++) {
        if (b[i] != 0) {
            v_push_back(&ans->k, i);
            v_push_back(&ans->v, (double)b[i]);
        }
    }
}

bool mat_check_skew_symmetry(matrix *mat) {
    for (int t = 0; t < v_get_size(&mat->k); t++) {
        int i = (int)v_get(&mat->k, t) / mat->n;
        int j = (int)v_get(&mat->k, t) % mat->n;
        if ((int)v_get(&mat->v, t) != -mat_get(mat, j, i)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: ./а.out <FILE_NAME>\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Не удалось открыть файл \"%s\"\n", argv[1]);
        return 2;
    }
    matrix a, ans;
    mat_init(&a);                                                    // Создаётся матрица
    mat_read(&a, f);                                                // Чтение данных из файла в матрицу
    fprintf(stdout, "\nИзначальная матрица:\n");
    mat_print(&a);
    fprintf(stdout, "\nПредставление матрицы:\n");
    mat_print_vec(&a);
    fprintf(stdout, "\n");
    fprintf(stdout, "═══════════════════════════════════════════════════════════\n");
    fprintf(stdout, "\n");
    if (a.n == a.m) {
        mat_trans_diag(&a, &ans);
        fprintf(stdout, "Матрица, транспонированная относительно побочной диагонали:\n");
        mat_print(&ans);
        fprintf(stdout, "\nПредставление матрицы:\n");
        mat_print_vec(&ans);
        if (mat_check_skew_symmetry(&ans)) {
            fprintf(stdout, "\n═ Матрица кососимметричная ═\n");
        } else {
            fprintf(stdout, "\n═ Матрица НЕ кососимметричная ═\n");
        }
    } else {
        fprintf(stdout, "═ Матрица не является квадратной, транспонировать нельзя ═\n");
    }
    mat_destroy(&a);
    mat_destroy(&ans);
    fclose(f);
}