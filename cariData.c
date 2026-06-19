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
      print("ID: %s\n", current->data.id);
      print("Nama: %s\n", current->data.nama);
      print("Kategori: %s\n", current->data.kategori);
      print("Stok: %d\n", current->data.stok);
      print("Lokasi: %s\n", current->data.lokasi);
      print("Status: %s\n", current->data.status);
      print("Pemilik: %s\n", current->data.pemilik);
      print("PIC: %s\n", current->data.pic);
      return;
    }
    current = current->next;
  }
  printf("Pencarian Gagal: ID tidak ditemukan di dalam sistem!");
}
