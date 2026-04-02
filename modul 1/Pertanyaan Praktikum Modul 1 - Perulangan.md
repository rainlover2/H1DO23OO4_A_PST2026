**1.Rangkaian schematic 5 LED running**

<img width="1303" height="662" alt="skematika" src="https://github.com/user-attachments/assets/71bb299c-f9ec-495f-9e41-e16794f51d9f" />

**2. Bagaimana program membuat efek LED berjalan dari kiri ke kanan?**

<img width="442" height="159" alt="image" src="https://github.com/user-attachments/assets/10d12436-f8f7-4761-abd9-559f920dcdb0" />

Efek ini dihasilkan oleh Loop Induk: for (int ledPin = 2; ledPin < 7; ledPin++).

Inisialisasi (ledPin = 2): Program mulai dari pin terkecil (Pin 2). Berdasarkan gambar, ini adalah LED pertama di sisi kiri.

Kondisi (ledPin < 7): Program akan terus berjalan selama nomor pin di bawah 7 (yaitu pin 2, 3, 4, 5, dan 6).

Urutan Eksekusi: Program menyalakan LED (HIGH), menunggu sejenak (delay), lalu mematikannya (LOW).

Inkremen (ledPin++): Setelah satu LED selesai, nilai ledPin bertambah 1. Hal ini menyebabkan "nyala" lampu berpindah ke pin di sebelah kanannya secara berurutan.
