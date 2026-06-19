#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "inventaris.h"

void cariData(Node* head, char* id) {
    Node* current = head;

    if (current == NULL) {
        printf_P(PSTR("Inventaris kosong. Tidak ada data yang dapat dicari!\n"));
        return;
    }

    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            printf_P(PSTR("ID: %s\n"), current->data.id);
            printf_P(PSTR("Nama: %s\n"), current->data.nama);
            printf_P(PSTR("Kategori: %s\n"), current->data.kategori);
            printf_P(PSTR("Stok: %d\n"), current->data.stok);
            printf_P(PSTR("Lokasi: %s\n"), current->data.lokasi);
            printf_P(PSTR("Status: %s\n"), current->data.status);
            printf_P(PSTR("Pemilik: %s\n"), current->data.pemilik);
            printf_P(PSTR("PIC: %s\n"), current->data.pic);
            return;
        }
        current = current->next;
    }
    printf_P(PSTR("Pencarian Gagal: ID tidak ditemukan di dalam sistem!\n"));
}