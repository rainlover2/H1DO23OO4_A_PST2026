

## **1. Keuntungan dan Kerugian UART dan I2C**

Pemilihan protokol komunikasi sangat bergantung pada kebutuhan sistem, apakah mengutamakan kesederhanaan atau efisiensi jumlah kabel untuk banyak perangkat.

### **Universal Asynchronous Receiver-Transmitter (UART)**
* **Keuntungan:**
    * **Sederhana dan Murah:** Protokol ini sangat klasik, mudah diimplementasikan, dan tidak memerlukan biaya tinggi].
    * **Tanpa Sinyal Clock:** Bekerja secara asinkron, sehingga tidak membutuhkan kabel tambahan untuk sinyal detak (*clock*) bersama.
    * **Pengaturan Fleksibel:** Kecepatan transmisi (*baud rate*) dan format data dapat diatur sesuai kebutuhan.
* **Kerugian:**
    * **Terbatas pada Dua Perangkat:** Umumnya digunakan untuk komunikasi titik-ke-titik (*point-to-point*), berbeda dengan komunikasi paralel yang bisa mengirim banyak bit sekaligus.
    * **Sensitif terhadap Kecepatan:** Perangkat pengirim dan penerima **wajib** memiliki *baud rate* yang sama persis agar data tidak korup.



### **Inter-Integrated Circuit (I2C)**
* **Keuntungan:**
    * **Hemat Kabel:** Mampu menghubungkan banyak perangkat (sensor, layar, dll.) hanya dengan dua kabel saja: SDA dan SCL.
    * **Sistem Pengalamatan:** Setiap perangkat memiliki alamat unik, sehingga Master (Arduino) bisa berkomunikasi dengan Slave tertentu tanpa gangguan dari perangkat lain di jalur yang sama.
* **Kerugian:**
    * **Risiko Konflik Alamat:** Jika dua modul memiliki alamat yang sama (misalnya banyak modul menggunakan 0x68), akan terjadi bentrokan data pada bus.
    * **Kecepatan Terbatas:** Biasanya digunakan untuk perangkat berkecepatan rendah dibandingkan protokol lain seperti SPI.



---

## **2. Peran Alamat I2C pada LCD (0x27 vs 0x20)**

Alamat I2C berfungsi sebagai **"Nomor Kursi"** unik bagi setiap perangkat yang terhubung pada jalur kabel yang sama. Tanpa alamat ini, Arduino tidak akan tahu ke mana data harus dikirimkan.

* **Alamat 0x27:** Biasanya digunakan oleh modul LCD yang menggunakan chip *backpack* buatan **NXP**.
* **Alamat 0x20:** Biasanya digunakan oleh chip **PCF8574** atau *I/O Expander* tertentu untuk menambah jumlah pin digital.
* **Signifikansi:** Perbedaan alamat ini terjadi karena pabrikan yang berbeda menggunakan *hardwired address* yang berbeda pada modulnya. Jika Anda menggunakan alamat yang salah dalam kode program (`LiquidCrystal_I2C lcd(0x27, 16, 2)`), maka LCD tidak akan merespons perintah meskipun kabel sudah terpasang dengan benar.

---

## **3. Alur Kerja Penggabungan UART dan I2C**

Saat UART dan I2C digabungkan dalam satu sistem (misalnya: mengetik perintah di komputer untuk ditampilkan di LCD), Arduino bertindak sebagai jembatan komunikasi.

### **Alur Kerja Sistem:**
1.  **Input (UART):** Pengguna mengirim data melalui Serial Monitor pada komputer. Data ini masuk ke Arduino melalui kabel USB/pin RX dalam bentuk bit serial.
2.  **Pemrosesan (Arduino):** Arduino mengecek ketersediaan data di buffer serial menggunakan `Serial.available()`. Setelah data dibaca dengan `Serial.read()`, program akan memproses karakter tersebut.
3.  **Output (I2C):** Arduino kemudian mengirimkan instruksi tersebut ke LCD melalui jalur bus I2C (pin A4 dan A5 pada Uno). Arduino berperan sebagai "Supir Bus" (Master) yang memanggil "Penumpang" (Slave) dengan alamat tertentu agar data ditampilkan di layar.

### **Bagaimana Arduino Mengelola Keduanya?**
Arduino mengelola kedua protokol ini secara **sekuensial** (berurutan) di dalam fungsi `loop()`.
* Arduino tidak menjalankan keduanya benar-benar di saat yang bersamaan, melainkan berpindah tugas dengan sangat cepat.
* Protokol UART dikelola oleh *hardware* internal UART melalui objek `Serial`.
* Protokol I2C dikelola oleh *library* `Wire.h` yang mengatur pengaturan waktu sinyal pada pin SDA/SCL.
* Karena prosesor bekerja dalam kecepatan MHz, jeda antara membaca Serial (UART) dan mengirim ke LCD (I2C) tidak akan terasa oleh pengguna manusia.

