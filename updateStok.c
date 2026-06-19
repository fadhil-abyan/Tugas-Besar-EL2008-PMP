#include <stdio.h>
#include <string.h>
#include "inventaris.h"

void updateStok(Node* head, char* id, int jumlah) {
    Node* current = head;

    while (current != NULL && strcmp(current->data.id, id) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Data tidak ditemukan\n");
        return;
    }

    if (current->data.stok + jumlah < 0) {
        printf("Stok tidak mencukupi\n");
        return;
    }

    current->data.stok += jumlah;

    if (current->data.stok == 0) {
        strcpy(current->data.status, "habis");
    } else if (strcmp(current->data.status, "habis") == 0) {
        strcpy(current->data.status, "tersedia");
    }
}
