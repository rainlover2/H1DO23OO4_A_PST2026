
int timer = 100;           
// delay. Semakin tinggi angkanya, 

void setup() { 
// gunakan loop for untuk menginisialisasi setiap pin sebagai 
output: 
for (int ledPin = 6; ledPin < 10; ledPin++) { 
pinMode(ledPin, OUTPUT); 
} 
} 
void loop() { 
// looping dari pin rendah ke tinggi 
for (int ledPin = 6; ledPin < 10; ledPin++) { 
// hidupkan LED pin nya: 
digitalWrite(ledPin, HIGH); 
delay(timer); 
// matikan pin LED nya: 
digitalWrite(ledPin, LOW); 
} 
// looping dari pin yang tinggi ke yang rendah 
for (int ledPin = 10; ledPin >= 6; ledPin--) { 
// menghidupkan pin: 
digitalWrite(ledPin, HIGH); 
delay(timer); 
// mematikan pin: 
digitalWrite(ledPin, LOW); 
} 
}
