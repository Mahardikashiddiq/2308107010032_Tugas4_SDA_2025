#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "sorting.h"

#define MAX_WORD_LEN 100
#define MAX_DATA 2000000

// Variabel global untuk manajemen memori
int *original_int = NULL;
int *copy_int = NULL;
char **original_str = NULL;
char **copy_str = NULL;
size_t current_allocated_size = 0;

// Prototipe fungsi
void load_data_int(const char *filename, int *arr, int n);      // Memuat data integer dari file ke array
void load_data_str(const char *filename, char **arr, int n);    // Memuat data string dari file ke array
void jalankan_sorting_int(int n);                               // Menjalankan pengujian algoritma sorting untuk data integer
void jalankan_sorting_str(int n);                               // Menjalankan pengujian algoritma sorting untuk data string
void cleanup_memory();                                          // Membersihkan memori yang dialokasikan

// Fungsi untuk memuat data angka dari file ke array integer
void load_data_int(const char *filename, int *arr, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Gagal membuka file %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "File %s berisi kurang dari %d angka (hanya %d ditemukan).\n", filename, n, i);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

// Fungsi untuk memuat data kata dari file ke array string
void load_data_str(const char *filename, char **arr, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Gagal membuka file %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    char buffer[MAX_WORD_LEN];
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%99s", buffer) != 1) {
            fprintf(stderr, "File %s berisi kurang dari %d kata (hanya %d ditemukan).\n", filename, n, i);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        arr[i] = (char *)malloc(strlen(buffer) + 1);
        if (!arr[i]) {
            fprintf(stderr, "Gagal mengalokasikan memori untuk kata ke-%d.\n", i);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        strcpy(arr[i], buffer);
    }
    fclose(fp);
}

// Fungsi untuk menjalankan dan mengukur performa semua algoritma sorting untuk data integer
void jalankan_sorting_int(int n) {
    // Alokasi memori untuk data asli dan salinan
    original_int = (int *)malloc(n * sizeof(int));
    copy_int = (int *)malloc(n * sizeof(int));
    if (!original_int || !copy_int) {
        fprintf(stderr, "Gagal mengalokasikan memori untuk %d data integer (%zu MB).\n",
                n, (2 * n * sizeof(int)) / (1024.0 * 1024.0));
        cleanup_memory();
        exit(EXIT_FAILURE);
    }

    // Memuat data dari file
    load_data_int("../data/data_angka.txt", original_int, n);

    // Menampilkan header tabel hasil
    printf("\nProses Sorting %d data...\n\n", n);
    printf("+----------------------------+--------------+--------------+\n");
    printf("|         Algoritma          |  Waktu (s)   | Memori (MB)  |\n");
    printf("+----------------------------+--------------+--------------+\n");

    // Menjalankan semua algoritma sorting untuk integer
    memcpy(copy_int, original_int, n * sizeof(int));
    benchmark_sort_int("Bubble Sort (int)", bubble_sort_int, copy_int, n);

    memcpy(copy_int, original_int, n * sizeof(int));
    benchmark_sort_int("Selection Sort (int)", selection_sort_int, copy_int, n);

    memcpy(copy_int, original_int, n * sizeof(int));
    benchmark_sort_int("Insertion Sort (int)", insertion_sort_int, copy_int, n);

    memcpy(copy_int, original_int, n * sizeof(int));
    benchmark_sort_int("Merge Sort (int)", merge_sort_int_wrapper, copy_int, n);

    memcpy(copy_int, original_int, n * sizeof(int));
    benchmark_sort_int("Quick Sort (int)", quick_sort_int_wrapper, copy_int, n);

    memcpy(copy_int, original_int, n * sizeof(int));
    benchmark_sort_int("Shell Sort (int)", shell_sort_int, copy_int, n);

    printf("+----------------------------+--------------+--------------+\n");
}

// Fungsi untuk menjalankan dan mengukur performa semua algoritma sorting untuk data string
void jalankan_sorting_str(int n) {
    // Alokasi memori untuk array string
    original_str = (char **)malloc(n * sizeof(char *));
    copy_str = (char **)malloc(n * sizeof(char *));
    if (!original_str || !copy_str) {
        fprintf(stderr, "Gagal mengalokasikan memori untuk %d data string.\n", n);
        cleanup_memory();
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        original_str[i] = (char *)malloc(MAX_WORD_LEN);
        copy_str[i] = (char *)malloc(MAX_WORD_LEN);
        if (!original_str[i] || !copy_str[i]) {
            fprintf(stderr, "Gagal mengalokasikan memori untuk string ke-%d.\n", i);
            cleanup_memory();
            exit(EXIT_FAILURE);
        }
    }
    current_allocated_size = n;

    // Memuat data string dari file
    load_data_str("../data/data_kata.txt", original_str, n);

    // Menampilkan header tabel hasil
    printf("\nMenjalankan sorting untuk %d data...\n\n", n);
    printf("+----------------------------+-----------+----------------+\n");
    printf("|         Algoritma          | Waktu(s)  | Penyimpanan(MB)|\n");
    printf("+----------------------------+-----------+----------------+\n");
    
    // Menjalankan semua algoritma sorting untuk string
    for (int i = 0; i < n; i++) strcpy(copy_str[i], original_str[i]);
    benchmark_sort_str("Bubble Sort (abjad)  ", bubble_sort_str, copy_str, n);
    
    for (int i = 0; i < n; i++) strcpy(copy_str[i], original_str[i]);
    benchmark_sort_str("Selection Sort(abjad)", selection_sort_str, copy_str, n);
    
    for (int i = 0; i < n; i++) strcpy(copy_str[i], original_str[i]);
    benchmark_sort_str("Insertion Sort(abjad)", insertion_sort_str, copy_str, n);
    
    for (int i = 0; i < n; i++) strcpy(copy_str[i], original_str[i]);
    benchmark_sort_str("Merge Sort  (abjad)  ", merge_sort_str_wrapper, copy_str, n);
    
    for (int i = 0; i < n; i++) strcpy(copy_str[i], original_str[i]);
    benchmark_sort_str("Quick Sort (abjad)   ", quick_sort_str_wrapper, copy_str, n);
    
    for (int i = 0; i < n; i++) strcpy(copy_str[i], original_str[i]);
    benchmark_sort_str("Shell Sort  (abjad)  ", shell_sort_str, copy_str, n);
    
    printf("+----------------------------+-----------+----------------+\n");
}    

// Fungsi untuk membersihkan seluruh memori yang dialokasikan secara dinamis
void cleanup_memory() {
    if (original_int) {
        free(original_int);
        original_int = NULL;
    }
    if (copy_int) {
        free(copy_int);
        copy_int = NULL;
    }
    if (original_str) {
        for (size_t i = 0; i < current_allocated_size; i++) {
            if (original_str[i]) free(original_str[i]);
            if (copy_str[i]) free(copy_str[i]);
        }
        free(original_str);
        free(copy_str);
        original_str = NULL;
        copy_str = NULL;
        current_allocated_size = 0;
    }
}

// Fungsi untuk menampilkan menu pilihan jenis data (angka atau kata)
int pilih_jenis_data() {
    int pilihan;
    printf("=== PILIH JENIS DATA ===\n");
    printf("1. Angka\n2. Kata\nMasukkan pilihan [1-2]: ");
    if (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > 2) {
        printf("Pilihan tidak valid.\n");
        while (getchar() != '\n'); // Mengosongkan buffer input
        exit(EXIT_FAILURE);
    }
    while (getchar() != '\n'); // Mengosongkan buffer input
    return pilihan;
}

// Fungsi untuk menampilkan menu pilihan ukuran data yang akan diuji
int pilih_ukuran_data() {
    int pilihan;
    int ukuran_data[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    printf("\n=== PILIH UKURAN DATA ===\n");
    for (int i = 0; i < 8; i++) printf("%d. %d data\n", i + 1, ukuran_data[i]);
    printf("Masukkan pilihan [1-8]: ");
    if (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > 8) {
        printf("Pilihan tidak valid.\n");
        while (getchar() != '\n'); // Mengosongkan buffer input
        exit(EXIT_FAILURE);
    }
    while (getchar() != '\n'); // Mengosongkan buffer input
    return ukuran_data[pilihan - 1];
}

// Fungsi utama program
int main() {
    int jenis = pilih_jenis_data();      // Memilih apakah data berupa angka atau kata
    int n = pilih_ukuran_data();         // Memilih berapa banyak data yang ingin diuji

    cleanup_memory();                    // Membersihkan alokasi sebelum digunakan

    if (jenis == 1) {
        jalankan_sorting_int(n);         // Menjalankan sorting untuk data integer
    } else {
        jalankan_sorting_str(n);         // Menjalankan sorting untuk data string
    }

    cleanup_memory();                    // Membersihkan memori setelah selesai
    return 0;
}
