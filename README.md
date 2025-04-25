Nama  : Mahardika Shiddiq Anshari
NPM   : 2308107010032
Kelas : SDA D 

# README - Program Perbandingan Algoritma Sorting

Program ini merupakan alat untuk membandingkan performa berbagai algoritma sorting menggunakan data angka (integer) dan kata (string). Program utama mengimplementasikan 6 algoritma sorting yang berbeda dan mengukur waktu eksekusi serta penggunaan memori untuk setiap algoritma pada dataset dengan ukuran yang bervariasi.

## Struktur Program

Program terdiri dari beberapa file:

1. main.c: File utama yang mengatur alur program, menangani input pengguna, memuat data, dan melakukan benchmarking.
2. sorting.h: Header file yang berisi implementasi algoritma sorting untuk data integer dan string.
3. angka.c: Program untuk membangkitkan data acak berupa angka/integer.
4. kata.c: Program untuk membangkitkan data acak berupa kata/string.

## Algoritma Sorting yang Diimplementasikan

Program ini mengimplementasikan 6 algoritma sorting populer:
- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Shell Sort

Setiap algoritma diimplementasikan untuk kedua jenis data: integer dan string.

## Cara Penggunaan

1. Pertama, gunakan `angka.c` dan `kata.c` untuk membangkitkan data uji:
   ```
   gcc angka.c -o angka
   ./angka
   gcc kata.c -o kata
   ./kata
   ```

2. Kompilasi program utama:
   ```
   gcc main.c -o main
   ./main
   ``

3. Ikuti petunjuk pada program:
   - Pilih jenis data (1 untuk angka, 2 untuk kata)
   - Pilih ukuran data yang ingin diuji (10.000 hingga 2.000.000)

4. Program akan menampilkan hasil performa setiap algoritma sorting dalam format tabel.

## Detail Implementasi

### Pembangkitan Data
- `angka.c`: Menghasilkan file `data_angka.txt` berisi angka acak dengan nilai maksimal 2.000.000.
- `kata.c`: Menghasilkan file `data_kata.txt` berisi kata acak dengan panjang 3-20 karakter.

### Program Utama (main.c)
- Menyediakan manajemen memori untuk data yang akan diurutkan
- Memuat data dari file ke dalam array
- Menjalankan dan mengukur waktu eksekusi setiap algoritma sorting
- Menampilkan hasil dalam bentuk tabel yang terformat
- Membersihkan memori setelah digunakan

### Algoritma Sorting (sorting.h)
- Mengimplementasikan 6 algoritma sorting untuk data integer dan string
- Menyediakan fungsi wrapper untuk algoritma rekursif (Merge Sort dan Quick Sort)
- Menyediakan fungsi benchmark untuk mengukur waktu eksekusi.
