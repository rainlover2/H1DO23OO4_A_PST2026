

#### **1. Mekanisme Berjalannya Task**
Kedua task tersebut berjalan secara **bergantian** (*concurrent*). Karena mikrokontroler seperti Arduino Uno umumnya hanya memiliki satu inti prosesor (*single-core*), ia tidak dapat mengeksekusi dua instruksi secara bersamaan.

* **Mekanisme Penjadwalan:** *Kernel Scheduler* membagi waktu CPU untuk masing-masing task. Karena kedua task (`read_data` dan `display`) memiliki nilai prioritas yang sama, yaitu **0**, penjadwal akan menggunakan metode *Round Robin* untuk menggilir eksekusi keduanya.
* **Efisiensi dengan Delay:** Saat task `read_data` memanggil `vTaskDelay`, task tersebut masuk ke kondisi *Blocked* (berhenti sementara), sehingga penjadwal memberikan waktu CPU kepada task `display`.
* **Sinkronisasi Antrean:** Task `display` akan menunggu data di antrean menggunakan `xQueueReceive`. Jika antrean kosong, task ini akan diam (*blocked*) hingga `read_data` mengirimkan data baru melalui `xQueueSend`, memastikan sistem bekerja secara real-time tanpa penundaan yang tidak perlu.

#### **2. Potensi Race Condition**
Program ini **tidak berpotensi** mengalami *race condition* yang berbahaya.

* **Thread-Safety:** *Queue* pada FreeRTOS dirancang khusus untuk menangani komunikasi antar task secara aman.
* **Mekanisme Antrean:** Fungsi `xQueueSend` dan `xQueueReceive` sudah memiliki mekanisme penguncian internal (*atomic operations*). Saat satu task sedang menulis ke antrean, task lain tidak dapat mengganggu data tersebut sampai proses selesai, sehingga integritas data tetap terjaga meskipun task berjalan secara bergantian.

---

#### **3. Modifikasi Program dengan Sensor DHT**
Berikut adalah kode yang telah dimodifikasi untuk membaca data suhu dan kelembapan secara dinamis dari sensor DHT sesungguhnya.

```cpp
#include <Arduino_FreeRTOS.h> 
#include <queue.h> 
#include "DHT.h" 

#define DHTPIN 2    
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

struct readings { 
  int temp; 
  int h; 
}; 

QueueHandle_t my_queue; 
 
void setup() { 
  Serial.begin(9600);
  dht.begin(); // Inisialisasi sensor

  // Membuat antrean untuk menampung 1 struct readings
  my_queue = xQueueCreate(1, sizeof(struct readings)); 

  // Task membaca sensor dengan prioritas lebih tinggi agar data selalu terupdate
  xTaskCreate(read_data, "read sensors", 128, NULL, 1, NULL); 
  xTaskCreate(display, "display", 128, NULL, 1, NULL); 
} 
 
void loop() {} 
 
void read_data(void *pvParameters) { 
  struct readings x; 
  for(;;) { 
    // Membaca data dinamis dari sensor DHT
    x.temp = (int)dht.readTemperature(); 
    x.h = (int)dht.readHumidity(); 
    
    // Mengirim struct ke antrean
    xQueueSend(my_queue, &x, portMAX_DELAY); 
    
    vTaskDelay(2000 / portTICK_PERIOD_MS); 
  } 
} 
 
void display(void *pvParameters) { 
  struct readings x; 
  for(;;) { 
    // Menunggu data masuk ke antrean
    if(xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) { 
      Serial.println("--- Data Sensor Dinamis ---");
      Serial.print("Suhu      = "); 
      Serial.print(x.temp); 
      Serial.println(" C");
      Serial.print("Kelembapan = "); 
      Serial.print(x.h); 
      Serial.println(" %");
      Serial.println("---------------------------");
    } 
  } 
}
```

Program modifikasi untuk **Percobaan 5B** ini mengubah pengiriman data yang awalnya statis (angka tetap) menjadi data dinamis yang diambil langsung dari sensor suhu dan kelembapan (DHT).

Berikut adalah penjelasan detail mengenai alur dan komponen program tersebut:

### 1. Struktur Data (`struct`)
Program menggunakan `struct readings` sebagai paket data. Dibandingkan mengirim data satu per satu, `struct` memungkinkan kita membungkus variabel `temp` (suhu) dan `h` (kelembapan) ke dalam satu wadah agar dapat dikirimkan melalui antrean (*queue*) secara bersamaan.

### 2. Inisialisasi Queue (`xQueueCreate`)
Di dalam `setup()`, fungsi `my_queue = xQueueCreate(1, sizeof(struct readings))` membuahkan sebuah jalur komunikasi. 
* **Angka 1**: Berarti antrean ini hanya bisa menampung 1 paket data di satu waktu (kapasitas).
* **sizeof**: Menentukan ukuran memori yang dipesan sesuai dengan besar `struct` yang kita buat.

### 3. Task Produser (`read_data`)
Task ini berperan sebagai pengambil informasi.
* **Pembacaan Dinamis**: Fungsi `dht.readTemperature()` dan `dht.readHumidity()` mengambil data asli dari lingkungan.
* **xQueueSend**: Data yang sudah didapat "dikirim" ke dalam antrean.
* **vTaskDelay**: Menggunakan delay sebesar 2000ms (2 detik) karena sensor DHT memerlukan waktu untuk menstabilkan pembacaan sensor sebelum diambil kembali. Selama jeda ini, task masuk ke kondisi *Blocked* dan memberikan giliran pada task lain.



### 4. Task Konsumen (`display`)
Task ini bertugas menampilkan hasil ke pengguna.
* **xQueueReceive**: Task ini akan "berdiam diri" (menunggu) pada baris ini. Ia tidak akan memproses apapun sampai ada data yang masuk ke antrean dari task produser.
* **portMAX_DELAY**: Parameter ini menginstruksikan task untuk menunggu selamanya sampai data tersedia, sehingga tidak ada pemborosan siklus CPU.
* **pdPASS**: Jika data berhasil diterima, maka program akan mencetak hasilnya ke Serial Monitor secara rapi.

