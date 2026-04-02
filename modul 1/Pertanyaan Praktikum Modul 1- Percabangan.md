
**1. Kapan program masuk ke blok if?**

Program akan masuk ke blok if (timeDelay <= 100) ketika nilai variabel timeDelay sudah mencapai 100 atau kurang.
Berdasarkan logika pengurangan di dalam else, ini terjadi setelah LED berkedip sebanyak 10 kali (dari 1000ms berkurang 100ms setiap siklusnya). Saat mencapai titik ini, program akan berhenti selama 3 detik lalu mengulang kecepatannya dari awal (1000ms).

**2. Kapan program masuk ke blok else?**

Program akan masuk ke blok else selama nilai timeDelay masih lebih besar dari 100.
Di dalam blok ini, durasi kedipan dikurangi sebesar 100ms (timeDelay -= 100). Inilah yang menyebabkan efek LED berkedip yang semakin lama semakin cepat.

**3. Apa fungsi perintah delay(timeDelay)?**

Fungsi delay(timeDelay) digunakan untuk menghentikan eksekusi program sementara selama durasi yang ditentukan dalam milidetik (ms).
Karena diletakkan setelah perintah HIGH, ia menahan LED agar tetap menyala.
Karena diletakkan setelah perintah LOW, ia menahan LED agar tetap mati.
Nilainya bersifat dinamis karena mengikuti variabel timeDelay.

**4. Modifikasi Kode: Lambat → Cepat → Sedang → Mati**

Untuk mengubah alurnya menjadi Lambat → Cepat → Sedang → Mati, kita tidak bisa hanya menggunakan satu variabel yang terus berkurang. Kita perlu menentukan urutan durasi secara spesifik.

```cpp
const int ledPin = 11; // Menentukan pin 11 sebagai jalur data untuk LED 

void setup() { 
  pinMode(ledPin, OUTPUT); // Mengatur pin 11 sebagai output listrik 
}

void loop() { 
  // --- TAHAP 1: LAMBAT (1000ms) --- 
  digitalWrite(ledPin, HIGH); // Nyalakan LED 
  delay(1000);                // Tahan selama 1 detik 
  digitalWrite(ledPin, LOW);  // Matikan LED 
  delay(1000);                // Tahan selama 1 detik

  // --- TAHAP 2: CEPAT (200ms) --- 
  digitalWrite(ledPin, HIGH); // Nyalakan LED 
  delay(200);                 // Tahan sebentar saja (cepat) 
  digitalWrite(ledPin, LOW);  // Matikan LED 
  delay(200);                 // Tahan sebentar saja

  // --- TAHAP 3: SEDANG (500ms) --- 
  digitalWrite(ledPin, HIGH); // Nyalakan LED 
  delay(500);                 // Tahan dengan kecepatan menengah 
  digitalWrite(ledPin, LOW);  // Matikan LED 
  delay(500);                 // Tahan dengan kecepatan menengah

  // --- TAHAP 4: MATI (Berhenti) --- 
  digitalWrite(ledPin, LOW);  // Pastikan LED mati 
  while(true) { 
    // Loop kosong yang mengunci program di sini selamanya 
    // sehingga LED tetap mati dan tidak mengulang ke atas (reset). 
  } 
}
```

*Penjelasan Baris Kode Modifikasi:*

digitalWrite(ledPin, HIGH/LOW): Perintah untuk mengirim sinyal voltase ke LED (HIGH = Nyala, LOW = Mati).
delay(1000) vs delay(200): Mengontrol persepsi kecepatan. Angka besar berarti kedipan lambat, angka kecil berarti kedipan cepat.
Urutan Penulisan: Karena fungsi loop() berjalan dari atas ke bawah, kita cukup menuliskan blok HIGH-LOW secara berurutan dengan nilai delay yang berbeda (1000 → 200 → 500).
while(true) {}: Ini adalah trik untuk membuat program "berhenti" tanpa mematikan Arduino. Program akan terjebak di dalam kurung kurawal ini selamanya, sehingga LED akan tetap dalam kondisi terakhirnya (Mati) dan tidak akan pernah kembali ke baris atas.
