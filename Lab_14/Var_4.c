#include <stdio.h>

int main(void)
{
    int t;
    int n;
    int m;
    int k;
    int imp;
    int i;
    int j;
    int count;

    scanf("%d", &t);
    scanf("%d", &n);
    for (k = 0; k < t; k++) {
        count = 2;
        scanf("%d", &m);
        long long X[m][m];
        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++) {
                scanf("%lld", &X[i][j]);
            }
        }
        imp = m * 2;
        while (count <= imp) {
            if (count >= m + 1) {
                i = m;
                j = count - i;
            } else {
                i = count - 1;
                j = count - i;
            }
            if (i == m && j == m) {
                printf("%lld ", X[i - 1][j - 1]);
            } else {
                while (j < count && j <= m) {
                    printf("%lld ", X[i - 1][j - 1]);
                    i = i - 1;
                    j = j + 1;
                }
            }
            count = count + 1;
        }
        printf("\n");
    }
    return 0;
}
