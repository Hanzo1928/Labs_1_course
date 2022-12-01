#include <stdio.h>

int main(void)
{
    int a;
    int b;
    int a_new;
    int b_new;
    int count_old;
    int count_new;
    int i;

    scanf("%d", &a);
    scanf("%d", &b);

    for (i = 1 ; i < 10 ; i++) {
        a_new = (b + a) * i;
        b_new = b % a + i;
        count_new = (count_old + (a_new * b_new)) % i;
        count_old = count_new;
        a = a_new;
        b = b_new;
    }
    printf("%d %d %d\n", a, b, count_new);
    return 0;
}
