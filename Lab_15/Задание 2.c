#include <stdio.h>

int main(void)
{
    int m;
    int i;
    long long max;
    long long min;
    int max_i;
    int min_i;
    int sym;

    max = -10000000;
    min = 10000000;
    sym = 0;

    scanf("%d", &m);
    int X [m];
    for (i = 0; i < m; i++) {
        scanf("%d", &X[i]);
        if (X[i] > max) {
            max = X[i];
            max_i = i;
        }
        if (X[i] < min) {
            min = X[i];
            min_i = i;
        }
    }
    if (max_i > min_i) {
        for (i = (min_i + 1); i < max_i; i++) {
            sym = sym + X[i];
        }
    }
    if (min_i > max_i) {
        for (i = (max_i + 1); i < min_i; i++) {
            sym = sym + X[i];
        }
    }
    printf("%d", sym);
}