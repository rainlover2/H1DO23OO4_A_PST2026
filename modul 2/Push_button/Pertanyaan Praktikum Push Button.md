
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

---
