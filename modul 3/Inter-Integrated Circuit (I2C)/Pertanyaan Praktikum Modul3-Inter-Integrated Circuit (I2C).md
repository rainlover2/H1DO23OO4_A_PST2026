
### **1. Cara Kerja Komunikasi I2C antara Arduino dan LCD**
Komunikasi I2C (Inter-Integrated Circuit) pada rangkaian ini bekerja dengan prinsip **Master-Slave**.
* **Peran Perangkat:** Arduino Uno bertindak sebagai **Master** (supir bus) yang mengendalikan aliran data, sedangkan LCD I2C bertindak sebagai **Slave** (penumpang) yang menerima instruksi.
* **Jalur Kabel:** Komunikasi hanya membutuhkan dua kabel data, yaitu **SDA** (Serial Data) untuk mengirim bit data dan **SCL** (Serial Clock) untuk menyelaraskan waktu pengiriman data.
* **Alamat I2C:** Agar data sampai ke perangkat yang benar, Arduino menggunakan alamat unik (pada kode Anda adalah `0x27`). Ini seperti nomor kursi yang memastikan hanya LCD yang merespons instruksi tersebut.


---

### **2. Analisis Pin Potensiometer**
Pin potensiometer pada dasarnya berfungsi sebagai pembagi tegangan (*voltage divider*).
* **Apakah harus seperti itu?** Secara teknis, kaki tengah (wiper) **wajib** dihubungkan ke pin Analog (A0) untuk membaca perubahan tegangan. Namun, posisi kaki kiri dan kanan bisa diubah.
* **Jika pin kiri (GND) dan kanan (5V) tertukar:** Rangkaian tetap aman dan tidak akan rusak. Namun, **logika pembacaannya akan terbalik**. Jika awalnya memutar ke kanan (searah jarum jam) membuat nilai ADC bertambah besar (0 ke 1023), maka setelah ditukar, memutar ke kanan justru akan membuat nilai ADC mengecil (1023 ke 0).

---

### **3. Modifikasi Program (UART & I2C)**

Berikut adalah kode yang telah dimodifikasi untuk menampilkan data pada Serial Monitor dan LCD sesuai permintaan:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilaiADC = analogRead(pinPot);
  
  // Kalkulasi Volt dan Persen
  float volt = (nilaiADC / 1023.0) * 5.0;
  int persen = map(nilaiADC, 0, 1023, 0, 100);
  int panjangBar = map(nilaiADC, 0, 1023, 0, 16);

  // --- Output Serial Monitor ---
  Serial.print("ADC: "); Serial.print(nilaiADC);
  Serial.print("  Volt: "); Serial.print(volt); Serial.print(" V");
  Serial.print("  Persen: "); Serial.print(persen); Serial.println("%");

  // --- Output LCD Baris 1 ---
  lcd.setCursor(0, 0);
  lcd.print("ADC:"); lcd.print(nilaiADC);
  lcd.print(" "); lcd.print(persen); lcd.print("%   "); // Spasi untuk clear sisa

  // --- Output LCD Baris 2 (Progress Bar) ---
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255); // Karakter blok
    } else {
      lcd.print(" "); // Spasi kosong
    }
  }

  delay(200);
}
```

#### **(Penjelasan Kode)**
* `float volt = (nilaiADC / 1023.0) * 5.0;`: Menghitung nilai tegangan nyata dengan membagi nilai ADC terhadap resolusi 10-bit (1023) dikali tegangan referensi (5V).
* `map(nilaiADC, 0, 1023, 0, 100);`: Mengubah rentang pembacaan sensor (0-1023) menjadi skala persentase (0-100).
* `lcd.setCursor(0, 0)` & `(0, 1)`: Menentukan posisi awal penulisan teks pada baris pertama dan kedua LCD.
* `lcd.print("    ")`: Penambahan spasi di akhir teks bertujuan untuk menghapus karakter lama yang tersisa saat nilai angka mengecil.

---

### **4. Tabel Hasil Pengamatan**
Berdasarkan rumus perhitungan $Volt = \frac{ADC}{1023} \times 5$ dan $Persen = \frac{ADC}{1023} \times 100$:

| ADC | Volt (V) | Persen (%) |
| :--- | :--- | :--- |
| **1** | 0.005 V | 0.1 % |
| **21** | 0.10 V | 2.0 % |
| **49** | 0.24 V | 4.8 % |
| **74** | 0.36 V | 7.2 % |
| **96** | 0.47 V | 9.4 % |

