#ifndef INVENTARIS_H
#define INVENTARIS_H

typedef struct Item {
    char id[10];
    char nama[50];
    char kategori[30];
    int stok;
    char lokasi[30];
    char status[20];    // status: "tersedia", "dipinjam", "rusak", "habis"
    char pemilik[30];
    char pic[30];
} Item;

typedef struct Node {
    Item data;
    struct Node* next;
} Node;

/**
 * @brief Menambahkan data inventaris baru ke dalam struktur data linked list.
 * @param item Struct Item yang berisi kelengkapan data barang yang akan ditambahkan.
 */
void tambahData(Node** head, Item item);

/**
 * @brief Menghapus data barang dari linked list berdasarkan ID barang.
 * @param id String yang merepresentasikan ID barang yang ingin dihapus.
 */
void hapusData(Node** head, char* id);

/**
 * @brief Mencari data barang tertentu dan menampilkannya ke Serial Monitor.
 * @param id String yang merepresentasikan ID barang yang dicari.
 */
void cariData(Node* head, char* id);

/**
 * @brief Memperbarui jumlah stok untuk barang tertentu.
 * @param id String yang merepresentasikan ID barang yang akan diperbarui stoknya.
 * @param jumlah Nilai integer untuk stok barang yang baru.
 */
void updateStok(Node* head, char* id, int jumlah);

/**
 * @brief Memperbarui status ketersediaan barang tertentu.
 * @param id String yang merepresentasikan ID barang yang akan diperbarui statusnya.
 * @param status String status yang baru (contoh: "tersedia", "dipinjam", "rusak", "habis").
 */
void updateStatus(Node* head, char* id, char* status);

/**
 * @brief Menampilkan seluruh data inventaris yang ada di dalam sistem ke Serial Monitor.
 * @param head Node pertama linked list untuk mengakses ke keseluruhan data
 */
void tampilSemua(Node* head);

/**
 * @brief Menampilkan ringkasan inventaris (misal: total barang, barang rusak, dll) ke Serial Monitor.
 * @param head Node pertama linked list.
 */
void tampilRingkasan(Node* head);

/**
 * @brief Menerima, membaca, dan memproses pilihan menu serta input data dari Serial Monitor.
 *        Ini adalah loop utama program; dipanggil satu kali dari main().
 * @param head Pointer ganda ke head karena isi data ingin diubah melalui input pengguna.
 */
void prosesInput(Node** head);

#endif