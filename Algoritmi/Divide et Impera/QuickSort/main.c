#include <stdio.h>


/*
   Eficienta Quicksort:  O(nlog(n))

   Pentru sortare descrescatoare, schimbi  while (arr[i] > pivot) si while (arr[j] < pivot)

   Daca se cere o sortare dupa mai multe campuri (ex: in caz de egalitate note, sa se sorteze dupa ... )
   la partile cu while(arr[poz] < pivot) tinem cont de:
   (condiție_principală) || (egalitate_pe_prima && condiție_secundară)

Ex: while (arr[i].medie < pivot.medie || (arr[i].medie == pivot.medie && strcmp(arr[i].nume, pivot.nume) < 0))
    De preferat ar fi sa se construiasca o functie separata care sa furnizez 1 sau 0 in functie de rezultatul
    expresiei

 */

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void QuickSort(int arr[], int st, int dr) {
    int i = st;
    int j = dr;

    int pivot = arr[(st + dr)/2]; //alegem elem din mijloc ca pivot

    while (i <= j) {
        while (arr[i] < pivot) { //cautam un elem care ar trebui sa fie in dreapta pivotului
            i++;
        }

        while (arr[j] > pivot) { //cautam un elem care ar trebui sa fie in stanga pivotului
            j--;
        }

        if (i <= j) { // interschimbam cele doua elem daca indicii nu s-au depasit
            swap(&arr[i], &arr[j]);
            i++; //trecem pe urm pozitii cu indicii
            j--;
        }
    }

    if (st < j) { //daca au mai ramas elem in stanga pivotului, le sortam
        QuickSort(arr, st, j);
    }

    if (i < dr) { //daca au mai ramas elem in dreapta pivotului, le sortam
        QuickSort(arr, i, dr);
    }

}


void afisare(int *v, int n) {
    for (int i = 0; i < n; i ++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int v[] = {4, 6 ,12, 3, 8, 0, -2};
    int n = sizeof(v) / sizeof(v[0]);
    afisare(v, n);
    QuickSort(v, 0, n - 1);
    afisare(v, n);
    return 0;
}