#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventaris.h"

void hapusData(Node** head, char* id) {
    // mulai awalnya di head
    Node* curr = *head;
    Node* prev = NULL;
   
    //cek semua data dengan loop
    while(curr != NULL && strcmp(curr->data.id,id) != 0){
        prev = curr;
        curr = curr->next;
    }
    //kasus pertama ketika data yang ingin dihapus tidak ditemukan
    if (curr == NULL){
        printf("Data tidak ditemukan");
        return;
    }

    //kasus kedua ketika penghapusan node pertama (head)
    if (curr == *head){
        Node *temp = curr;
        *head = curr->next;
        free(temp);
        return;
    }

    //kasus ketiga ketika penghapusan node ada di tengah atau di akhir
    else{
        prev->next = curr->next;
        free(curr);
        return;
    }

} 