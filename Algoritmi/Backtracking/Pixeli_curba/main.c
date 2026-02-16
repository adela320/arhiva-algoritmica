#include <stdio.h>
#include <stdlib.h>

const int di[] = {1, -1, 0, 0};
const int dj[] = {0, 0, 1, -1};

void eliberare(int **a, int **b, int m) {
    for (int i = 0; i < m; i ++) {
        free(a[i]);
        free(b[i]);
    }
    free(a);
    free(b);
}


int valid(int **a, int **b, int m, int n, int i, int j) {
    if (i < 0 || i >= m || j < 0 || j >= n) {
        return 0;
    }

    if (a[i][j] != 1 || b[i][j] != 0) {
        return 0;
    }

    return 1;
}

void verif_margine(int i, int j, int m, int n, int *margine) {
    if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
        *margine = 1;
    }
}

void Bk(int **a, int **b, int m, int n, int i, int j, int *cnt, int *margine) {

    if (!valid(a, b, m, n, i, j)) {
        return;
    }

    b[i][j] = 1; //marcam celulele vizitate

    verif_margine(i, j, m, n, margine); //daca e margine, aux[1] = 1;

    (*cnt)++;

    for (int k = 0; k < 4; k ++) {
        Bk(a, b, m, n, i + di[k], j + dj[k],  cnt, margine);
    }

  //  b[i][j] = 0; //revenim

}

void afisare(int **a, int m, int n) {
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Nr incorect de argumente");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Fisier intrare");
        exit(1);
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("Fisier iesire");
        exit(1);
    }
    int n, m;
    fscanf(f, "%d %d", &m, &n);
    int **a = malloc(m * sizeof(int *));
    int **b = calloc(m, sizeof(int *));
    if (a == NULL || b == NULL) {
        fprintf(stderr,"Eroare alocare memorie:");
        exit(1);
    }
    for (int i = 0; i < m; i++) {
        a[i] = malloc(n * sizeof(int));
        b[i] = calloc(n, sizeof(int)); // si aici trebuie verificare pentru malloc/calloc
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j ++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }

    int min_curba= 100000; //aria maxima a unei curbe inchise
    int cnt_curbe = 0;

    int is, js; //coordonatele celui mai din stanga pixel sus al curbei minime
    is = js = -1;
    for (int i = 0; i < m; i ++) { //mereu incep parcurgerea din stanga sus
        for (int j = 0; j < n; j ++) {
            if (a[i][j] == 1) {
                int cnt = 0;
                int margine = 0;

                Bk(a, b, m, n, i, j, &cnt, &margine);

                if (cnt > 3 && margine == 0)  //curba inchisa valida
                {
                    cnt_curbe++;
                    if (cnt < min_curba) {
                        min_curba = cnt;
                        is = i;
                        js = j;
                    }
                }
            }
        }
    }
    fprintf(out, "Curba minima: %d\nNr de curbe valide: %d\nCoordonate (is, js): (%d, %d)", min_curba, cnt_curbe, is, js);
    eliberare(a, b, m);
    fclose(f);
    fclose(out);
    return 0;
}