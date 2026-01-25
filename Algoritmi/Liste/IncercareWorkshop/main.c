#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct IDParticipant {
    struct IDParticipant *next;
    int id;
}IDParticipant;

typedef struct ZiWorkShop {
    struct ZiWorkShop *next;
    IDParticipant *ID;
    int zi;
}ZiWorkShop;

typedef struct CodWorkshop{
    char cod[50];
    struct CodWorkshop* next;
    ZiWorkShop *z;
} CodWorkshop;

void eliberare_cod(CodWorkshop *head);
void eliberare_zi(ZiWorkShop *z);
void eliberare_id(IDParticipant *i);

/*
 Avem nevoie de gaseste_zi si exista_id pentru a verifica ca valoarea acestora nu e deja adaugata
 */


ZiWorkShop* gaseste_zi(ZiWorkShop *z, int zi) {
    while (z != NULL) {
        if (z->zi == zi)
            return z;
        z = z->next;
    }
    return NULL;
}
int exista_id(IDParticipant *idp, int id) {
    while (idp != NULL) {
        if (idp->id == id)
            return 1;
        idp = idp->next;
    }
    return 0;
}


void adauga_id(ZiWorkShop *zi, int id) {
    if (!exista_id(zi->ID, id)) {
        IDParticipant *p = zi->ID;
        while (p->next != NULL)
            p = p->next;

        p->next = malloc(sizeof(IDParticipant));
        p->next->id = id;
        p->next->next = NULL;
    }
}

void adaugare(CodWorkshop **head, char cod[50], int zi, int id) {
    CodWorkshop *p = *head;
    CodWorkshop *last = NULL;
    ZiWorkShop *noua_zi = NULL;

    // căutăm codul
    while (p != NULL) {
        if (strcmp(p->cod, cod) == 0) { //daca codul exista, cautam ziua

            ZiWorkShop *z = gaseste_zi(p->z, zi);

            if (z != NULL) { //daca ziua exista, adaugam id
                adauga_id(z, id);
            } else {
                // ziua nu exista -> o cream
                noua_zi = malloc(sizeof(ZiWorkShop));
                noua_zi->zi = zi;
                noua_zi->next = NULL;

                noua_zi->ID = malloc(sizeof(IDParticipant));
                noua_zi->ID->id = id;
                noua_zi->ID->next = NULL;

                // o legam la final
                z = p->z;
                while (z->next != NULL)
                    z = z->next;
                z->next = noua_zi;
                z->next->ID = noua_zi->ID;
            }
            return;
        }
        last = p;
        p = p->next;
    }

    // daca nu exista cod-ul
    CodWorkshop *nou = malloc(sizeof(CodWorkshop));
    strcpy(nou->cod, cod); // cod
    nou->next = NULL;

    nou->z = malloc(sizeof(ZiWorkShop)); //zi
    nou->z->zi = zi;
    nou->z->next = NULL;

    nou->z->ID = malloc(sizeof(IDParticipant)); //id
    nou->z->ID->id = id;
    nou->z->ID->next = NULL;

    if (*head == NULL) //daca nu avem niciun cod, cel nou cread e primul
        *head = nou;
    else //daca avem coduri in lista, atunci cel nou creat va fi trecut la final
        last->next = nou;
}

void printID(IDParticipant *i) {
    while (i != NULL) {
        printf(" %d ", i->id);
        i = i->next;
    }
}

void printZi(ZiWorkShop *z) {
    while (z != NULL) {
        printf(" zi: %d si id: ", z->zi);
        printID(z->ID);
        z = z->next;
    }
}


void printCod(CodWorkshop *c) {
    int cnt = 0;
    while (c != NULL) {
        printf("%d: %s", cnt, c->cod);
        printZi(c->z);
        printf("\n");
        c = c->next;
        cnt++;
    }
}

void eliberare_id(IDParticipant *i) {
    while (i != NULL) {
        IDParticipant *aux = i;
        i = i -> next;
        free(aux);
    }
}

void eliberare_zi(ZiWorkShop *z) {
    while (z != NULL) {
        ZiWorkShop *aux = z;
        z = z->next;
        eliberare_id(aux->ID);
        free(aux);
    }
}

void eliberare_cod(CodWorkshop *head) {
    while (head != NULL) {
        CodWorkshop *p = head;
        head = head->next;
        eliberare_zi(p->z);
        free(p);
    }
}


int main(int argc, const char * argv[]) {
    if (argc != 2) {
        printf("Nr incorect de argumente\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    CodWorkshop *head = NULL;
    int nr_op, id, zi;
    char cod[50];
    char cod_final[50];
    fscanf(f, "%d", &nr_op);
    for (int i = 0; i < nr_op; i++) {
        int n = fscanf(f, "%49s %d %d", cod, &zi, &id);
        if (n != EOF) {
            printf("%s %d %d\n", cod, zi, id);
            strcpy(cod_final, cod+1);
            if (cod[0] == '+') {
                adaugare(&head, cod_final, zi, id);
            }
        }
    }
    printCod(head);
    eliberare_cod(head);
    return 0;
}