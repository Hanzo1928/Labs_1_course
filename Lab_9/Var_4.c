#include <stdio.h>
#include <math.h>

int abs(int N)
{
    if (N >= 0) {
        return N;
    } else {
        return (N * (-1));
    }
}

int divf(double M, double x)
{
    double N;
    N = M / x;
    if (x >= 0) {
        return floor(N);
    } else {
        return ceil(N);
    }
}

int mod(int N, int x)
{
    return (N - divf(N, x) * x);
}

int min(int I_J_old, int I_L_old)
{
    if (I_J_old < I_L_old) {
        return I_J_old;
    } else {
        return I_L_old;
    }
}

int max(int I_J_old, int I_L_old, int J_L_old)
{
    if ((I_J_old >= I_L_old) && (I_J_old >= J_L_old)) {
        return I_J_old;
    } if ((I_L_old >= I_J_old) && (I_L_old >= J_L_old)) {
        return I_L_old;
    } else {
        return J_L_old;
    }
}

int sign(int J_old)
{
    if (J_old > 0) {
        return 1;
    } if (J_old < 0) {
        return -1;
    } else {
        return 0;
    }
}

int main(void)
{
    int I_old;
    int J_old;
    int L_old;
    int I_new;
    int J_new;
    int L_new;
    
    scanf("%d", &I_new);
    scanf("%d", &J_new);
    scanf("%d", &L_new);
    
    if ((((10 - I_new) * (10 - I_new) + (10 - J_new) * (10 - J_new)) <= 100) && (((10 - I_new) * (10 - I_new) + (10 - J_new) * (10 - J_new)) > 25)) {
        printf("Yes\n%d %d %d %d\n", I_new, J_new, L_new, 0);
    } else {
        for (int k = 1 ; k < 51 ; k++) {
            I_old = I_new;
            J_old = J_new;
            L_old = L_new;
            I_new = mod((min(I_old + J_old, I_old + L_old) * (k)), 30);
            J_new = J_old + mod(L_old * sign(J_old), 20) + mod((k - 1) * sign(I_old), 10);
            L_new = mod(max(I_old * J_old, I_old * L_old, J_old * L_old), 30);
            if ((((10 - I_new) * (10 - I_new) + (10 - J_new) * (10 - J_new)) <= 100) && (((10 - I_new) * (10 - I_new) + (10 - J_new) * (10 - J_new)) > 25)) {
                printf("Yes\n%d %d %d %d\n", I_new, J_new, L_new, k);
                break;
            }
            if (k >= 50) {
                printf("No\n%d %d %d %d\n", I_new, J_new, L_new, k);
            }
        }
    }
   
    return 0;
}
