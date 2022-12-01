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
    Out = 0.25 * pow(x,3) + x - 1.2502;
    return Out;
}

double F_Dix_ab_1(double a, double b) {
    double Out;
    double x;
    x = (a + b) / 2;
    Out = 0.25 * pow(x,3) + x - 1.2502;
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
    Out = a + sqrt(a) + pow(a, 1.0 / 3) - 2.5;
    return Out;
}

double F_Dix_ab_2 (double a, double b) {
    double Out;
    double x;
    x = (a + b) / 2;
    Out = x + sqrt(x) + pow(x, 1.0 / 3) - 2.5;
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
    z = (-0.75 * pow(x_old, 2));
    if (z < 0) {
        z = -1 * z;
    }
    if (z < 1) {
        x = 1.2502 - (0.25 * pow(x_old, 3));
        z = mod(x, x_old);
        while (z > eps() && n < 100) {
            x_old = x;
            x = 1.2502 - (0.25 * pow(x_old, 3));
            z = mod(x, x_old);
            n = n + 1;
        }
        return x;
    }
    return 0;
}

double Method_Iteracii_2(double a, double b) {
    double x_old;
    double x;
    double z;
    int n;
    n = 0;
    x_old = (a + b) / 2;
    z = -(1.0 / 2 * sqrt(x_old)) - (1.0 / 3 * pow(x_old * x_old, 1.0 / 3));
    if (z < 0) {
        z = -1 * z;
    }
    if (z < 1) {
        x = 2.5 - sqrt(x_old) - pow(x_old, 1.0 / 3);
        z = mod(x, x_old);
        while (z > eps() && n < 1000) {
            x_old = x;
            x = 2.5 - sqrt(x_old) - pow(x_old, 1.0 / 3);
            z = mod(x, x_old);
            n = n + 1;
        }
        return x;
    }
    return 0;
}

double F_x_1(double x_old) {
    double F_x;
    F_x = 0.25 * pow(x_old,3) + x_old - 1.2502; // исходная формула
    return F_x;
}

double F_diff_1_x_1(double x_old) {
    double F_diff_x;
    F_diff_x = 0.75 * pow(x_old, 2) + 1; // первая производная
    return F_diff_x;
}

double F_diff_2_x_1(double x_old) {
    double F_x;
    F_x = 1.5 * x_old; // вторая производная
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
    return 0;
}

double F_x_2(double x_old) {
    double F_x;
    F_x = x_old + sqrt(x_old) + pow(x_old, 1.0 / 3) - 2.5;
    return F_x;
}

double F_diff_1_x_2(double x_old) {
    double F_x;
    F_x = 1 + (1.0 / 2 * sqrt(x_old)) + (1.0 / 3 * pow(x_old * x_old, 1.0 / 3));
    return F_x;
}

double F_diff_2_x_2(double x_old) {
    double F_x;
    F_x = - (1.0 / 4 * x_old * sqrt(x_old)) - (2.0 / 9 * x_old * pow(x_old * x_old, 1.0 / 3));
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
    return 0;
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
    a_1 = 0.0;
    b_1 = 2.0;
    a_2 = 0.4;
    b_2 = 1.0;
    printf("Машинное эпсилон: %.20f\n\n", eps());
    Line();
    printf("%s %s %s %s\n", "| Function  :          0.25 pow(x, 3) + x - 1.2502         | ", "", "   Отрезок, содрежащий корень: [0, 2]      |", "    Приближенное значение корня: 1.0001      |");
    Line();
    printf("|   Метод   : %44s %14s| %42s %15s| %41s %15s|\n", "Метод Дихотомии:", "", "Метод Итераций:", "", "Метод Ньютона:", "");
    Line();
    printf("%9s %.42f | %.42f | %.42f |\n", "| Значение X:", Method_Dixotomii_1(a_1, b_1), Method_Iteracii_1(a_1, b_1), Method_Newton_1(a_1, b_1));
    printf("%9s %.42f | %.42f | %.42f |\n", "| Проверка F:", F_x_1(Method_Dixotomii_1(a_1, b_1)), F_x_1(Method_Iteracii_1(a_1, b_1)), F_x_1(Method_Newton_1(a_1, b_1)));
    Line();
    printf("\n\n\n");
    Line();
    printf("%s %s %s %s\n", "| Function  :      x + sqrt(x) + pow(x, 1.0 / 3) - 2.5     | ", "", "  Отрезок, содрежащий корень: [0.4, 1]     |", "    Приближенное значение корня: 0.7376      |");
    Line();
    printf("|   Метод   : %44s %14s| %42s %15s| %41s %15s|\n", "Метод Дихотомии:", "", "Метод Итераций:", "", "Метод Ньютона:", "");
    Line();
    printf("%9s %.42f | %.42f | %.42f |\n", "| Значение X:", Method_Dixotomii_2(a_2, b_2), Method_Iteracii_2(a_2, b_2), Method_Newton_2(a_2, b_2));
    printf("%9s %.42f | %.42f | %.42f |\n", "| Проверка F:", F_x_2(Method_Dixotomii_2(a_2, b_2)), F_x_2(Method_Iteracii_2(a_2, b_2)), F_x_2(Method_Newton_2(a_2, b_2)));
    Line();
    return 0;
}