#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "inventaris.h"

void hapusData(Node** head, char* id) {
    Node* curr = *head;
    Node* prev = NULL;
   
    while(curr != NULL && strcmp(curr->data.id,id) != 0){
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL){
        printf_P(PSTR("Data tidak ditemukan\n"));
        return;
    }

    if (curr == *head){
        Node *temp = curr;
        *head = curr->next;
        free(temp);
        printf_P(PSTR("Sukses: Data berhasil dihapus!\n"));
        return;
    } else {
        prev->next = curr->next;
        free(curr);
        printf_P(PSTR("Sukses: Data berhasil dihapus!\n"));
        return;
    }
}