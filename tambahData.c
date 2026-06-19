#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"

void tambahData(Node** head, Item item) {
  // Pengecekan ID duplikat
  Node* current = *head;
  
  while (current != NULL) {
    if (strcmp(current->data.id, item.id) == 0) {
      printf("Gagal: ID barang sudah terdaftar!");
      return;
    }
    current = current->next;
  }

  // Penanganan Kapasitas Memori Habis
  Node* newNode = (Node*)malloc(sizeof(Node));
  
  if (newNode == NULL) {
    printf("Gagal: Kapasitas memori tidak mencukupi!");
    return;
  }

  // Penambahan Data Ke Node Baru
  newNode->data = item;
  newNode->next = NULL;
  
  if (*head == NULL) {
    *head = newNode;
  } else {
    current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
  printf("Sukses: Data berhasil ditambahkan!");
}
