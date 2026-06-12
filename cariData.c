#include <stdio.h>
#include <string.h>
#include "inventaris.h"

void cariData(Node* head, char* id) {
  // Pengecekan Data Kosong
  Node* current = head;

  if (current == NULL) {
    Serial.println("Inventaris kosong. Tidak ada data yang dapat dicari!");
    return;
  }

  while (current != NULL) {
    if (strcmp(current->data.id, id) == 0) {
      // Serial.print("ID: "); Serial.println(current->data.id);
      // Serial.print("Nama: "); Serial.println(current->data.nama);
      // Serial.print("Stok: "); Serial.println(current->data.stok);
      // ...
      return;
    }
    current = current->next;
  }
  Serial.println("Pencarian Gagal: ID tidak ditemukan di dalam sistem!");
}
