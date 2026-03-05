#include <stdio.h>
#include <stdlib.h>


void citire(int n, int *arr, FILE *f) {
    for (int i = 0; i < n; i ++) {
        fscanf(f, "%d", &arr[i]);
    }
}

void afisare_tablou(int n, int *arr, FILE *out) {
    for (int i = 0; i < n; i ++) {
        fprintf(out, "%d ", arr[i]);
    }
    fprintf(out, "\n");
}


int mutare_bomboane(int n, int arr[], int aux[], FILE *out) {
    int medie = 0;
    for (int i = 0; i < n; i ++) {
        medie += arr[i];
    }
    if (medie % n != 0) {
        return -1;
    }
    medie = medie / n;
    int cnt = 0, k = 0;
    int poz_min=0, poz_max=0;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
              if (arr[j] > arr[poz_max]) {
                  poz_max = j;
              }
              if (arr[j] < arr[poz_min]) {
                  poz_min = j;
              }
        }
        int dif = medie - arr[poz_min];
        if (dif == 0) {
            return cnt;
        }
        cnt++;

        aux[k++] = poz_max + 1;
        aux[k++] = poz_min + 1;
        aux[k++] = dif;
        arr[poz_min] += dif;
        arr[poz_max] -= dif;
    }
    return cnt;
}

int main(int argc, char ** argv) {
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
    int n;
    fscanf(f, "%d", &n);
    int arr[n];
    int aux[n * 3]; //tinem minte cutie_max cutie_min nr_bombaone mutate
    citire(n, arr, f);

    int cnt = mutare_bomboane(n, arr, aux, out);
    afisare_tablou(n, arr, out);
    for (int i = 0; i < cnt*3; i ++) {
        fprintf(out, "%d ", aux[i]);
        if ((i + 1) % 3 == 0) {
            fprintf(out, "\n");
        }
    }
    fclose(f);
    fclose(out);
    return 0;
}