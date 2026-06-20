#include <Arduino.h>
#include <stdio.h>

extern "C" {
    #include "inventaris.h"
    void bacaBarisSerial(char *buf, int ukuran);
}

static int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        Serial.write('\r');
    }
    Serial.write(c);
    return 0;
}
static FILE uartout = {0};

void bacaBarisSerial(char *buf, int ukuran) {
    buf[0] = '\0';
    while (true) {
        if (Serial.available() > 0) {
            int len = Serial.readBytesUntil('\n', buf, ukuran - 1);
            buf[len] = '\0';
            if (len > 0 && buf[len - 1] == '\r') {
                buf[len - 1] = '\0';
            }
            break;
        }
    }
}

int main(void) {
    init();
    Serial.begin(9600);

    fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout;

    Node* headInventaris = NULL;
    prosesInput(&headInventaris);

    while(1) {} 
    
    return 0;
}