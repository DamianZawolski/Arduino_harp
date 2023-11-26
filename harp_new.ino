#include "thingProperties.h"
#include <SoftwareSerial.h>

#define potencjometr_glosnosc 0
#define potencjometr_tonacja 1
#define sensor 0
#define sensor2 1
#define sensor3 2
#define sensor4 3
#define sensor5 4
#define sensor6 5
#define sensor7 6
#define sensor8 7
#define laser 8
#define button 11
SoftwareSerial mp3(9, 10);

int wcisniecie_przycisku = 0;
int glosnosc = 10;


static uint8_t komunikat_sterujacy_yx5300[8] = {0};

void komenda_MP3(int8_t polecenie, int16_t wartosc)
{
  delay(20);
  komunikat_sterujacy_yx5300[0] = 0x7e;
  komunikat_sterujacy_yx5300[1] = 0xFF;
  komunikat_sterujacy_yx5300[2] = 0x06;
  komunikat_sterujacy_yx5300[3] = polecenie;
  komunikat_sterujacy_yx5300[4] = 0x00;
  komunikat_sterujacy_yx5300[5] = (int8_t)(wartosc >> 8);
  komunikat_sterujacy_yx5300[6] = (int8_t)(wartosc);
  komunikat_sterujacy_yx5300[7] = 0xef;
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(komunikat_sterujacy_yx5300[i]);
  }
}

void setup() {
  Serial.begin(9600);
  delay(1500);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
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
  digitalWrite(laser, HIGH);
  wybrany_instrument = 1;

  Serial.begin(9600);
  mp3.begin(9600);
  delay(500);
  komenda_MP3(0x09, 0x0002); // Karte SD jako zrodlo
  delay(200);
  komenda_MP3(0x06, 0x001E); // Ustaw głośność na 30
}

void loop() {
  ArduinoCloud.update();
  wcisniecie_przycisku = digitalRead(button);
  bool wartosc_lasera_1 = digitalRead(sensor);
  bool wartosc_lasera_2 = digitalRead(sensor2);
  bool wartosc_lasera_3 = digitalRead(sensor3);
  bool wartosc_lasera_4 = digitalRead(sensor4);
  bool wartosc_lasera_5 = digitalRead(sensor5);
  bool wartosc_lasera_6 = digitalRead(sensor6);
  bool wartosc_lasera_7 = digitalRead(sensor7);
  bool wartosc_lasera_8 = digitalRead(sensor8);
  int wartosc_potencjometr_glosnosc = analogRead(potencjometr_glosnosc);
  int wartosc_potencjometr_tonacja = analogRead(potencjometr_tonacja);
  wybrana_glosnosc = map(wartosc_potencjometr_glosnosc, 0, 1000, 0, 10);
  wybrana_tonacja = map(wartosc_potencjometr_tonacja, 0, 1000, 0, 4);
  int wybrana_struna;
  if (wcisniecie_przycisku == LOW) {
    if (wybrany_instrument > 3) {
      wybrany_instrument = 1;
    }
    else {
      wybrany_instrument++;
    }
    delay(100);
  }
  if (glosnosc != wybrana_glosnosc) {
    if (wybrana_glosnosc == 0) {
      komenda_MP3(0x06, 0x0000); // Ustaw głośność na 0
    }
    else if (wybrana_glosnosc == 1) {
      komenda_MP3(0x06, 0x0003); // Ustaw głośność na 3
    }
    else if (wybrana_glosnosc == 2) {
      komenda_MP3(0x06, 0x0006); // Ustaw głośność na 6
    }
    else if (wybrana_glosnosc == 3) {
      komenda_MP3(0x06, 0x0009); // Ustaw głośność na 9
    }
    else if (wybrana_glosnosc == 4) {
      komenda_MP3(0x06, 0x000C); // Ustaw głośność na 12
    }
    else if (wybrana_glosnosc == 5) {
      komenda_MP3(0x06, 0x000F); // Ustaw głośność na 15
    }
    else if (wybrana_glosnosc == 6) {
      komenda_MP3(0x06, 0x0012); // Ustaw głośność na 18
    }
    else if (wybrana_glosnosc == 7) {
      komenda_MP3(0x06, 0x0015); // Ustaw głośność na 21
    }
    else if (wybrana_glosnosc == 8) {
      komenda_MP3(0x06, 0x0018); // Ustaw głośność na 24
    }
    else if (wybrana_glosnosc == 9) {
      komenda_MP3(0x06, 0x001B); // Ustaw głośność na 27
    }
    else {
      komenda_MP3(0x06, 0x0001E); // Ustaw głośność na 30
    }
    glosnosc = wybrana_glosnosc;
  }
  //wybór struny
  if (wartosc_lasera_1 == 0) {
      wybrana_struna = 1;
    }
  else if (wartosc_lasera_2 == 0) {
      wybrana_struna = 2;
    }
  else if (wartosc_lasera_3 == 0) {
      wybrana_struna = 3;
    }
  else if (wartosc_lasera_4 == 0) {
      wybrana_struna = 4;
    }
  else if (wartosc_lasera_5 == 0) {
      wybrana_struna = 5;
    }
  else if (wartosc_lasera_6 == 0) {
      wybrana_struna = 6;
    }
  else if (wartosc_lasera_7 == 0) {
      wybrana_struna = 7;
    }
  else if (wartosc_lasera_8 == 0) {
      wybrana_struna = 8;
    }
  
  //harfa
  if (wybrany_instrument == 0){
    if (wybrana_struna + wybrana_tonacja == 1)
    {
      komenda_MP3(0x0F, 0x0101);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa C2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 2)
    {
      komenda_MP3(0x0F, 0x0102);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa F2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 3)
    {
      komenda_MP3(0x0F, 0x0103);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa B2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 4)
    {
      komenda_MP3(0x0F, 0x0104);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa E3)";
    }
    else if (wybrana_struna + wybrana_tonacja == 5)
    {
      komenda_MP3(0x0F, 0x0105);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa A3)";
    }
    else if (wybrana_struna + wybrana_tonacja == 6)
    {
      komenda_MP3(0x0F, 0x0106);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa D4)";
    }
    else if (wybrana_struna + wybrana_tonacja == 7)
    {
      komenda_MP3(0x0F, 0x0107);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa G4)";
    }
    else if (wybrana_struna + wybrana_tonacja == 8)
    {
      komenda_MP3(0x0F, 0x0108);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa C5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 9)
    {
      komenda_MP3(0x0F, 0x0109);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa F5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 10)
    {
      komenda_MP3(0x0F, 0x010A);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa B5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 11)
    {
      komenda_MP3(0x0F, 0x010B);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa E6)";
    }
    else if (wybrana_struna + wybrana_tonacja == 12)
    {
      komenda_MP3(0x0F, 0x010C);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(harfa A6)";
    }
  }
  //fortepian
  else if (wybrany_instrument == 1){
    if (wybrana_struna + wybrana_tonacja == 1)
    {
      komenda_MP3(0x0F, 0x0201);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian C2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 2)
    {
      komenda_MP3(0x0F, 0x0202);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian F2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 3)
    {
      komenda_MP3(0x0F, 0x0203);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian B2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 4)
    {
      komenda_MP3(0x0F, 0x0204);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian E3)";
    }
    else if (wybrana_struna + wybrana_tonacja == 5)
    {
      komenda_MP3(0x0F, 0x0205);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian A3)";
    }
    else if (wybrana_struna + wybrana_tonacja == 6)
    {
      komenda_MP3(0x0F, 0x0206);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian D4)";
    }
    else if (wybrana_struna + wybrana_tonacja == 7)
    {
      komenda_MP3(0x0F, 0x0207);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian G4)";
    }
    else if (wybrana_struna + wybrana_tonacja == 8)
    {
      komenda_MP3(0x0F, 0x0208);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian C5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 9)
    {
      komenda_MP3(0x0F, 0x0209);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian F5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 10)
    {
      komenda_MP3(0x0F, 0x020A);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian B5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 11)
    {
      komenda_MP3(0x0F, 0x020B);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian E6)";
    }
    else if (wybrana_struna + wybrana_tonacja == 12)
    {
      komenda_MP3(0x0F, 0x020C);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(fortepian A6)";
    }
  }
  //perkusja
  else if (wybrany_instrument == 2){
    if (wybrana_struna + wybrana_tonacja == 1)
    {
      komenda_MP3(0x0F, 0x0301);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja G3 bęben basowy)";
    }
    else if (wybrana_struna + wybrana_tonacja == 2)
    {
      komenda_MP3(0x0F, 0x0302);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja A3 werbel)";
    }
    else if (wybrana_struna + wybrana_tonacja == 3)
    {
      komenda_MP3(0x0F, 0x0303);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja B3 werbel (cross stick))";
    }
    else if (wybrana_struna + wybrana_tonacja == 4)
    {
      komenda_MP3(0x0F, 0x0304); 
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja C4 hi-hat (zamknięty))";
    }
    else if (wybrana_struna + wybrana_tonacja == 5)
    {
      komenda_MP3(0x0F, 0x0305);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja D4 hi-hat (otwarty))";
    }
    else if (wybrana_struna + wybrana_tonacja == 6)
    {
      komenda_MP3(0x0F, 0x0306);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja F4 wysoki tom-tom)";
    }
    else if (wybrana_struna + wybrana_tonacja == 7)
    {
      komenda_MP3(0x0F, 0x0307);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja A4 floor tom)";
    }
    else if (wybrana_struna + wybrana_tonacja == 8)
    {
      komenda_MP3(0x0F, 0x0308);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja B4 talerz)";
    }
    else if (wybrana_struna + wybrana_tonacja == 9)
    {
      komenda_MP3(0x0F, 0x0309);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja C5 talerz crash)";
    }
    else if (wybrana_struna + wybrana_tonacja == 10)
    {
      komenda_MP3(0x0F, 0x030A);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja E5 Hi hat)";
    }
    else if (wybrana_struna + wybrana_tonacja == 11)
    {
      komenda_MP3(0x0F, 0x030B);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja F5 Hi hat)";
    }
    else if (wybrana_struna + wybrana_tonacja == 12)
    {
      komenda_MP3(0x0F, 0x030C);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(perkusja A5 bell)";
    }
  }
  //gitara
  else if (wybrany_instrument == 3){
    if (wybrana_struna + wybrana_tonacja == 1)
    {
      komenda_MP3(0x0F, 0x0401);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara C2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 2)
    {
      komenda_MP3(0x0F, 0x0402);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara F2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 3)
    {
      komenda_MP3(0x0F, 0x0403);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara B2)";
    }
    else if (wybrana_struna + wybrana_tonacja == 4)
    {
      komenda_MP3(0x0F, 0x0404);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara E3)";
    }
    else if (wybrana_struna + wybrana_tonacja == 5)
    {
      komenda_MP3(0x0F, 0x0405);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara A3)";
    }
    else if (wybrana_struna + wybrana_tonacja == 6)
    {
      komenda_MP3(0x0F, 0x0406);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara D4)";
    }
    else if (wybrana_struna + wybrana_tonacja == 7)
    {
      komenda_MP3(0x0F, 0x0407);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara G4)";
    }
    else if (wybrana_struna + wybrana_tonacja == 8)
    {
      komenda_MP3(0x0F, 0x0408);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara C5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 9)
    {
      komenda_MP3(0x0F, 0x0409);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara F5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 10)
    {
      komenda_MP3(0x0F, 0x040A);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara B5)";
    }
    else if (wybrana_struna + wybrana_tonacja == 11)
    {
      komenda_MP3(0x0F, 0x040B);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara E6)";
    }
    else if (wybrana_struna + wybrana_tonacja == 12)
    {
      komenda_MP3(0x0F, 0x040C);
      tekst_IOT = "Gra struna numer " + String(wybrana_struna) +"(gitara A6)";
    }
  }

  delay(100);
  Serial.print("Wartość potencjometr_glosnosc: ");
  Serial.println(wartosc_potencjometr_glosnosc);
  Serial.print("Wartość potencjometr_tonacja: ");
  Serial.println(wartosc_potencjometr_tonacja);
  Serial.print("Głośność: ");
  Serial.println(wybrana_glosnosc);
  Serial.print("Wybrany instrument: ");
  Serial.print(wybrany_instrument);
  if (wybrany_instrument == 0){
    Serial.println("- harfa");
  }
  else if (wybrany_instrument == 1){
    Serial.println("- fortepian");
  }
  else if (wybrany_instrument == 2){
    Serial.println("- perkusja");
  }
  else if (wybrany_instrument == 3){
    Serial.println("- gitara");
  }
  Serial.print("Tonacja: ");
  Serial.println(wybrana_tonacja);
  Serial.print("Lasery (1:");
  Serial.print(wartosc_lasera_1);
  Serial.print(" 2:");
  Serial.print(wartosc_lasera_2);
  Serial.print(" 3:");
  Serial.print(wartosc_lasera_3);
  Serial.print(" 4:");
  Serial.print(wartosc_lasera_4);
  Serial.print(" 5:");
  Serial.print(wartosc_lasera_5);
  Serial.print(" 6:");
  Serial.print(wartosc_lasera_6);
  Serial.print(" 7:");
  Serial.print(wartosc_lasera_7);
  Serial.print(" 8:");
  Serial.print(wartosc_lasera_8);
  Serial.println(")");
  Serial.println("");
  Serial.println("");
  Serial.println("");
}
