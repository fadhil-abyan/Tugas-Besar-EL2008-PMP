#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "inventaris.h"

void tambahData(Node** head, Item item) {
    Node* current = *head;
    
    while (current != NULL) {
        if (strcmp(current->data.id, item.id) == 0) {
            printf_P(PSTR("Gagal: ID barang sudah terdaftar!\n"));
            return;
        }
        current = current->next;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf_P(PSTR("Gagal: Kapasitas memori tidak mencukupi!\n"));
        return;
    }

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
    printf_P(PSTR("Sukses: Data berhasil ditambahkan!\n"));
}