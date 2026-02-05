#include <stdio.h>


/*
 * Afiseaza pentru fiecare elem din vect aux '1' si '0' daca apare sau nu in vect principal v[]

 * Ex:
    7
    1 2 5 6 9 10 14
    8
    8 14 9 14 16 15 4 2

    Va afisa:
    0 1 1 1 0 0 0 1
 */

int cautare(int v[], int x, int st, int dr) {
    if (st > dr) {
        return 0;
    }
    else {
        int m = (st + dr) / 2;
        if (v[m] == x) {
            return m;
        }
        if (v[m] < x) {
            return cautare(v,x, m+1, dr);
        }
        if (v[m] > x) {
            return cautare(v, x, st, m-1);
        }
        return 0;
    }
}

void citire(int v[], int *n) {
    scanf("%d", n);
    for (int i = 0; i < *n; i ++) {
        scanf("%d", &v[i]);
    }
}

int main(void) {
    int n, v[100];
    int m, aux[100];
    citire(v, &n);
    citire(aux,&m);

    for (int i = 0; i < m; i ++) {
        if (cautare(v, aux[i], 0, n-1)) {
            printf("1 ");
        }
        else {
            printf("0 ");
        }
    }
    return 0;
}