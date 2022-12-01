#include <stdio.h>
#include <math.h>

void Line() {
    int i;
    printf("|");
    for (i = 0; i < 137; i++) {
        printf("-");
    }
    printf("|\n");
}

int main(void)
{
    double eps;
    double lgf;
    double lg;
    double func;
    double sum;
    double step;
    double X;
    double a;
    double b;
    int n;
    int i;
    int iter;
    int part;

    a = -1.0;
    b = 1.0;
    iter = 0;
    X = a;

    eps = (7.0 / 3.0 - 4.0 / 3.0 - 1.0);
    printf("Машинное эпсилон: %.42f\n", eps);
    lg = log(2);

    printf("Введите число разбиений отрезка [-1, 1]: ");
    scanf("%d", &part);
    step = (b - a) / part;

    Line();
    printf("| Номер шага | Значение X: |     Значение функции по формуле Тейлора:     |  Значение функции по встроенной функции ЯП:  | Число итераций |\n");
    Line();

    for (i = 0; i <= part; i++) {
        n = 1;
        func = 1;
        sum = 0;
        while ((func > eps || func < -eps) && (n < 100)) {
            func = pow((-1), n - 1) * (pow(X, n) / (n * pow(2, n)));
            sum = sum + func;
            n = n + 1;
            iter = iter + 1;
        }
        sum = sum + lg;
        lgf = log(2 + X);
        printf("|     %2d\t |    %.2f\t   | %.42f | %.42f |       %2d       |\n", i, X, sum, lgf, iter);
        X = X + step;
        iter = 0;
    }
    Line();
    return 0;
}
