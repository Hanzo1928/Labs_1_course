#include <stdio.h>
#include <math.h>

enum Value {
    A,
    N0,
    P0,
    N1,
    P1,
    Bad
};

int main(void)
{
    int k;
    int l;
    long long x;
    int e;
    int zero;

    long long count_f;
    long long count;
    long long count_out;
    char sym;

    k = 1;
    zero = 0;
    count = 0;

    enum Value state = A;
    while (scanf("%c", &sym) != EOF) {
        switch (state) {
            case A:
                if (sym == ' ' || sym == '\n') {
                    if (count == 0 && zero != 0) {
                        if (k == -1) {
                            printf("%c", '-');
                        }
                        if (k == 2) {
                            printf("%c", '+');
                        }
                        for (e = 0; e < zero; e++) {
                            printf("%d", 0);
                        }
                        printf(" ");
                    }
                    count = 0;
                    k = 1;
                    state = A;
                    zero = 0;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym == '0') {
                    zero = zero + 1;
                }
                if (sym == '1' || sym == '2') {
                    state = P1;
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != '-' && sym != '+' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (sym == '-' && state != Bad) {
                    state = N0;
                    k = -1;
                }
                if (sym == '+' && state != Bad) {
                    k = 2;
                }
                if (state != Bad && sym != '-' && sym != '+' && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case P0:
                if (sym == ' ' || sym == '\n') {
                    if (count == 0 && zero > 0) {
                        if (k == -1) {
                            printf("%c", '-');
                        }
                        if (k == 2) {
                            printf("%c", '+');
                        }
                        if (count == 0) {
                            for (e = 0; e < zero; e++) {
                                printf("%d", 0);
                            }
                            printf(" ");
                        }
                    }
                    count = 0;
                    k = 1;
                    zero = 0;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym == '1' || sym == '2') {
                    state = P1;
                    k = 1;
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (state != Bad && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case P1:
                if (sym == ' ' || sym == '\n') {
                    if ((state != Bad) || (count == 0 && sym == '0')) {
                        l = 0;
                        count_f = 0;
                        count_out = count;
                        while (count >= 1) {
                            x = count % 10;
                            x = x * powf(3, l);
                            count_f = count_f + x;
                            l = l + 1;
                            count = count / 10;
                        }
                        if (count_f % 3 == 0) {
                            if (k == -1) {
                                printf("%c", '-');
                            }
                            if (k == 2) {
                                printf("%c", '+');
                            }
                            if (count_out != 0) {
                                for (e = 0; e < zero; e++) {
                                    printf("%d", 0);
                                }
                            }
                            if (count_out == 0) {
                                for (e = 1; e < zero; e++) {
                                    printf("%d", 0);
                                }
                            }
                            printf("%lld ", count_out);
                        }
                    }
                    k = 1;
                    zero = 0;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (state != Bad && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case N0:
                if (sym == ' ' || sym == '\n') {
                    if (count == 0 && zero > 0) {
                        if (k == -1) {
                            printf("%c", '-');
                        }
                        if (k == 2) {
                            printf("%c", '+');
                        }
                        if (count == 0) {
                            for (e = 0; e < zero; e++) {
                                printf("%d", 0);
                            }
                            printf(" ");
                        }
                    }
                    count = 0;
                    k = 1;
                    zero = 0;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym == '0') {
                    zero = zero + 1;
                }
                if (sym == '1' || sym == '2') {
                    state = N1;
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (state != Bad && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case N1:
                if (sym == ' ' || sym == '\n') {
                    if ((state != Bad) || (count == 0 && sym == '0')) {
                        l = 0;
                        count_f = 0;
                        count_out = count;
                        while (count >= 1) {
                            x = count % 10;
                            x = x * powf(3, l);
                            count_f = count_f + x;
                            l = l + 1;
                            count = count / 10;
                        }
                        if (count_f % 3 == 0) {
                            if (k == -1) {
                                printf("%c", '-');
                            }
                            if (k == 2) {
                                printf("%c", '+');
                            }
                            if (count_out != 0) {
                                for (e = 0; e < zero; e++) {
                                    printf("%d", 0);
                                }
                            }
                            if (count_out == 0) {
                                for (e = 1; e < zero; e++) {
                                    printf("%d", 0);
                                }
                            }
                            printf("%lld ", count_out);
                        }
                    }
                    k = 1;
                    zero = 0;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (state != Bad && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case Bad:
                if (sym == ' ' || sym == '\n') {
                    state = A;
                    count = 0;
                    k = 1;
                    zero = 0;
                }
                if (sym == '\n') {
                    printf("\n");
                }
            default:
                break;
        }
    }
    if (((state == P1 || state == N1) && sym != ' ' && sym != '\n') || (state != Bad && count == 0 && sym == '0'))  {
        l = 0;
        count_f = 0;
        count_out = count;
        while (count >= 1) {
            x = count % 10;
            x = x * powf(3, l);
            count_f = count_f + x;
            l = l + 1;
            count = count / 10;
        }
        if (count_f % 3 == 0) {
            if (k == -1) {
                printf("%c", '-');
            }
            if (k == 2) {
                printf("%c", '+');
            }
            if (count_out != 0) {
                for (e = 0; e < zero; e++) {
                    printf("%d", 0);
                }
            }
            if (count_out == 0) {
                for (e = 1; e < zero; e++) {
                    printf("%d", 0);
                }
            }
            printf("%lld ", count_out);
        }
    }
    printf("\n");
    return 0;
}
