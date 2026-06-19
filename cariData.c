#include <stdio.h>
#include <stdlib.h>
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
      Serial.print("ID: "); Serial.println(current->data.id);
      Serial.print("Nama: "); Serial.println(current->data.nama);
      Serial.print("Kategori: "); Serial.println(current->data.kategori);
      Serial.print("Stok: "); Serial.println(current->data.stok);
      Serial.print("Lokasi: "); Serial.println(current->data.lokasi);
      Serial.print("Status: "); Serial.println(current->data.status);
      Serial.print("Pemilik: "); Serial.println(current->data.pemilik);
      Serial.print("PIC: "); Serial.println(current->data.pic);
      return;
    }
    current = current->next;
  }
  Serial.println("Pencarian Gagal: ID tidak ditemukan di dalam sistem!");
}
