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
    int x;
    long long count_f;
    long long count;
    char sym;

    k = 1;
    count = 0;

    enum Value state = A;
    while (scanf("%c", &sym) != EOF) {
        switch (state) {
            case A:
                if (sym == ' ' || sym == '\n') {
                    count = 0;
                    k = 1;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym == '0' || sym == '1' || sym == '2' || sym == '+') {
                    state = P0;
                    k = 1;
                }
                if (sym == '3' || sym == '4') {
                    state = P1;
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != '3' && sym != '4' && sym != '-' && sym != '+' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (sym == '-' && state != Bad) {
                    state = N0;
                    k = -1;
                }
                if (state != Bad && sym != '-' && sym != '+' && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case P0:
                if (sym == ' ' || sym == '\n') {
                    count = 0;
                    k = 1;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym == '3' || sym == '4') {
                    state = P1;
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != '3' && sym != '4' && sym != ' ' && sym != '\n') {
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
                        while (count >= 1) {
                            x = count % 10;
                            x = x * powf(5, l);
                            count_f = count_f + x;
                            l = l + 1;
                            count = count / 10;
                        }
                        printf("%lld ", count_f * k);
                    }
                    k = 1;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != '3' && sym != '4' && sym != ' ' && sym != '\n') {
                    state = Bad;
                }
                if (state != Bad && sym != ' ' && sym != '\n') {
                    count = count * 10 + (sym - '0');
                }
                break;
            case N0:
                if (sym == ' ' || sym == '\n') {
                    count = 0;
                    k = 1;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym == '3' || sym == '4') {
                    state = N1;
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != '3' && sym != '4' && sym != ' ' && sym != '\n') {
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
                        while (count >= 1) {
                            x = count % 10;
                            x = x * powf(5, l);
                            count_f = count_f + x;
                            l = l + 1;
                            count = count / 10;
                        }
                        printf("%lld ", count_f * k);
                    }
                    k = 1;
                    state = A;
                    if (sym == '\n') {
                        printf("\n");
                    }
                }
                if (sym != '0' && sym != '1' && sym != '2' && sym != '3' && sym != '4' && sym != ' ' && sym != '\n') {
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
        while (count >= 1) {
            x = count % 10;
            x = x * powf(5, l);
            count_f = count_f + x;
            l = l + 1;
            count = count / 10;
        }
        printf("%lld\n", count_f * k);
    }
    return 0;
}
