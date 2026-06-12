#include <string.h>
#include "inventaris.h"

void tampilSemua(Node* head) {
    if (head == NULL) {
        printf("Data inventaris kosong. Tidak ada barang untuk ditampilkan.\n");
        return;
    }

    printf("===============================================\n");
    printf("     DAFTAR SELURUH INVENTARIS LABORATORIUM    \n");
    printf("===============================================\n");
    
    Node* current = head;
    int nomor = 1;

    while (current != NULL) {
        printf("Item #%d\n", nomor);
        printf("  ID Barang : %s\n", current->data.id);
        printf("  Nama      : %s\n", current->data.nama);
        printf("  Kategori  : %s\n", current->data.kategori);
        printf("  Stok      : %d\n", current->data.stok);
        printf("  Lokasi    : %s\n", current->data.lokasi);
        printf("  Status    : %s\n", current->data.status);
        printf("  Pemilik   : %s\n", current->data.pemilik);
        printf("  PIC       : %s\n", current->data.pic);
        printf("-----------------------------------------------\n");
        
        current = current->next;
        nomor++;
    }
}

void tampilRingkasan(Node* head) {
    if (head == NULL) {
        printf("Data inventaris kosong. Tidak ada ringkasan yang dapat dibuat.\n");
        return;
    }

    int totalJenisBarang = 0;
    int totalFisikBarang = 0;
    int jmlTersedia = 0;
    int jmlDipinjam = 0;
    int jmlRusak = 0;
    int jmlHabis = 0;

    Node* current = head;

    while (current != NULL) {
        totalJenisBarang++; 
        totalFisikBarang += current->data.stok; 

        if (strcmp(current->data.status, "tersedia") == 0) {
            jmlTersedia++;
        } else if (strcmp(current->data.status, "dipinjam") == 0) {
            jmlDipinjam++;
        } else if (strcmp(current->data.status, "rusak") == 0) {
            jmlRusak++;
        } else if (strcmp(current->data.status, "habis") == 0) {
            jmlHabis++;
        }

        current = current->next;
    }

    printf("===============================================\n");
    printf("             RINGKASAN INVENTARIS              \n");
    printf("===============================================\n");
    printf("Total Jenis/Item Barang : %d\n", totalJenisBarang);
    printf("Total Fisik Keseluruhan : %d\n", totalFisikBarang);
    printf("-----------------------------------------------\n");
    printf("Berdasarkan Status Ketersediaan (Jenis Barang):\n");
    printf("  - Tersedia : %d\n", jmlTersedia);
    printf("  - Dipinjam : %d\n", jmlDipinjam);
    printf("  - Rusak    : %d\n", jmlRusak);
    printf("  - Habis    : %d\n", jmlHabis);
    printf("===============================================\n");
}