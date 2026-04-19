
### **1) Proses dari Input Keyboard hingga LED Menyala/Mati**

Proses komunikasi ini menggunakan protokol **UART (Universal Asynchronous Receiver-Transmitter)**. Berikut adalah alur kerjanya:
1.  **Input:** Pengguna mengetik karakter '1' atau '0' di Serial Monitor pada komputer.
2.  **Transmisi:** Data dikirim secara serial (satu per satu bit) melalui kabel USB menuju pin RX pada Arduino.
3.  **Buffering:** Data yang masuk disimpan sementara di dalam *serial buffer* Arduino.
4.  **Pengecekan:** Program menjalankan fungsi `Serial.available()` untuk memastikan ada data yang masuk ke buffer.
5.  **Pembacaan:** Fungsi `Serial.read()` mengambil karakter tersebut dan menyimpannya dalam variabel `data`.
6.  **Eksekusi:** Melalui struktur **percabangan (if-else)**, program membandingkan nilai variabel:
    * Jika `data == '1'`, Arduino mengirim sinyal `HIGH` ke `PIN_LED` sehingga LED menyala.
    * Jika `data == '0'`, Arduino mengirim sinyal `LOW` ke `PIN_LED` sehingga LED mati.



---

### **2) Fungsi `Serial.available()` dan Dampak Jika Dihilangkan**

* **Mengapa digunakan:** Fungsi ini berfungsi untuk mengecek apakah ada data serial yang telah diterima dan siap untuk dibaca. Tanpa pengecekan ini, Arduino tidak tahu apakah ada data baru atau tidak.
* **Jika dihilangkan:** Jika baris `if (Serial.available() > 0)` dihapus, fungsi `Serial.read()` akan terus dijalankan pada setiap perulangan `loop()`. Karena `loop()` berjalan sangat cepat, saat tidak ada data yang masuk, `Serial.read()` akan mengembalikan nilai `-1`. Hal ini akan menyebabkan blok `else` (perintah tidak dikenal) tereksekusi secara terus-menerus, sehingga Serial Monitor akan dipenuhi pesan error meskipun kamu tidak mengetik apa pun.

---

### **3) Modifikasi Program (Mode Blink)**

Untuk membuat LED terus berkedip sampai ada perintah baru, kita perlu menggunakan variabel "status" (state) untuk menyimpan perintah terakhir yang diterima.

#### **Source Code Modifikasi**
```cpp
const int PIN_LED = 12;
char statusPerintah = '0'; // Menyimpan status terakhir
unsigned long previousMillis = 0;
const long interval = 500; // Interval kedip 500ms
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1': ON, '0': OFF, '2': Blink");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  // Cek input baru dari Serial Monitor
  if (Serial.available() > 0) {
    statusPerintah = Serial.read();
    
    // Respon instan saat menerima input
    if (statusPerintah == '1') {
      digitalWrite(PIN_LED, HIGH);
      Serial.println("Mode: LED ON");
    } 
    else if (statusPerintah == '0') {
      digitalWrite(PIN_LED, LOW);
      Serial.println("Mode: LED OFF");
    } 
    else if (statusPerintah == '2') {
      Serial.println("Mode: LED BLINKING");
    }
  }

  // Logika menjalankan mode Blink tanpa menghentikan pembacaan serial
  if (statusPerintah == '2') {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState; // Balikkan status LED
      digitalWrite(PIN_LED, ledState);
    }
  }
}
```

#### **README.md**
```markdown
# Dokumentasi Modifikasi Modul 3

## Penjelasan Kode Per Baris
- `char statusPerintah`: Variabel global untuk mengingat mode terakhir (ON/OFF/Blink) agar sistem tetap berjalan pada mode tersebut.
- `if (Serial.available() > 0)`: Mengecek apakah ada input baru dari keyboard.
- `statusPerintah = Serial.read()`: Memperbarui mode berdasarkan input terbaru.
- `if (statusPerintah == '2')`: Jika mode aktif adalah '2', program menjalankan logika blinking.
- `millis()`: Digunakan agar Arduino tetap bisa membaca input Serial saat LED sedang dalam jeda kedip (Non-blocking).
```

---

### **4) Penentuan `delay()` atau `millis()`**

**Keputusan: Menggunakan `millis()`.** 

**Penjelasan dan Pengaruhnya:**
* **Jika menggunakan `delay()`:** Fungsi ini bersifat *blocking*. Artinya, Arduino akan "berhenti total" dan tidak melakukan aktivitas apa pun selama durasi delay. Jika LED sedang berkedip dengan `delay(1000)`, Arduino tidak akan bisa membaca Serial Monitor jika kamu mengetik '0' untuk mematikan LED sampai waktu delay tersebut selesai. Hal ini membuat sistem terasa tidak responsif.
* **Jika menggunakan `millis()`:** Fungsi ini bersifat *non-blocking*. Arduino hanya membandingkan waktu yang telah berlalu tanpa menghentikan jalannya program. Dengan `millis()`, Arduino bisa terus mengecek `Serial.available()` setiap milidetik, sehingga saat kamu berpindah dari mode '2' (blink) ke '0' (off), sistem akan langsung merespon tanpa menunggu satu siklus kedipan selesai.
