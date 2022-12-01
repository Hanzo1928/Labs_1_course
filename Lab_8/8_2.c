#include <stdio.h>
int main(void)
{
    int sum;
    int x;
    int k;

    scanf("%d", &k);

    sum = 0;
    for (int i = 1 ; i <= k ; i++) {
        scanf("%d", &x);

        sum = sum + x;
    }

    printf("%d\n", sum);

    return 0;
}