# Makefile — Sistem Inventarisasi Laboratorium (versi terintegrasi & diperbaiki)
# Penggunaan:
#   make        -> compile
#   make run    -> compile + jalankan
#   make clean  -> hapus binary

CC     = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = inventaris
SRCS   = main.c prosesInput.c tambahData.c hapusData.c cariData.c \
         updateStok.c updateStatus.c tampilkan.c

all: $(TARGET)

$(TARGET): $(SRCS) inventaris.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
