#include <stdio.h>

int main(void)
{
    int t;
    int n;
    int m;
    long long max;
    int i;
    int j;
    int k;
    int l;
    int f;
    int until;

    max = -45001;
    f = 0;
    until = -1;

    scanf("%d", &t);
    scanf("%d", &n);

    if (t != EOF) {
        for (k = 0; k < t; k++) {
            scanf("%d", &m);
            long long X[m][m];
            for (i = 0; i < m; i++) {
                for (j = 0; j < m; j++) {
                    scanf("%lld", &X[i][j]);
                    if (X[i][j] > max) {
                        max = X[i][j];
                    }
                }
            }
            for (i = 0; i < m; i++) {
                for (j = 0; j < m; j++) {
                    if (X[i][j] == max) {
                        if (until == -1) {
                            until = i;
                        }
                        if (i != 0) {
                            for (l = 0; l < m; l++) {
                                if (f == 1) {
                                    X[until][l] = X[until][l] + X[i][l];
                                }
                            }
                            f = 1;
                        } else {
                            f = 1;
                        }
                        break;
                    }
                }
            }
            max = -45001;
            until = -1;
            f = 0;
            for (i = 0; i < m; i++) {
                for (j = 0; j < m; j++) {
                    printf("%lld ", X[i][j]);
                }
                printf("\n");
            }
        }
    }
    return 0;
}
