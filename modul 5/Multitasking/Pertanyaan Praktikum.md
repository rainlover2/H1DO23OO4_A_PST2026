
## 1. Mekanisme Berjalannya Task
Ketiga task tersebut sebenarnya berjalan secara **bergantian** (konkuren), namun karena perpindahan antar task terjadi sangat cepat, jadi terlihat seolah-olah berjalan secara bersamaan (simultan).

**Penjelasan Mekanisme:**
* **Kernel Scheduler:** FreeRTOS menggunakan sebuah penjadwal (*Kernel Scheduler*) yang bertugas mengatur alokasi waktu CPU untuk setiap task. 
* **Time Slicing:** Karena ketiga task Anda memiliki prioritas yang sama (yaitu **1**), penjadwal akan membagi waktu secara adil menggunakan metode *Round Robin*.
* **Blocked State:** Saat sebuah task memanggil fungsi `vTaskDelay()`, task tersebut akan masuk ke kondisi *Blocked* (berhenti sementara).Hal ini memberikan kesempatan kepada penjadwal untuk menjalankan task lain yang sedang menunggu giliran (kondisi *Ready*).
* **Konteks Real-Time:** Sistem ini memastikan pengolahan data dilakukan secara konsisten sesuai waktu yang dibutuhkan tanpa penundaan yang tidak terduga (*buffer*)].


---

## 2. Cara Menambahkan Task Keempat
Untuk menambahkan task keempat, Anda perlu mengikuti tiga langkah utama yang serupa dengan struktur task sebelumnya:

1.  **Deklarasi Prototype:** Tambahkan prototype fungsi di bagian atas program (sebelum `setup()`).
    * Contoh: `void TaskBlink3(void *pvParameters);`
2.  **Pembuatan Task di setup():** Gunakan fungsi `xTaskCreate()` di dalam fungsi `setup()` untuk mendaftarkan task baru ke dalam penjadwal.
    ```cpp
    xTaskCreate(TaskBlink3, "task4", 128, NULL, 1, NULL);
    ```
3.  **Implementasi Fungsi Task:** Buat definisi fungsi task tersebut di luar `setup()` dan `loop()` dengan menyertakan loop tak berujung `while(1)` agar task terus berjalan.

---

###  3. Program Modifikasi (RTOS dengan Kontrol Potensiometer)

```cpp
#include <Arduino_FreeRTOS.h>

int sharedDelay = 500;

void TaskPot(void *pvParameters);
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);

void setup() {
  Serial.begin(9600);

  // Membuat task untuk membaca nilai potensiometer
  xTaskCreate(TaskPot, "ReadPot", 128, NULL, 2, NULL); 

  // Membuat task untuk Blink LED 1 (Pin 8)
 xTaskCreate(TaskBlink1, "Blink1", 128, NULL, 1, NULL); 

  // Membuat task untuk Blink LED 2 (Pin 9)
  xTaskCreate(TaskBlink2, "Blink2", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
}

// Task untuk membaca input analog dari potensiometer
void TaskPot(void *pvParameters) {
  while (1) {
    int sensorValue = analogRead(A0);
    // Memetakan nilai 0-1023 menjadi delay 100ms - 1000ms
    sharedDelay = map(sensorValue, 0, 1023, 100, 1000);
    
    Serial.print("Delay saat ini: ");
    Serial.println(sharedDelay);
    
    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);
  while (1) {
    digitalWrite(8, HIGH);
    vTaskDelay(sharedDelay / portTICK_PERIOD_MS);
    digitalWrite(8, LOW);
    vTaskDelay(sharedDelay / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(9, OUTPUT);
  while (1) {
    digitalWrite(9, HIGH);
    // Kecepatan berbeda 
    vTaskDelay((sharedDelay / 2) / portTICK_PERIOD_MS);
    digitalWrite(9, LOW);
    vTaskDelay((sharedDelay / 2) / portTICK_PERIOD_MS);
  }
}
```


### Penjelasan Program

* **Variabel Global `sharedDelay`**: Bertindak sebagai "jembatan" data antar task. Nilai ini diupdate oleh `TaskPot` dan dibaca oleh `TaskBlink1` serta `TaskBlink2`.
* **Prioritas Task (`TaskPot`)**: Dalam program ini, `TaskPot` diberikan prioritas **2** (lebih tinggi dari task LED yang berprioritas 1). Hal ini memastikan pembacaan sensor menjadi prioritas utama sistem agar perubahan pada potensiometer langsung terasa efeknya (responsif).
* **Fungsi `map()`**: Digunakan untuk mengubah rentang pembacaan analog potensiometer (0 hingga 1023) menjadi rentang waktu milidetik yang diinginkan (misalnya 100ms hingga 1000ms).
* **Penggunaan `vTaskDelay()`**: Berbeda dengan `delay()` biasa pada Arduino yang menghentikan seluruh proses (blocking), `vTaskDelay()` menempatkan task ke dalam kondisi *Blocked*. Ini memberikan kesempatan bagi *Kernel Scheduler* untuk menjalankan task lain yang sedang menunggu (Ready).
* **Multitasking Konkuren**: Meskipun ada tiga task yang berjalan, program ini membuktikan prinsip kerja RTOS di mana sistem tetap konsisten dalam mengerjakan berbagai task aplikasi secara bersamaan tanpa penundaan yang merusak performa sistem.
