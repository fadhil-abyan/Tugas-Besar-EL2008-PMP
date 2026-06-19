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
          (s[len - 1] == '\r' ||
           s[len - 1] == '\n' ||
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

static int statusValid(const char *status) {
    if (status == NULL) return 0;

    return (
        strcmp(status, "tersedia") == 0 ||
        strcmp(status, "dipinjam") == 0 ||
        strcmp(status, "rusak") == 0 ||
        strcmp(status, "habis") == 0
    );
}

void updateStatus(Node *head) {
    if (head == NULL) {
        printf("Inventaris kosong. Tidak ada data yang dapat diperbarui.\n");
        return;
    }

    char id[10];
    char statusBaru[20];

    bacaInputString("Masukkan ID barang yang ingin diupdate statusnya:", id, sizeof(id));

    Node *current = cariNode(head, id);
    if (current == NULL) {
        printf("Gagal: ID tidak ditemukan di dalam sistem.\n");
        return;
    }

    bacaInputString("Masukkan status baru (tersedia/dipinjam/rusak/habis):", statusBaru, sizeof(statusBaru));

    if (!statusValid(statusBaru)) {
        printf("Gagal: status tidak valid.\n");
        printf("Status yang diizinkan: tersedia, dipinjam, rusak, habis\n");
        return;
    }

    if (strcmp(statusBaru, "tersedia") == 0 && current->data.stok <= 0) {
        printf("Gagal: status 'tersedia' tidak cocok jika stok 0.\n");
        return;
    }

    salinString(current->data.status, sizeof(current->data.status), statusBaru);

    if (strcmp(statusBaru, "habis") == 0) {
        current->data.stok = 0;
    }

    printf("Sukses: status berhasil diperbarui.\n");
    printf("Status baru: %s\n", current->data.status);
    printf("Stok saat ini: %d\n", current->data.stok);
}
