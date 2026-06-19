#include <Arduino.h>
#include <stdio.h>

// Deklarasi extern "C" agar C++ Arduino mengenali file .c kita
extern "C" {
    #include "inventaris.h"
    void bacaBarisSerial(char *buf, int ukuran);
}

// ---------------------------------------------------------
// 1. JEMBATAN OUTPUT (printf -> Serial Monitor)
// ---------------------------------------------------------
static int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        Serial.write('\r'); // Menambahkan Carriage Return agar rapi
    }
    Serial.write(c);
    return 0;
}
static FILE uartout = {0};

// ---------------------------------------------------------
// 2. JEMBATAN INPUT (Serial Monitor -> fungsi fgets)
// ---------------------------------------------------------
void bacaBarisSerial(char *buf, int ukuran) {
    buf[0] = '\0';
    while (true) {
        if (Serial.available() > 0) {
            int len = Serial.readBytesUntil('\n', buf, ukuran - 1);
            buf[len] = '\0';
            // Membersihkan sisa karakter enter (\r) jika ada
            if (len > 0 && buf[len - 1] == '\r') {
                buf[len - 1] = '\0';
            }
            break; // Keluar dari loop setelah selesai membaca
        }
    }
}

// ---------------------------------------------------------
// 3. FUNGSI UTAMA SESUAI ATURAN TUGAS
// ---------------------------------------------------------
int main(void) {
    init(); // Wajib dipanggil untuk inisialisasi hardware Arduino Uno
    Serial.begin(9600);

    // "Menyihir" printf agar langsung terhubung ke Serial Monitor
    fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout;

    // Memanggil pemroses data
    Node* headInventaris = NULL;
    prosesInput(&headInventaris);

    // Loop pencegah program mati
    while(1) {} 
    
    return 0;
}