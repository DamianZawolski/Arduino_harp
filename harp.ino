#include "thingProperties.h"
#include <SoftwareSerial.h>

#define PR_PIN 0

#define laser 2
#define sensor 3
#define sensor2 8
#define sensor3 9
#define sensor4 10
#define sensor5 11
#define button 12
#define LED 4
int buttonState = 0;  // variable for reading the pushbutton status
int song = 1;
int volume = 10;
SoftwareSerial mp3(5, 6);

static uint8_t cmdbuf[8] = {0};

void command(int8_t cmd, int16_t dat)
{
  delay(20);

  cmdbuf[0] = 0x7e; // bajt startu
  cmdbuf[1] = 0xFF; // wersja
  cmdbuf[2] = 0x06; // liczba bajtow polecenia
  cmdbuf[3] = cmd;  // polecenie
  cmdbuf[4] = 0x00; // 0x00 = no feedback, 0x01 = feedback
  cmdbuf[5] = (int8_t)(dat >> 8); // parametr DAT1
  cmdbuf[6] = (int8_t)(dat); //  parametr DAT2
  cmdbuf[7] = 0xef; // bajt konczacy

  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(cmdbuf[i]);
  }
}
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(laser, HIGH);

  //moduł MP3 YX5300
  Serial.begin(9600);
  mp3.begin(9600);

  delay(500); // Czekamy 500ms na inicjalizacje

  command(0x09, 0x0002); // Wybieramy karte SD jako zrodlo
  delay(200); // Czekamu 200ms na inicjalizacje

  command(0x06, 0x001E); // Ustaw glosnosc na 30
}

void loop() {
  ArduinoCloud.update();
  buttonState = digitalRead(button);
  bool value = digitalRead(sensor);
  bool value2 = digitalRead(sensor2);
  bool value3 = digitalRead(sensor3);
  bool value4 = digitalRead(sensor4);
  bool value5 = digitalRead(sensor5);
  int value_poten = analogRead(PR_PIN);
  int desired_volume = map(value_poten, 0, 1000, 0, 10);

  if (buttonState == LOW) {
    if (song > 4) {
      song = 1;
      delay(100);
    }
    else {
      song++;
      delay(100);
    }
    audio_set = song;
  }
  if (volume != desired_volume) {
    if (desired_volume == 0) {
      command(0x06, 0x0000); // Ustaw glosnosc na 0
    }
    else if (desired_volume == 1) {
      command(0x06, 0x0003); // Ustaw glosnosc na 3
    }
    else if (desired_volume == 2) {
      command(0x06, 0x0006); // Ustaw glosnosc na 6
    }
    else if (desired_volume == 3) {
      command(0x06, 0x0009); // Ustaw glosnosc na 9
    }
    else if (desired_volume == 4) {
      command(0x06, 0x000C); // Ustaw glosnosc na 12
    }
    else if (desired_volume == 5) {
      command(0x06, 0x000F); // Ustaw glosnosc na 15
    }
    else if (desired_volume == 6) {
      command(0x06, 0x0012); // Ustaw glosnosc na 18
    }
    else if (desired_volume == 7) {
      command(0x06, 0x0015); // Ustaw glosnosc na 21
    }
    else if (desired_volume == 8) {
      command(0x06, 0x0018); // Ustaw glosnosc na 24
    }
    else if (desired_volume == 9) {
      command(0x06, 0x001B); // Ustaw glosnosc na 27
    }
    else {
      command(0x06, 0x0001E); // Ustaw glosnosc na 30
    }

  }
  digitalWrite(LED, LOW);
  if (value == 0) {
    strings = "Gra struna numer 1";
    if (song == 1) {
      command(0x0F, 0x0101);
    }
    else if (song == 2) {
      command(0x0F, 0x0201);
    }
    else if (song == 3) {
      command(0x0F, 0x0301);
    }
    else if (song == 4) {
      command(0x0F, 0x0401);
    }
    else if (song == 5) {
      command(0x0F, 0x0501);
    }

    digitalWrite(LED, HIGH);

  }
  else if (value2 == 0) {
    strings = "Gra struna numer 2";
    if (song == 1) {
      command(0x0F, 0x0102);
    }
    else if (song == 2) {
      command(0x0F, 0x0202);
    }
    else if (song == 3) {
      command(0x0F, 0x0302);
    }
    else if (song == 4) {
      command(0x0F, 0x0402);
    }
    else if (song == 5) {
      command(0x0F, 0x0502);
    }

    digitalWrite(LED, HIGH);

  }
  else if (value3 == 0) {
    strings = "Gra struna numer 3";
    if (song == 1) {
      command(0x0F, 0x0103);
    }
    else if (song == 2) {
      command(0x0F, 0x0203);
    }
    else if (song == 3) {
      command(0x0F, 0x0303);
    }
    else if (song == 4) {
      command(0x0F, 0x0403);
    }
    else if (song == 5) {
      command(0x0F, 0x0503);
    }

    digitalWrite(LED, HIGH);

  }
  else if (value4 == 0) {
    strings = "Gra struna numer 4";
    if (song == 1) {
      command(0x0F, 0x0104);
    }
    else if (song == 2) {
      command(0x0F, 0x0204);
    }
    else if (song == 3) {
      command(0x0F, 0x0304);
    }
    else if (song == 4) {
      command(0x0F, 0x0404);
    }
    else if (song == 5) {
      command(0x0F, 0x0504);
    }

    digitalWrite(LED, HIGH);

  }
  else if (value5 == 0) {
    strings = "Gra struna numer 5";
    if (song == 1) {
      command(0x0F, 0x0105);
    }
    else if (song == 2) {
      command(0x0F, 0x0205);
    }
    else if (song == 3) {
      command(0x0F, 0x0305);
    }
    else if (song == 4) {
      command(0x0F, 0x0405);
    }
    else if (song == 5) {
      command(0x0F, 0x0505);
    }

    digitalWrite(LED, HIGH);

  }
  delay(100);
  Serial.print("Potentiometer value: ");
  Serial.println(value_poten);
  Serial.print("Volume: ");
  Serial.println(desired_volume);
  Serial.print("Audio set: ");
  Serial.println(song);
  Serial.print("Lasers (1:");
  Serial.print(value);
  Serial.print(" 2:");
  Serial.print(value2);
  Serial.print(" 3:");
  Serial.print(value3);
  Serial.print(" 4:");
  Serial.print(value4);
  Serial.print(" 5:");
  Serial.print(value5);
  Serial.println(")");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  volume2 = desired_volume;
}
