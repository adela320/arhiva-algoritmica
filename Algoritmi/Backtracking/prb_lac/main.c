#include <stdio.h>
#include <stdlib.h>

const int di[] = {1, -1, 0, 0};
const int dj[] = {0, 0, 1, -1};

void eliberare(int **a, int m) {
    for (int i = 0; i < m; i ++) {
        free(a[i]);
    }
    free(a);
}

//tip 1 -> insula; tip2 -> peninsula

int valid(int **a, int n, int m, int i, int j) {
    if (i < 0 || i >= m || j < 0 || j >= n) {
        return 0;
    }

    if (a[i][j] != 1) {
        return 0;
    }

    return 1;
}

void verif_peninsula(int i, int j, int m, int n, int aux[]) {
    if (i == 0 || j == 0 || i == m - 1 || j == n - 1) { //daca e peninsula atinge marginile
        aux[1] = 2;
    }
}

void Bk(int **a, int n, int m, int i, int j, int aux[]) {

    if (!valid(a, n, m, i, j)) {
        return;
    }

    a[i][j] = 2; //marcam celulele vizitate

    verif_peninsula(i, j, m, n, aux); //daca e peninsula, aux[1] = 2; daca e insula, ramane pe 1;

    aux[0] = aux[0] + 1; //aux[0] contorizeaza nr de 1

    for (int k = 0; k < 4; k ++) {
        Bk(a, n, m, i + di[k], j + dj[k],  aux);
    }

    a[i][j] = 1; //revenim

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
    if (a == NULL) {
        printf("Eroare la malloc\n");
        exit(1);
    }
    for (int i = 0; i < m; i++) {
        a[i] = malloc(n * sizeof(int));
        if (a[i] == NULL) {
            printf("Eroare la malloc\n");
            exit(1);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j ++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }

    int aux[2];
    int maxi = -1; //aria maxima a unei insule
    int maxp = -1; //aria maxima a unei peninsule


    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            if (a[i][j] == 1) {
                aux[0] = 0; //cnt
                aux[1] = 1; //tipul (initial insula)

                Bk(a, n, m, i, j, aux);

                if (aux[0] > 0)  //daca am gasit valori de 1
                {
                   if (aux[1] == 1) {  //daca e insula -> maxi
                       if (aux[0] > maxi) {
                           maxi = aux[0];
                       }
                   }
                   else {
                        if (aux[0] > maxp) { //daca e penisula -> maxp
                            maxp = aux[0];
                        }
                    }
                }
            }
        }
    }
    fprintf(out, "%d %d", maxi, maxp);
    eliberare(a, m);
    fclose(f);
    fclose(out);
    return 0;
}