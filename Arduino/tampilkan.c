#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "inventaris.h"

void tampilSemua(Node* head) {
    if (head == NULL) {
        printf_P(PSTR("Data inventaris kosong. Tidak ada barang untuk ditampilkan.\n"));
        return;
    }

    printf_P(PSTR("===============================================\n"));
    printf_P(PSTR("     DAFTAR SELURUH INVENTARIS LABORATORIUM    \n"));
    printf_P(PSTR("===============================================\n"));
    
    Node* current = head;
    int nomor = 1;

    while (current != NULL) {
        printf_P(PSTR("Item #%d\n"), nomor);
        printf_P(PSTR("  ID Barang : %s\n"), current->data.id);
        printf_P(PSTR("  Nama      : %s\n"), current->data.nama);
        printf_P(PSTR("  Kategori  : %s\n"), current->data.kategori);
        printf_P(PSTR("  Stok      : %d\n"), current->data.stok);
        printf_P(PSTR("  Lokasi    : %s\n"), current->data.lokasi);
        printf_P(PSTR("  Status    : %s\n"), current->data.status);
        printf_P(PSTR("  Pemilik   : %s\n"), current->data.pemilik);
        printf_P(PSTR("  PIC       : %s\n"), current->data.pic);
        printf_P(PSTR("-----------------------------------------------\n"));
        
        current = current->next;
        nomor++;
    }
}

void tampilRingkasan(Node* head) {
    if (head == NULL) {
        printf_P(PSTR("Data inventaris kosong. Tidak ada ringkasan yang dapat dibuat.\n"));
        return;
    }

    int totalJenisBarang = 0;
    int totalFisikBarang = 0;
    int jmlTersedia = 0, jmlDipinjam = 0, jmlRusak = 0, jmlHabis = 0;

    Node* current = head;

    while (current != NULL) {
        totalJenisBarang++; 
        totalFisikBarang += current->data.stok; 

        if (strcmp(current->data.status, "tersedia") == 0) jmlTersedia++;
        else if (strcmp(current->data.status, "dipinjam") == 0) jmlDipinjam++;
        else if (strcmp(current->data.status, "rusak") == 0) jmlRusak++;
        else if (strcmp(current->data.status, "habis") == 0) jmlHabis++;

        current = current->next;
    }

    printf_P(PSTR("===============================================\n"));
    printf_P(PSTR("             RINGKASAN INVENTARIS              \n"));
    printf_P(PSTR("===============================================\n"));
    printf_P(PSTR("Total Jenis/Item Barang : %d\n"), totalJenisBarang);
    printf_P(PSTR("Total Fisik Keseluruhan : %d\n"), totalFisikBarang);
    printf_P(PSTR("-----------------------------------------------\n"));
    printf_P(PSTR("Berdasarkan Status Ketersediaan (Jenis Barang):\n"));
    printf_P(PSTR("  - Tersedia : %d\n"), jmlTersedia);
    printf_P(PSTR("  - Dipinjam : %d\n"), jmlDipinjam);
    printf_P(PSTR("  - Rusak    : %d\n"), jmlRusak);
    printf_P(PSTR("  - Habis    : %d\n"), jmlHabis);
    printf_P(PSTR("===============================================\n"));
}