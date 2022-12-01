#include <stdio.h>
#include <math.h>

int main(void)
{
    long long N;
    int ost;
    long long New;
    int i;
    int sign;

    New = 0;
    i = 1;
    sign = 1;

    while (scanf("%lld", &N) != EOF) {
        if (N < 0) {
            N = -1 * N;
            sign = -1;
        }
        while (N >= 1) {
            ost = N % 10;
            if (ost % 2 != 0) {
                if (New == 0) {
                    New = ost;
                } else {
                    New = (ost * powl(10, i)) + New;
                    i = i + 1;
                }
            }
            N = N / 10;
        }
        printf("%lld\n", New * sign);
        New = 0;
        i = 1;
        sign = 1;
    }
    return 0;
}
