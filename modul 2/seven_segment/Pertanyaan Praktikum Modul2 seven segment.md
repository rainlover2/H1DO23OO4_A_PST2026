Berikut adalah jawaban untuk pertanyaan praktikum pada Modul 2 berdasarkan data yang terdapat dalam dokumen tersebut.

---

## **Jawaban Pertanyaan Praktikum 2.5.4 (Seven Segment)**

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**


**2. Apa yang terjadi jika nilai num lebih dari 15?**

Jika variabel `num` melebihi 15, program akan mencoba mengakses indeks di luar batas array `digitPattern[16][8]` yang didefinisikan[cite: 153]. [cite_start]Hal ini akan menyebabkan program membaca data "sampah" dari memori mikrokontroler, sehingga tampilan pada *Seven Segment* akan menjadi acak, tidak terdefinisi, atau menunjukkan pola yang salah.

**3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!**

Program ini menggunakan **Common Cathode (CC)**. Alasannya terlihat pada pola data `digitPattern`, di mana nilai **1** digunakan untuk menyalakan segmen dan **0** untuk mematikan. Misalnya, untuk menampilkan angka '0', segmen a sampai f diberikan logika **1** agar menyala.

**4. Modifikasi program agar tampilan berjalan dari F ke 0.**

Untuk membalik urutan, Anda hanya perlu mengubah parameter pada perulangan `for` di dalam fungsi `loop()`:
```cpp
void loop() {
  for(int i = 15; i >= 0; i--) { // Dimulai dari 15 (F) turun ke 0
    displayDigit(i);
    delay(1000);
  }
}
```

---
