
## **Jawaban Pertanyaan Praktikum 2.5.4 (Seven Segment)**

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**


**2. Apa yang terjadi jika nilai num lebih dari 15?**

Jika variabel `num` melebihi 15, program akan mencoba mengakses indeks di luar batas array `digitPattern[16][8]` yang didefinisikan. Hal ini akan menyebabkan program membaca data "sampah" dari memori mikrokontroler, sehingga tampilan pada *Seven Segment* akan menjadi acak, tidak terdefinisi, atau menunjukkan pola yang salah.

**3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!**

Program ini menggunakan **Common Cathode (CC)**. Alasannya terlihat pada pola data `digitPattern`, di mana nilai **1** digunakan untuk menyalakan segmen dan **0** untuk mematikan. Misalnya, untuk menampilkan angka '0', segmen a sampai f diberikan logika **1** agar menyala.

**4. Modifikasi program agar tampilan berjalan dari F ke 0.**

Untuk membalik urutan, hanya perlu mengubah parameter pada perulangan `for` di dalam fungsi `loop()`:
```cpp
void loop() {
  for(int i = 15; i >= 0; i--) { // Dimulai dari 15 (F) turun ke 0
    displayDigit(i);
    delay(1000);
  }
}

[cite_start]Berdasarkan perintah pada **Pertanyaan Praktikum 2.5.4 poin 4** dalam modul[cite: 202], berikut adalah modifikasi kode program agar tampilan pada *Seven Segment* berjalan mundur dari **F ke 0**, serta penjelasan kode dalam format **README.md**.

### **1. Kode Program Modifikasi (F ke 0)**

```cpp
#include <Arduino.h>

// Pin mapping segment (a, b, c, d, e, f, g, dp)
[cite_start]const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4}; [cite: 138, 195]

// Pola segmen untuk karakter Hexadecimal 0-F
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,0}, // A
  {0,0,1,1,1,1,1,0}, // b
  {1,0,0,1,1,1,0,0}, // C
  {0,1,1,1,1,0,1,0}, // d
  {1,0,0,1,1,1,1,0}, // E
  {1,0,0,0,1,1,1,0}  // F
[cite_start]}; [cite: 153-178]

void displayDigit(int num) {
  for(int i = 0; i < 8; i++) {
    // Inversi (!) dilakukan jika menggunakan Seven Segment Common Anode
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup() {
  // Mengatur semua pin segmen sebagai OUTPUT
  for(int i = 0; i < 8; i++) {
    [cite_start]pinMode(segmentPins[i], OUTPUT); [cite: 151]
  }
}

void loop() {
  // PERUBAHAN: Perulangan dimulai dari 15 (F) turun ke 0
  for(int i = 15; i >= 0; i--) { 
    displayDigit(i);
    delay(1000); // Jeda 1 detik setiap perubahan karakter
  }
}
```

---

### **2. Penjelasan Kode**

```markdown
# Dokumentasi Modifikasi Program Seven Segment (F ke 0)

Program ini merupakan modifikasi dari Percobaan 2A untuk menampilkan karakter Hexadecimal secara mundur (decrement) dari F ke 0.

## Penjelasan Baris Kode

* **#include <Arduino.h>** : Memasukkan library standar Arduino untuk fungsi dasar.
* **const int segmentPins[8]** : Mendefinisikan array yang berisi urutan pin digital Arduino (7, 6, 5, 11, 10, 8, 9, 4) yang terhubung ke segmen a, b, c, d, e, f, g, dan dp.
* **byte digitPattern[16][8]** : Matriks 2 dimensi yang menyimpan pola logika biner (0 dan 1) untuk membentuk karakter 0-9 dan A-F pada display.
* **void displayDigit(int num)** : Fungsi khusus untuk mengirimkan sinyal digital ke pin segmen berdasarkan pola karakter yang dipilih.
* **digitalWrite(segmentPins[i], !digitPattern[num][i])** : Menyalakan atau mematikan segmen individu. Tanda `!` digunakan untuk membalik logika (inversi) agar sesuai dengan hardware Common Anode.
* **void setup()** : Fungsi yang berjalan sekali saat sistem menyala untuk konfigurasi awal.
* **pinMode(segmentPins[i], OUTPUT)** : Mengonfigurasi setiap pin dalam array segmentPins sebagai output daya.
* **void loop()** : Fungsi utama yang berjalan terus-menerus.
* **for(int i = 15; i >= 0; i--)** : Logika inti modifikasi. Perulangan dimulai dari indeks 15 (karakter F) dan berkurang (decrement) hingga mencapai 0.
* **displayDigit(i)** : Memanggil fungsi penampil untuk mencetak karakter sesuai nilai `i`.
* **delay(1000)** : Memberikan jeda waktu selama 1000 milidetik (1 detik) sebelum berganti ke karakter berikutnya.
```

Perubahan utama terletak pada struktur `for` di dalam `void loop()`. Dengan mengubah nilai awal menjadi `15`, kondisi menjadi `i >= 0`, dan langkah menjadi `i--`, program akan mengeksekusi urutan mundur sesuai dengan instruksi praktikum.

