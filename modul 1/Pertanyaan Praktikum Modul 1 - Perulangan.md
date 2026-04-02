**1.Rangkaian schematic 5 LED running**

<img width="1303" height="662" alt="skematika" src="https://github.com/user-attachments/assets/71bb299c-f9ec-495f-9e41-e16794f51d9f" />

**2. Bagaimana program membuat efek LED berjalan dari kiri ke kanan?**

<img width="442" height="159" alt="image" src="https://github.com/user-attachments/assets/10d12436-f8f7-4761-abd9-559f920dcdb0" />

Efek ini dihasilkan oleh Loop Induk: for (int ledPin = 2; ledPin < 7; ledPin++).
Inisialisasi (ledPin = 2): Program mulai dari pin terkecil (Pin 2). Berdasarkan gambar, ini adalah LED pertama di sisi kiri.
Kondisi (ledPin < 7): Program akan terus berjalan selama nomor pin di bawah 7 (yaitu pin 2, 3, 4, 5, dan 6).
Urutan Eksekusi: Program menyalakan LED (HIGH), menunggu sejenak (delay), lalu mematikannya (LOW).
Inkremen (ledPin++): Setelah satu LED selesai, nilai ledPin bertambah 1. Hal ini menyebabkan "nyala" lampu berpindah ke pin di sebelah kanannya secara berurutan.

**3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!**

<img width="508" height="180" alt="image" src="https://github.com/user-attachments/assets/ffa70c4b-f318-4a21-8006-2c2fdd94e1fd" />

Efek ini dihasilkan oleh Loop Anak: for (int ledPin = 7; ledPin >= 2; ledPin--).
Inisialisasi (ledPin = 7): Meskipun pin LED terakhir ada di angka 6, loop ini memulai perhitungan dari angka yang lebih besar.
Kondisi (ledPin >= 2): Program akan terus berjalan mundur hingga mencapai pin 2.
Dekremen (ledPin--): Berbeda dengan loop pertama, tanda -- berarti nilai pin dikurangi 1 di setiap putaran.
Arah Gerak: Karena angka pin berkurang (misal dari 6 ke 5, lalu ke 4, dan seterusnya), maka urutan lampu yang menyala akan bergerak mundur dari posisi paling kanan kembali ke arah kiri.

**4. Program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dengan perulangan**


```cpp
/*
  Program Flip-Flop Kelompok LED
  Membagi 6 LED menjadi 2 grup (Pin 2-4 dan Pin 5-7)
  yang menyala bergantian secara berkelompok.
*/

int timer = 1000; // Durasi jeda dalam milidetik (1 detik)

void setup() { 
  // Inisialisasi pin 2 sampai 7 sebagai OUTPUT menggunakan loop
  for (int ledPin = 2; ledPin <= 7; ledPin++) { 
    pinMode(ledPin, OUTPUT); 
  } 
} 

void loop() { 
  // --- FASE 1: GRUP KIRI NYALA, GRUP KANAN MATI ---
  
  // Menyalakan LED pada pin 2, 3, dan 4
  for (int ledPin = 2; ledPin <= 4; ledPin++) { 
    digitalWrite(ledPin, HIGH); 
  }
  
  // Mematikan LED pada pin 5, 6, dan 7
  for (int ledPin = 5; ledPin <= 7; ledPin++) { 
    digitalWrite(ledPin, LOW); 
  }
  
  delay(timer); // Menahan kondisi Fase 1 selama 1 detik
  
  // --- FASE 2: GRUP KIRI MATI, GRUP KANAN NYALA ---
  
  // Mematikan LED pada pin 2, 3, dan 4
  for (int ledPin = 2; ledPin <= 4; ledPin++) { 
    digitalWrite(ledPin, LOW); 
  }
  
  // Menyalakan LED pada pin 5, 6, dan 7
  for (int ledPin = 5; ledPin <= 7; ledPin++) { 
    digitalWrite(ledPin, HIGH); 
  }
  
  delay(timer); // Menahan kondisi Fase 2 selama 1 detik sebelum mengulang ke awal
}
```

**Penjelasan Alur Progran**

1. Inisialisasi (setup)

Pada bagian ini, program menyiapkan "jalur" untuk arus listrik.
Program menggunakan for loop untuk menyisir pin 2 sampai 7.
Setiap pin tersebut diatur sebagai OUTPUT. Artinya, Arduino siap mengirimkan tegangan listrik ke LED yang terhubung pada pin-pin tersebut.

2. Fase Pertama: Kiri Nyala, Kanan Mati
   
Ketika memasuki void loop(), program menjalankan instruksi berikut:
Grup Kiri (Pin 2, 3, 4): Diberi instruksi HIGH. Ketiga LED ini akan menyala secara bersamaan (karena proses komputasi sangat cepat, mata kita melihatnya menyala serentak).
Grup Kanan (Pin 5, 6, 7): Diberi instruksi LOW. Ketiga LED ini dipastikan dalam kondisi mati.
delay(timer): Program berhenti sejenak selama 1 detik (1000ms). Pada saat ini, kamu akan melihat 3 lampu kiri menyala terang dan 3 lampu kanan gelap.

3. Fase Kedua: Kiri Mati, Kanan Nyala
   
Setelah jeda 1 detik selesai, program berlanjut ke instruksi berikutnya yang merupakan kebalikan dari fase pertama:
Grup Kiri (Pin 2, 3, 4): Sekarang diberi instruksi LOW. Ketiga LED yang tadinya nyala langsung padam.
Grup Kanan (Pin 5, 6, 7): Sekarang diberi instruksi HIGH. Ketiga LED ini menyala serentak.
delay(timer): Program kembali berhenti sejenak selama 1 detik. Kamu akan melihat kondisi sebaliknya: sisi kiri gelap, sisi kanan menyala.

4. Pengulangan (Loop)
   
Karena kode ini berada di dalam fungsi loop(), setelah Fase Kedua selesai, program tidak berhenti. Ia akan meloncat kembali ke baris paling atas (Fase Pertama).

