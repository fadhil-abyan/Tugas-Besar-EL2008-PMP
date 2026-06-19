#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "inventaris.h"

static int statusValid(char* status) {
    return strcmp(status, "tersedia") == 0 ||
           strcmp(status, "dipinjam") == 0 ||
           strcmp(status, "rusak") == 0 ||
           strcmp(status, "habis") == 0;
}

void updateStatus(Node* head, char* id, char* statusBaru) {
    Node* current = head;

    while (current != NULL && strcmp(current->data.id, id) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf_P(PSTR("Data tidak ditemukan\n"));
        return;
    }

    if (!statusValid(statusBaru)) {
        printf_P(PSTR("Status tidak valid!\n"));
        return;
    }

    strcpy(current->data.status, statusBaru);

    if (strcmp(statusBaru, "habis") == 0) {
        current->data.stok = 0;
    }
}