
### 1. Mengapa kecerahan LED dapat diatur dengan `analogWrite()`?
LED dapat diatur kecerahannya karena fungsi `analogWrite()` menerapkan teknik **Pulse Width Modulation (PWM)**. 

*   **Sinyal Analog Semu**: Pin digital Arduino sebenarnya hanya bisa mengeluarkan tegangan 0V (LOW) atau 5V (HIGH). PWM memanipulasi ini dengan menyalakan dan mematikan aliran listrik dengan sangat cepat (frekuensi tinggi).
*   **Duty Cycle**: Kecerahan LED bergantung pada *duty cycle*, yaitu persentase waktu sinyal berada dalam kondisi HIGH dalam satu periode gelombang.
*   **Persepsi Mata**: Jika *duty cycle* tinggi (misal 90%), LED menyala lebih lama daripada matinya, sehingga terlihat terang. Jika *duty cycle* rendah (misal 10%), LED mati lebih lama, sehingga terlihat redup. Mata manusia merata-ratakan pulsa cepat ini sebagai tingkat kecerahan yang stabil.



### 2. Hubungan antara Nilai ADC (0–1023) dan Nilai PWM (0–255)
Hubungan keduanya terletak pada perbedaan resolusi bit antara input analog dan output PWM pada Arduino Uno:

*   **Resolusi ADC (10-bit)**: Pin `A0` membaca tegangan analog dan mengubahnya menjadi angka digital dari $0$ hingga $1023$ ($2^{10}$ tingkatan).
*   **Resolusi PWM (8-bit)**: Fungsi `analogWrite()` hanya menerima parameter dari $0$ hingga $255$ ($2^8$ tingkatan).
*   **Rasio Pemetaan**: Perbandingannya adalah **4:1**. Nilai ADC adalah empat kali lipat dari nilai PWM ($1024 / 256 = 4$). Oleh karena itu, fungsi `map(nilaiADC, 0, 1023, 0, 255)` digunakan untuk menskalakan nilai input yang besar agar pas dengan kapasitas input output PWM.

### 3. Modifikasi Program (Rentang PWM 50–200)
Untuk membatasi kecerahan LED agar hanya berada pada rentang sedang (50 hingga 200), Anda cukup mengubah parameter pada fungsi `map()`. Berikut adalah potongan kode yang dimodifikasi:

```cpp
void loop() {
  // Membaca nilai dari potensiometer (0-1023)
  nilaiADC = analogRead(potPin);

  // MODIFIKASI: Membatasi output PWM hanya dari 50 sampai 200
  // Meskipun potensio diputar habis (0 atau 1023), LED tidak akan mati total 
  // atau mencapai terang maksimal (hanya di rentang sedang).
  pwm = map(nilaiADC, 0, 1023, 50, 200);

  // Mengeluarkan sinyal PWM ke LED
  analogWrite(ledPin, pwm);

  // Monitoring data ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM Terbatas: ");
  Serial.println(pwm);

  delay(50);
}
```

**Penjelasan Modifikasi:**
Dengan mengubah parameter tujuan menjadi `50, 200`, maka saat potensiometer berada di posisi minimum (ADC 0), LED akan langsung menyala dengan kekuatan PWM 50. Begitu pula saat potensiometer di posisi maksimal (ADC 1023), LED hanya akan mencapai tingkat terang PWM 200, bukan 255. Hal ini memastikan LED selalu berada dalam rentang kecerahan sedang.
