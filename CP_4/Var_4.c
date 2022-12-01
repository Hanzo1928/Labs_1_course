#include <stdio.h>
#include <math.h>

double eps()
{
    double eps;
    eps = 1;
    while (1 + eps > 1) {
        eps = eps / 2;
    }
    return eps;
}

double mod(double a, double b) {
    double Out;
    if (a > b) {
        Out = a - b;
    }
    if (b >= a) {
        Out = b - a;
    }
    return Out;
}

double F_Dix_a_1(double x) {
    double Out;
    Out = (3 * x) - 14 + exp(x) - exp(-x);
    return Out;
}

double F_Dix_ab_1(double a, double b) {
    double Out;
    double x;
    x = (a + b) / 2;
    Out = (3 * x) - 14 + exp(x) - exp(-x);
    return Out;
}

double Method_Dixotomii_1(double a, double b) {
    double z;
    double x;
    int n;
    n = 0;
    x = 0;
    z = mod(a, b);
    while(z > eps() && n < 100) {
        if ((F_Dix_a_1(a) * F_Dix_ab_1(a, b)) > 0) {
            a = (a + b) / 2;
            b = b;
        }
        if ((F_Dix_a_1(b) * F_Dix_ab_1(a, b)) > 0) {
            a = a;
            b = (a + b) / 2;
        }
        z = mod(a, b);
        n = n + 1;
        x = (a + b) / 2;
    }
    return x;
}

double F_Dix_a_2 (double a) {
    double Out;
    Out = sqrt(1 - a) - tan(a);
    return Out;
}

double F_Dix_ab_2 (double a, double b) {
    double Out;
    double x;
    x = (a + b) / 2;
    Out = sqrt(1 - x) - tan(x);
    return Out;
}

double Method_Dixotomii_2(double a, double b) {
    int n;
    double z;
    double x;
    n = 0;
    x = 0;
    z = mod(a, b);
    while (z > eps() && n < 100) {
        if ((F_Dix_a_2(a) * F_Dix_ab_2(a, b)) > 0) {
            a = (a + b) / 2;
            b = b;
        }
        if ((F_Dix_a_2(b) * F_Dix_ab_2(a, b)) > 0) {
            a = a;
            b = (a + b) / 2;
        }
        z = mod(a, b);
        n = n + 1;
        x = (a + b) / 2;
    }
    return x;
}

double Method_Iteracii_1(double a, double b) {
    double x_old;
    double x;
    double z;
    int n;
    n = 0;
    x_old = (a + b) / 2;
    z = -((3 * exp(x_old) + 1) / ((14 * exp(x_old)) - (3 * x_old * exp(x_old) + 1)));
    if (z < 0) {
        z = -1 * z;
    }
    if (z < 1) {
        x = log(14 - 3 * x_old + exp(-x_old));
        z = mod(x, x_old);
        while (z > eps() && n < 100) {
            x_old = x;
            x = log(14 - 3 * x_old + exp(-x_old));
            z = mod(x, x_old);
            n = n + 1;
        }
        return x;
    }
}

double Method_Iteracii_2(double a, double b) {
    double x_old;
    double x;
    double z;
    int n;
    n = 0;
    x_old = (a + b) / 2;
    z = -(1 / (2 * sqrt(1 - x_old) * (2 - x_old)));
    if (z < 0) {
        z = -1 * z;
    }
    if (z < 1) {
        x = atan(sqrt(1 - x_old));
        z = mod(x, x_old);
        while (z > eps() && n < 100) {
            x_old = x;
            x = atan(sqrt(1 - x_old));
            z = mod(x, x_old);
            n = n + 1;
        }
        return x;
    }
}

double F_x_1(double x_old) {
    double F_x;
    F_x = 3 * x_old - 14 + exp(x_old) - exp(-x_old);
    return F_x;
}

double F_diff_1_x_1(double x_old) {
    double F_diff_x;
    F_diff_x = (3 * exp(x_old) + exp(2 * x_old) + 1) / exp(x_old);
    return F_diff_x;
}

double F_diff_2_x_1(double x_old) {
    double F_x;
    F_x = (exp(2 * x_old) - 1) / exp(x_old);
    return F_x;
}

double Method_Newton_1(double a, double b) {
    double x;
    double x_old;
    double z;
    int n;
    n = 0;
    x_old = (a + b) / 2;
    if (mod(F_x_1(x_old), F_diff_2_x_1(x_old)) < pow(F_diff_1_x_1(x_old), 2)) {
        x = x_old - (F_x_1(x_old) / F_diff_1_x_1(x_old));
        z = mod(x, x_old);
        while (z > eps() && n < 100) {
            x_old = x;
            x = x_old - (F_x_1(x_old) / F_diff_1_x_1(x_old));
            z = mod(x, x_old);
            n = n + 1;
        }
        return x;
    }
}

double F_x_2(double x_old) {
    double F_x;
    F_x = sqrt(1 - x_old) - tan(x_old);
    return F_x;
}

double F_diff_1_x_2(double x_old) {
    double F_x;
    F_x = -(1.0 / pow(cos(x_old), 2)) -(1.0 / 2 * sqrt(1 - x_old));
    return F_x;
}

double F_diff_2_x_2(double x_old) {
    double F_x;
    F_x = -(2.0 * sin(x_old) / pow(cos(x_old), 3)) -(1.0 / 4 * sqrt(1 - x_old) * (1 - x_old));
    return F_x;
}

double Method_Newton_2(double a, double b) {
    double x;
    double x_old;
    double z;
    int n;
    n = 0;
    x_old = (a + b) / 2;
    if (mod(F_x_2(x_old), F_diff_2_x_2(x_old)) < pow(F_diff_1_x_2(x_old),2)) {
        x = x_old - (F_x_2(x_old) / F_diff_1_x_2(x_old));
        z = mod(x, x_old);
        while (z > eps() && n < 100) {
            x_old = x;
            x = x_old - (F_x_2(x_old) / F_diff_1_x_2(x_old));
            z = mod(x, x_old);
            n = n + 1;
        }
        return x;
    }
}

void Line() {
    int i;
    printf("|");
    for (i = 0; i < 152; i++) {
        printf("-");
    }
    printf("|\n");
}

int main(void)
{
    double a_1;
    double b_1;
    double a_2;
    double b_2;
    a_1 = 1;
    b_1 = 3;
    a_2 = 0;
    b_2 = 1;
    printf("Машинное эпсилон: %.20f\n\n", eps());
    Line();
    printf("%s %s %s %s\n", "| Function  :          3x - 14 + exp(x) - exp(-x)          | ", "", "   Отрезок, содрежащий корень: [1, 3]      |", "    Приближенное значение корня: 2.0692      |");
    Line();
    printf("|   Метод   : %44s %14s| %42s %15s| %41s %15s|\n", "Метод Дихотомии:", "", "Метод Итераций:", "", "Метод Ньютона:", "");
    Line();
    printf("%9s %.42f | %.42f | %.42f |\n", "| Значение X:", Method_Dixotomii_1(a_1, b_1), Method_Iteracii_1(a_1, b_1), Method_Newton_1(a_1, b_1));
    printf("%9s %.42f | %.42f | %.42f |\n", "| Проверка F:", F_x_1(Method_Dixotomii_1(a_1, b_1)), F_x_1(Method_Iteracii_1(a_1, b_1)), F_x_1(Method_Newton_1(a_1, b_1)));
    Line();
    printf("\n\n\n");
    Line();
    printf("%s %s %s %s\n", "| Function  :             sqrt(1 - x) - tan(x)             | ", "", "   Отрезок, содрежащий корень: [0, 1]      |", "    Приближенное значение корня: 0.5768      |");
    Line();
    printf("|   Метод   : %44s %14s| %42s %15s| %41s %15s|\n", "Метод Дихотомии:", "", "Метод Итераций:", "", "Метод Ньютона:", "");
    Line();
    printf("%9s %.42f | %.42f | %.42f |\n", "| Значение X:", Method_Dixotomii_2(a_2, b_2), Method_Iteracii_2(a_2, b_2), Method_Newton_2(a_2, b_2));
    printf("%9s %.42f | %.42f | %.42f |\n", "| Проверка F:", F_x_2(Method_Dixotomii_2(a_2, b_2)), F_x_2(Method_Iteracii_2(a_2, b_2)), F_x_2(Method_Newton_2(a_2, b_2)));
    Line();
    return 0;
}
