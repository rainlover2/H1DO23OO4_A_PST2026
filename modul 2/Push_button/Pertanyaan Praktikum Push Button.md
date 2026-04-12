
## **Jawaban Pertanyaan Praktikum 2.6.4 (Push Button)**

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**

Skema rangkaian ini serupa dengan percobaan sebelumnya, namun ditambah dengan satu unit *push button* yang dihubungkan ke **Pin 2** Arduino dan **GND**.



**2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya?**

Mode `INPUT_PULLUP` mengaktifkan resistor internal di dalam mikrokontroler Arduino yang menghubungkan pin ke tegangan 5V secara default.

**Keuntungan:** Kita tidak perlu memasang resistor eksternal secara fisik di *breadboard*, sehingga rangkaian menjadi lebih sederhana dan ringkas. Selain itu, ini mencegah kondisi pin "mengambang" (*floating*) yang dapat menyebabkan pembacaan input tidak stabil.

**3. Jika salah satu LED segmen tidak menyala, apa kemungkinan penyebabnya?**

* **Sisi Hardware:** Kabel *jumper* putus atau kendor, resistor terbakar/rusak, pin *Seven Segment* bengkok tidak masuk ke *breadboard*, atau salah satu LED pada unit display memang sudah mati.
* **Sisi Software:** Kesalahan penulisan nomor pin pada array `segmentPins` [cite: 138, 226] [cite_start]atau kesalahan logika biner (angka 0/1) pada baris karakter tertentu di matriks `digitPattern]`.

**4. Modifikasi rangkaian dan program dengan dua push button (Increment & Decrement).**

Menambahkan satu tombol lagi (misal di Pin 3) dan mengubah logika `loop()` untuk mendeteksi penekanan tombol tambah dan tombol kurang secara terpisah, lalu memperbarui nilai `currentDigit` sebelum memanggil `displayDigit()`.

Berikut adalah modifikasi kode program tersebut. Saya menambahkan tombol kedua pada **Pin 2** dan menyertakan logika pengurangan serta batas bawah agar angka kembali ke 'F' (15) jika dikurangi di bawah 0.

---

### **Program Modifikasi: Counter Up/Down dengan 2 Push Button**

```cpp
#include <Arduino.h>

// ================= PIN =================
// Pin untuk segmen a, b, c, d, e, f, g, dp sesuai Tabel 1.4
[cite_start]const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4}; [cite: 195, 328]

const int btnUp = 3;   // Tombol Tambah
const int btnDown = 2; [cite_start]// Tombol Kurang (Tambahan Baru) [cite: 337]

// ================= DATA =================
// Pola biner untuk karakter Hexadecimal 0-F
[cite_start]// Logika 1 = ON untuk Common Cathode [cite: 252]
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, //0
  {0,1,1,0,0,0,0,0}, //1
  {1,1,0,1,1,0,1,0}, //2
  {1,1,1,1,0,0,1,0}, //3
  {0,1,1,0,0,1,1,0}, //4
  {1,0,1,1,0,1,1,0}, //5
  {1,0,1,1,1,1,1,0}, //6
  {1,1,1,0,0,0,0,0}, //7
  {1,1,1,1,1,1,1,0}, //8
  {1,1,1,1,0,1,1,0}, //9
  {1,1,1,0,1,1,1,0}, //A
  {0,0,1,1,1,1,1,0}, //b
  {1,0,0,1,1,1,0,0}, //C
  {0,1,1,1,1,0,1,0}, //d
  {1,0,0,1,1,1,1,0}, //E
  {1,0,0,0,1,1,1,0}  //F
[cite_start]}; [cite: 153-178, 255-308]

int currentDigit = 0;

// State sebelumnya untuk mendeteksi perubahan tekanan (Edge Detection)
bool lastUpState = HIGH;
bool lastDownState = HIGH;

// ================= FUNCTION =================
void displayDigit(int num) {
  for(int i = 0; i < 8; i++) {
    // Menggunakan '!' jika Seven Segment Anda adalah Common Anode
    // Jika Common Cathode, hapus tanda '!' tersebut
    [cite_start]digitalWrite(segmentPins[i], !digitPattern[num][i]); [cite: 238]
  }
}

// ================= SETUP =================
void setup() {
  // Inisialisasi semua pin segmen sebagai OUTPUT
  for(int i = 0; i < 8; i++) {
    [cite_start]pinMode(segmentPins[i], OUTPUT); [cite: 254]
  }

  [cite_start]// Menggunakan INPUT_PULLUP agar tidak perlu resistor eksternal [cite: 265, 335]
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);

  // Tampilan awal
  [cite_start]displayDigit(currentDigit); [cite: 272]
}

// ================= LOOP =================
void loop() {
  // Membaca status tombol saat ini
  [cite_start]bool upState = digitalRead(btnUp); [cite: 288]
  bool downState = digitalRead(btnDown);

  // ===== LOGIKA TOMBOL TAMBAH (UP) =====
  if(lastUpState == HIGH && upState == LOW) { // Tombol ditekan
    currentDigit++;
    if(currentDigit > 15) currentDigit = 0; // Reset ke 0 jika lebih dari F
    displayDigit(currentDigit);
    delay(50); // Debounce sederhana
  }

  // ===== LOGIKA TOMBOL KURANG (DOWN) =====
  if(lastDownState == HIGH && downState == LOW) { // Tombol ditekan
    currentDigit--;
    if(currentDigit < 0) currentDigit = 15; // Kembali ke F jika kurang dari 0
    displayDigit(currentDigit);
    delay(50); // Debounce sederhana
  }

  // Simpan state saat ini untuk pengecekan berikutnya
  [cite_start]lastUpState = upState; [cite: 320]
  lastDownState = downState;
}
```

---

### **Penjelasan Perubahan Penting:**

1.  **Penambahan `btnDown`**: Mendefinisikan pin input baru (Pin 2) untuk fungsi pengurangan.
2.  **Inisialisasi `INPUT_PULLUP`**: Kedua tombol menggunakan resistor internal Arduino agar tetap stabil pada logika HIGH saat tidak ditekan.
3.  **Logika Decrement**: Menambahkan blok `if` untuk mendeteksi tekanan pada tombol bawah. Jika ditekan, `currentDigit` akan berkurang 1.
4.  **Batas Bawah (Underflow)**: Jika angka dikurangi saat posisi '0', sistem akan secara otomatis melompat ke angka '15' (karakter F) agar counter berjalan melingkar.
5.  **Debounce**: Menambahkan `delay(50)` untuk mencegah pembacaan ganda yang tidak disengaja akibat getaran mekanis pada tombol (*glitch*).
