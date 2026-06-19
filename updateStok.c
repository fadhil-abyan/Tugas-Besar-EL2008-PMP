#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventaris.h"

static void salinString(char *dst, size_t dstSize, const char *src) {
    if (dst == NULL || dstSize == 0) return;
    if (src == NULL) {
        dst[0] = '\0';
        return;
    }

    strncpy(dst, src, dstSize - 1);
    dst[dstSize - 1] = '\0';
}

static void trimBaris(char *s) {
    if (s == NULL) return;

    size_t len = strlen(s);
    while (len > 0 &&
           (s[len - 1] == '\n' ||
            s[len - 1] == '\r' ||
            s[len - 1] == ' '  ||
            s[len - 1] == '\t')) {
        s[len - 1] = '\0';
        len--;
    }

    size_t start = 0;
    while (s[start] == ' ' || s[start] == '\t') {
        start++;
    }

    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }
}

static void bacaInputString(const char *prompt, char *out, size_t outSize) {
    if (out == NULL || outSize == 0) return;

    printf("%s\n", prompt);

    if (fgets(out, (int)outSize, stdin) == NULL) {
        out[0] = '\0';
        return;
    }

    trimBaris(out);
}

static int bacaInputInt(const char *prompt) {
    char buffer[20];
    bacaInputString(prompt, buffer, sizeof(buffer));
    return atoi(buffer);
}

static Node* cariNode(Node *head, const char *id) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateStok(Node *head) {
    if (head == NULL) {
        printf("Inventaris kosong. Tidak ada data yang dapat diperbarui.\n");
        return;
    }

    char id[10];
    char buffer[20];

    bacaInputString("Masukkan ID barang yang ingin diupdate stoknya:", id, sizeof(id));

    Node *current = cariNode(head, id);
    if (current == NULL) {
        printf("Gagal: ID tidak ditemukan di dalam sistem.\n");
        return;
    }

    printf("Stok saat ini: %d\n", current->data.stok);

    bacaInputString(
        "Masukkan perubahan stok (positif = tambah, negatif = kurangi):",
        buffer,
        sizeof(buffer)
    );

    int jumlah = atoi(buffer);
    int stokBaru = current->data.stok + jumlah;

    if (stokBaru < 0) {
        printf("Gagal: stok tidak mencukupi, hasil akhir tidak boleh negatif.\n");
        return;
    }

    current->data.stok = stokBaru;

    if (current->data.stok == 0) {
        salinString(current->data.status, sizeof(current->data.status), "habis");
    } else if (strcmp(current->data.status, "habis") == 0) {
        salinString(current->data.status, sizeof(current->data.status), "tersedia");
    }

    printf("Sukses: stok berhasil diperbarui.\n");
    printf("Stok baru: %d\n", current->data.stok);
    printf("Status saat ini: %s\n", current->data.status);
}
