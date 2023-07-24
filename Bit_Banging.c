For NodeMCU:
// defining the SPI pins
#define MOSI D7
#define MISO D6
#define SCK D5
#define CS D4
void setup() {
 // initializing the GPIO pins
 pinMode(MOSI, OUTPUT);
 pinMode(MISO, INPUT);
 pinMode(SCK, OUTPUT);
 pinMode(CS, OUTPUT);
 // deselect the Uno board
 digitalWrite(CS, HIGH);
 // start the Serial communication
 Serial.begin(9600);
}
void loop() {
 // select the Uno board
 digitalWrite(CS, LOW);
 // send a string of characters
 char data [] = "Hello, Uno!";
 for (int i = 0; i < sizeof(data); i++) {
 digitalWrite(MOSI, data[i]);
 digitalWrite(SCK, HIGH);
 digitalWrite(SCK, LOW);
 }
 // read a response string
 char result[20];
 for (int i = 0; i < sizeof(result); i++) {
 digitalWrite(SCK, HIGH);
 result[i] = digitalRead(MISO);
 digitalWrite(SCK, LOW);
}
 // deselect the Uno board
 digitalWrite(CS, HIGH);
 // print the received string on Serial Monitor
 Serial.println(result);
 delay(1000);
}
For Arduino Uno:
#include <SPI.h>
// define the CS pin
#define CS 10
void setup() {
 // initialize the SPI pins
 pinMode(MOSI, OUTPUT);
 pinMode(MISO, INPUT);
 pinMode(SCK, OUTPUT);
 // initialize the CS pin
 pinMode(CS, OUTPUT);
 digitalWrite(CS, HIGH); // deselect the SPI device
 // initialize the SPI library
 SPI.begin();
 SPI.setDataMode(SPI_MODE0);
 SPI.setClockDivider(SPI_CLOCK_DIV8);
 // start the Serial communication
 Serial.begin(9600);
void loop() {
 // wait for a signal from NodeMCU
 while (digitalRead(CS) == HIGH);
 // read a string of characters
 char data[20];
 for (int i = 0; i < sizeof(data); i++) {
 data[i] = SPI.transfer(0);
 Serial.print(data[i]);
}
 // send a response string
 char result[] = "Hi, NodeMCU!";
 for (int i = 0; i < sizeof(result); i++) {
 SPI.transfer(result[i]);
 digitalWrite(SCK, HIGH);
 digitalWrite(SCK, LOW);
 }
 // deselect the SPI device
 digitalWrite(CS, HIGH);
 // print a new line on Serial Monitor
 Serial.println();
 delay(1000);
}