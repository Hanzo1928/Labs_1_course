#include <stdio.h>
int main(void)
{
    int sum;
    int k;
    int x;

    scanf("%d", &k);

    sum = 0;
    for (int i = 1 ; i <= k ; i++) {
        scanf("%d", &x);

        if (x >= 10) {
            sum = sum + x;
        }
    }

    printf("%d\n", sum);

    return 0;
}