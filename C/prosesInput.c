#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

static void bacaBaris(char *buf, int ukuran) {
    if (fgets(buf, ukuran, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

static void bacaItemBaru(Item *item, int *validFlag) {
    char buffer[64];
    *validFlag = 1;

    printf("ID Barang   : ");
    bacaBaris(item->id, sizeof(item->id));
    if (strlen(item->id) == 0) {
        printf("Input Anda tidak valid: ID barang tidak boleh kosong!\n");
        *validFlag = 0; return;
    }

    printf("Nama        : ");
    bacaBaris(item->nama, sizeof(item->nama));

    printf("Kategori    : ");
    bacaBaris(item->kategori, sizeof(item->kategori));

    printf("Stok        : ");
    bacaBaris(buffer, sizeof(buffer));
    if (strlen(buffer) == 0) {
        printf("Input Anda tidak valid: Stok tidak boleh kosong!\n");
        *validFlag = 0; return;
    }
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            printf("Input Anda tidak valid: Stok harus berupa angka bilangan bulat positif.\n");
            *validFlag = 0; return;
        }
    }
    item->stok = atoi(buffer);

    printf("Lokasi      : ");
    bacaBaris(item->lokasi, sizeof(item->lokasi));

    printf("Status (tersedia/dipinjam/rusak/habis): ");
    bacaBaris(item->status, sizeof(item->status));
    if (strcmp(item->status, "tersedia") != 0 && 
        strcmp(item->status, "dipinjam") != 0 && 
        strcmp(item->status, "rusak") != 0 && 
        strcmp(item->status, "habis") != 0) {
        printf("Input Anda tidak valid: Status harus persis (tersedia, dipinjam, rusak, atau habis).\n");
        *validFlag = 0; return;
    }

    printf("Pemilik     : ");
    bacaBaris(item->pemilik, sizeof(item->pemilik));

    printf("PIC         : ");
    bacaBaris(item->pic, sizeof(item->pic));
}

static void cetakMenu(void) {
    printf("\n================================================\n");
    printf("  SISTEM INVENTARISASI LABORATORIUM EMBEDDED\n");
    printf("================================================\n");
    printf("  1. Tambah data barang\n");
    printf("  2. Hapus data barang\n");
    printf("  3. Cari data berdasarkan ID\n");
    printf("  4. Update stok barang\n");
    printf("  5. Update status barang\n");
    printf("  6. Tampilkan semua data\n");
    printf("  7. Tampilkan ringkasan inventaris\n");
    printf("  0. Keluar\n");
    printf("================================================\n");
    printf("Pilihan: ");
}

// Interface
void prosesInput(Node **head) {
    char pilihan[8];
    char idBuf[10];
    char statusBuf[20];
    char angkaBuf[32];
    Item itemBaru;

    while (1) {
        cetakMenu();
        bacaBaris(pilihan, sizeof(pilihan));

        if (strcmp(pilihan, "1") == 0) {
            printf("\n-- Tambah Data Barang --\n");
            int dataValid = 0;
            bacaItemBaru(&itemBaru, &dataValid);
            
            if (dataValid == 1) {
                tambahData(head, itemBaru);
            } else {
                printf("Gagal: Proses tambah data dibatalkan akibat format input salah.\n");
            }

        } else if (strcmp(pilihan, "2") == 0) {
            printf("ID yang akan dihapus: ");
            bacaBaris(idBuf, sizeof(idBuf));
            hapusData(head, idBuf);

        } else if (strcmp(pilihan, "3") == 0) {
            printf("ID yang dicari: ");
            bacaBaris(idBuf, sizeof(idBuf));
            printf("\n");
            cariData(*head, idBuf);

        } else if (strcmp(pilihan, "4") == 0) {
            printf("ID barang        : ");
            bacaBaris(idBuf, sizeof(idBuf));
            printf("Perubahan stok (+/-): ");
            bacaBaris(angkaBuf, sizeof(angkaBuf));
            
            int validAngka = 1;
            if (strlen(angkaBuf) == 0) validAngka = 0;
            for (int i = 0; i < strlen(angkaBuf); i++) {
                if (i == 0 && (angkaBuf[i] == '-' || angkaBuf[i] == '+')) continue;
                if (angkaBuf[i] < '0' || angkaBuf[i] > '9') {
                    validAngka = 0;
                    break;
                }
            }
            if (validAngka) {
                updateStok(*head, idBuf, atoi(angkaBuf));
            } else {
                printf("Input Anda tidak valid: Perubahan stok harus berupa angka!\n");
            }

        } else if (strcmp(pilihan, "5") == 0) {
            printf("ID barang  : ");
            bacaBaris(idBuf, sizeof(idBuf));
            printf("Status baru (tersedia/dipinjam/rusak/habis): ");
            bacaBaris(statusBuf, sizeof(statusBuf));
            updateStatus(*head, idBuf, statusBuf);

        } else if (strcmp(pilihan, "6") == 0) {
            tampilSemua(*head);

        } else if (strcmp(pilihan, "7") == 0) {
            tampilRingkasan(*head);

        } else if (strcmp(pilihan, "0") == 0) {
            printf("\nProgram selesai. Sampai jumpa!\n");
            break;

        } else {
            printf("\nPilihan tidak valid. Masukkan angka 0-7.\n");
        }
    }
}