#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <avr/pgmspace.h>
#include "inventaris.h"

static void ubahKeHurufKecil(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

static void ubahKeHurufBesar(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

extern void bacaBarisSerial(char *buf, int ukuran);

static void bacaBaris(char *buf, int ukuran) {
    bacaBarisSerial(buf, ukuran);
}

static void bacaItemBaru(Item *item, int *validFlag) {
    char buffer[64];
    *validFlag = 1;

    printf_P(PSTR("ID Barang   : "));
    bacaBaris(item->id, sizeof(item->id));
    if (strlen(item->id) == 0) {
        printf_P(PSTR("Input Anda tidak valid: ID barang tidak boleh kosong!\n"));
        *validFlag = 0; return;
    }
    ubahKeHurufBesar(item->id); 

    printf_P(PSTR("Nama        : "));
    bacaBaris(item->nama, sizeof(item->nama));

    printf_P(PSTR("Kategori    : "));
    bacaBaris(item->kategori, sizeof(item->kategori));

    printf_P(PSTR("Stok        : "));
    bacaBaris(buffer, sizeof(buffer));
    if (strlen(buffer) == 0) {
        printf_P(PSTR("Input Anda tidak valid: Stok tidak boleh kosong!\n"));
        *validFlag = 0; return;
    }

    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            printf_P(PSTR("Input Anda tidak valid: Stok harus berupa angka bilangan bulat positif.\n"));
            *validFlag = 0; return;
        }
    }
    item->stok = atoi(buffer);

    printf_P(PSTR("Lokasi      : "));
    bacaBaris(item->lokasi, sizeof(item->lokasi));

    printf_P(PSTR("Status (tersedia/dipinjam/rusak/habis): "));
    bacaBaris(item->status, sizeof(item->status));
    ubahKeHurufKecil(item->status);

    if (strcmp(item->status, "tersedia") != 0 && 
        strcmp(item->status, "dipinjam") != 0 && 
        strcmp(item->status, "rusak") != 0 && 
        strcmp(item->status, "habis") != 0) {
        printf_P(PSTR("Input Anda tidak valid: Status harus persis (tersedia, dipinjam, rusak, atau habis).\n"));
        *validFlag = 0; return;
    }

    printf_P(PSTR("Pemilik     : "));
    bacaBaris(item->pemilik, sizeof(item->pemilik));

    printf_P(PSTR("PIC         : "));
    bacaBaris(item->pic, sizeof(item->pic));
}

static void cetakMenu(void) {
    printf_P(PSTR("\n================================================\n"));
    printf_P(PSTR("  SISTEM INVENTARISASI LABORATORIUM EMBEDDED\n"));
    printf_P(PSTR("================================================\n"));
    printf_P(PSTR("  1. Tambah data barang\n"));
    printf_P(PSTR("  2. Hapus data barang\n"));
    printf_P(PSTR("  3. Cari data berdasarkan ID\n"));
    printf_P(PSTR("  4. Update stok barang\n"));
    printf_P(PSTR("  5. Update status barang\n"));
    printf_P(PSTR("  6. Tampilkan semua data\n"));
    printf_P(PSTR("  7. Tampilkan ringkasan inventaris\n"));
    printf_P(PSTR("  0. Keluar\n"));
    printf_P(PSTR("================================================\n"));
    printf_P(PSTR("Pilihan: "));
}

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
            printf_P(PSTR("\n-- Tambah Data Barang --\n"));
            int dataValid = 0;
            bacaItemBaru(&itemBaru, &dataValid);
            
            if (dataValid == 1) {
                tambahData(head, itemBaru);
            } else {
                printf_P(PSTR("Gagal: Proses tambah data dibatalkan akibat format input salah.\n"));
            }

        } else if (strcmp(pilihan, "2") == 0) {
            printf_P(PSTR("ID yang akan dihapus: "));
            bacaBaris(idBuf, sizeof(idBuf));
            ubahKeHurufBesar(idBuf);
            hapusData(head, idBuf);

        } else if (strcmp(pilihan, "3") == 0) {
            printf_P(PSTR("ID yang dicari: "));
            bacaBaris(idBuf, sizeof(idBuf));
            ubahKeHurufBesar(idBuf);
            printf_P(PSTR("\n"));
            cariData(*head, idBuf);

        } else if (strcmp(pilihan, "4") == 0) {
            printf_P(PSTR("ID barang        : "));
            bacaBaris(idBuf, sizeof(idBuf));
            ubahKeHurufBesar(idBuf);
            
            printf_P(PSTR("Perubahan stok (+/-): "));
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
                printf_P(PSTR("Input Anda tidak valid: Perubahan stok harus berupa angka!\n"));
            }

        } else if (strcmp(pilihan, "5") == 0) {
            printf_P(PSTR("ID barang  : "));
            bacaBaris(idBuf, sizeof(idBuf));
            ubahKeHurufBesar(idBuf);
            
            printf_P(PSTR("Status baru (tersedia/dipinjam/rusak/habis): "));
            bacaBaris(statusBuf, sizeof(statusBuf));
            ubahKeHurufKecil(statusBuf); 
            updateStatus(*head, idBuf, statusBuf);

        } else if (strcmp(pilihan, "6") == 0) {
            tampilSemua(*head);

        } else if (strcmp(pilihan, "7") == 0) {
            tampilRingkasan(*head);

        } else if (strcmp(pilihan, "0") == 0) {
            printf_P(PSTR("\nProgram selesai. Sampai jumpa!\n"));
            break;

        } else {
            printf_P(PSTR("\nPilihan tidak valid. Masukkan angka 0-7.\n"));
        }
    }
}