#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

void cariData(Node* head, char* id) {
  // Pengecekan Data Kosong
  Node* current = head;

  if (current == NULL) {
    printf("Inventaris kosong. Tidak ada data yang dapat dicari!");
    return;
  }

  while (current != NULL) {
    if (strcmp(current->data.id, id) == 0) {
      printf("ID: %s\n", current->data.id);
      printf("Nama: %s\n", current->data.nama);
      printf("Kategori: %s\n", current->data.kategori);
      printf("Stok: %d\n", current->data.stok);
      printf("Lokasi: %s\n", current->data.lokasi);
      printf("Status: %s\n", current->data.status);
      printf("Pemilik: %s\n", current->data.pemilik);
      printf("PIC: %s\n", current->data.pic);
      return;
    }
    current = current->next;
  }
  printf("Pencarian Gagal: ID tidak ditemukan di dalam sistem!");
}
