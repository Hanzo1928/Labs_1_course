#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

const size_t MIN_CAP = 64;

typedef struct{
    double *buf;
    size_t size;
    size_t capacity;
} vector;

typedef struct {
    int m;
    int n;
    vector k;
    vector v;
} matrix;


bool v_init(vector *v) {
    double *newbuf = malloc(MIN_CAP * sizeof(double));
    if (newbuf != NULL) {
        v->buf = newbuf;
        v->size = 0;
        v->capacity = MIN_CAP;
        return true;
    }
    return false;
}

double v_get(vector *v, size_t i) {
    return v->buf[i];
}

void v_set(vector *v, size_t i, double val) {
    v->buf[i] = val;
}

size_t v_get_size(vector *v) {
    return v->size;
}

bool v_set_size(vector *v, size_t new_size) {
    if (new_size > v->capacity) {
        size_t new_cap = v->capacity * 3 / 2;
        if (new_cap < new_size) {
            new_cap = new_size;
        }
        if (new_cap < MIN_CAP) {
            new_cap = MIN_CAP;
        }

        double *new_buf = realloc(v->buf, new_cap * sizeof(double));
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

bool v_push_back(vector *v, double val) {
    if (v_set_size(v, v_get_size(v) + 1)) {
        v_set(v, v_get_size(v) - 1, val);
        return true;
    }
    return false;
}

void mat_init(matrix *m) {
    v_init(&m->k);
    v_init(&m->v);
}

void mat_destroy(matrix *m) {
    v_init(&m->k);
    v_init(&m->v);
    m->m = 0;
    m->n = 0;
}

void mat_read(matrix *mat, FILE *f) {
    fscanf(f, "%d%d", &mat->m, &mat->n);
    for (int i = 0; i < mat->m; i++) {
        for (int j = 0; j < mat->n; j++) {
            int tmp;
            fscanf(f, "%d", &tmp);
            if (tmp != 0) {
                v_push_back(&mat->k, i * mat->n + j);
                v_push_back(&mat->v, (double)tmp);
            }
        }
    }
}

void mat_print_vec(matrix *mat) {
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

void print_zeros (int *prev_i, int *prev_j, int border_i, int border_j, int n) {
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

void mat_print(matrix *mat) {
    if (mat->n == 0 || mat->m == 0) {
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
    mat_init(&a);
    mat_init(&ans);
    mat_read(&a, f);
    fprintf(stdout, "\nИзначальная матрица:\n");
    mat_print(&a);
    fprintf(stdout, "\nПредставление матрицы:\n");
    mat_print_vec(&a);
    mat_destroy(&a);
    mat_destroy(&ans);
    fclose(f);
}
