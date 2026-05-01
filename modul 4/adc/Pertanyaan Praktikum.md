
## 1. Fungsi Perintah `analogRead()`
Dalam rangkaian ini, fungsi `analogRead(potensioPin)` bertugas untuk **membaca tegangan analog** yang masuk ke pin **A0** dari kaki tengah (wiper) potensiometer. 

*   **Proses ADC:** Arduino mengubah tegangan tersebut (rentang 0V hingga 5V) menjadi nilai digital dalam bentuk bilangan bulat (integer).
*   **Resolusi:** Karena Arduino Uno memiliki ADC 10-bit, maka nilai yang dihasilkan berkisar antara **0 hingga 1023**.
*   **Interpretasi:** Nilai ini merepresentasikan posisi fisik dari tuas potensiometer yang diputar oleh pengguna.

---

## 2. Mengapa Diperlukan Fungsi `map()`?
Fungsi `map()` sangat krusial karena adanya **perbedaan skala data** antara input (potensiometer) dan output (servo motor):

*   **Rentang Input:** Nilai dari `analogRead()` adalah **0 – 1023**.
*   **Rentang Output:** Perintah `myservo.write()` memerlukan parameter sudut dalam derajat, yaitu **0 – 180**.
*   **Sinkronisasi:** Tanpa fungsi `map()`, jika kita langsung memasukkan nilai 1023 ke servo, motor tidak akan bekerja dengan benar karena melebihi batas sudut maksimalnya. Fungsi ini secara matematis mengubah skala 0–1023 menjadi proporsional terhadap skala 0–180.

---

## 3. Modifikasi Program (Rentang 30° – 150°)

Berikut adalah potongan kode yang telah dimodifikasi pada bagian fungsi `map()`:

```cpp
// ===================== KONVERSI DATA MODIFIKASI =====================
// Mengubah nilai ADC (0-1023) menjadi rentang sudut terbatas (30-150)
pos = map(val, 0, 1023, 30, 150); 

// Hasilnya: 
// Jika val = 0, maka pos = 30
// Jika val = 1023, maka pos = 150
```
> **Penjelasan Program Modifikasi:**
> Program ini membatasi gerak mekanik motor servo agar tidak berputar penuh dari 0° ke 180°. Dengan mengubah parameter pada fungsi `map(val, 0, 1023, 30, 150)`, kita menetapkan "batas bawah" baru sebesar **30°** dan "batas atas" sebesar **150°**. 
> Hal ini berguna dalam aplikasi nyata di mana pergerakan engsel atau lengan robot memiliki pembatas fisik, sehingga servo tidak dipaksa menabrak pembatas tersebut meskipun potensiometer diputar maksimal.

