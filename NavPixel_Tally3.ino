
//************************************************************
// Written by Nava Tabkum
// 10/01/2018 Version 3.0
// 1. Read GPIO and conver to NeoPixel stream
// 2. Use Blynk App to configure settings 
// 3. Fail-safe to run as stand alone without internet/ with EEprom backup 
//
//************************************************************

// #define BLYNK_TIMEOUT_MS  750  // BEFORE BlynkSimpleEsp8266.h 
// #define BLYNK_HEARTBEAT   15
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <EEPROM.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
// #include <ESP8266WiFiMulti.h>
#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"
// ESP8266WiFiMulti wMulti;

char ssid[] = "your ssid";
char pass[] = "your pass";
char auth[] = "your auth";
char server[] = "xxxxx.xxx";
unsigned int port = xxxxx;
#define PIN  D8 // GPIO pin
int NUMPIXELS = 12; // Number of pixels in strip
BlynkTimer TIMER;
byte M, A, R, G, B;
byte T[7];
// #define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  // Serial.begin(115200);
  EEPROM.begin(16);
  TIMER.setInterval(500L, LED);
  if (EEPROM.read(0) == 1) {
    LOAD();   
  }
  WiFi.mode(WIFI_STA);
  // wMulti.addAP("NavPhone7", "aabbccddee");
  // wMulti.addAP("Sterling", "amvsterling");
  
  WiFi.begin(ssid, pass); 
  delay(6000);
  if (WiFi.status() == WL_CONNECTED)
  //if (wMulti.run() == WL_CONNECTED) 
  {     //Serial.println("");
        //Serial.println("WiFi connected");
        //Serial.println("IP address: ");
        //Serial.println(WiFi.localIP());
  
  Blynk.config(auth, IPAddress(x,x,x,x), port); //(auth, server, port)
  Blynk.connect();
  }
  
  // Blynk.begin(auth, ssid, pass, IPAddress(68,111,139,135),55555);
  
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D4, OUTPUT);
  
  pixels.begin();
  M = EEPROM.read(7);
  pixels.setBrightness(M);
  pixels.show();
  R = EEPROM.read(8); G = EEPROM.read(9); B = EEPROM.read(10); 
  
}
void LED() { 
  digitalWrite(D4, !digitalRead(D4));  //LED flip-flop
}

void FLUSH() {
  for (int I = 0; I <= NUMPIXELS; I++) 
  {pixels.setPixelColor(I, pixels.Color(0,0,0));}
  pixels.show();
  
}
BLYNK_WRITE(V1) {
  if (A == 1){
  int data = param.asInt();
  EEPROM.write(1, data);
  EEPROM.commit();
  }
}
BLYNK_WRITE(V2) {
  if (A == 1){
  int data = param.asInt();
  EEPROM.write(2, data);
  EEPROM.commit();
  }
}
BLYNK_WRITE(V3) {
  if (A == 1){
  int data = param.asInt();
  EEPROM.write(3, data);
  EEPROM.commit();
  }
}
BLYNK_WRITE(V4) {
  if (A == 1){
  int data = param.asInt();
  EEPROM.write(4, data);
  EEPROM.commit();
  }
}
BLYNK_WRITE(V5) {
  if (A == 1){
  int data = param.asInt();
  EEPROM.write(5, data);
  EEPROM.commit();
  }
}
BLYNK_WRITE(V6) {
  if (A == 1){
  int data = param.asInt();
  EEPROM.write(6, data);
  EEPROM.commit();
  }
}
BLYNK_WRITE(V7) {  
      Blynk.virtualWrite(V1, EEPROM.read(1));
      Blynk.virtualWrite(V2, EEPROM.read(2));
      Blynk.virtualWrite(V3, EEPROM.read(3));
      Blynk.virtualWrite(V4, EEPROM.read(4));
      Blynk.virtualWrite(V5, EEPROM.read(5));
      Blynk.virtualWrite(V6, EEPROM.read(6));
      Blynk.virtualWrite(V8, EEPROM.read(7)); //Duty Cycle
      Blynk.virtualWrite(V11, EEPROM.read(8)); // R
      Blynk.virtualWrite(V12, EEPROM.read(9)); // G
      Blynk.virtualWrite(V13, EEPROM.read(10));// B
      if (EEPROM.read(0) != 1) {EEPROM.write(0, 1);
                                 EEPROM.commit();} 
}   
BLYNK_WRITE(V8) {
  int B = param.asInt();
  pixels.setBrightness(B);
  EEPROM.write(7, B);
  EEPROM.commit();
     
}
BLYNK_WRITE(V11) {
  int data = param.asInt();
  R = data;
  EEPROM.write(8, R);
  EEPROM.commit();
}

BLYNK_WRITE(V12) {
  int data = param.asInt();
  G = data;
  EEPROM.write(9, G);
  EEPROM.commit();
}
BLYNK_WRITE(V13) {
  int data = param.asInt();
  B = data;
  EEPROM.write(10, B);
  EEPROM.commit();
}

void LOAD() {
  for (int I = 1; I <= 6; I++) {T[I] = EEPROM.read(I);}
}
void RND() 
{
     
    if(!digitalRead(D1)) {
    pixels.setPixelColor(T[1]-1, pixels.Color(R,G,B));
    pixels.setPixelColor(T[1], pixels.Color(R,G,B));
    pixels.setPixelColor(T[1]+1, pixels.Color(R,G,B));
    
    pixels.show();}
    else {
    pixels.setPixelColor(T[1]-1, pixels.Color(0,0,0));
    pixels.setPixelColor(T[1], pixels.Color(0,0,0));
    pixels.setPixelColor(T[1]+1, pixels.Color(0,0,0));
    pixels.show();}
    
    if(!digitalRead(D2)) {
    pixels.setPixelColor(T[2]-1, pixels.Color(R,G,B));
    pixels.setPixelColor(T[2], pixels.Color(R,G,B));
    pixels.setPixelColor(T[2]+1, pixels.Color(R,G,B));
    
    pixels.show();}
    else {
    pixels.setPixelColor(T[2]-1, pixels.Color(0,0,0));
    pixels.setPixelColor(T[2], pixels.Color(0,0,0));
    pixels.setPixelColor(T[2]+1, pixels.Color(0,0,0));
    
    pixels.show();}
    
    if(!digitalRead(D3)) {
    pixels.setPixelColor(T[3]-1, pixels.Color(R,G,B));
    pixels.setPixelColor(T[3], pixels.Color(R,G,B));
    pixels.setPixelColor(T[3]+1, pixels.Color(R,G,B));
    
    pixels.show();}
    else {
    pixels.setPixelColor(T[3]-1, pixels.Color(0,0,0));
    pixels.setPixelColor(T[3], pixels.Color(0,0,0));
    pixels.setPixelColor(T[3]+1, pixels.Color(0,0,0));
    
    pixels.show();}
    
    if(!digitalRead(D5)) {
    pixels.setPixelColor(T[4]-1, pixels.Color(R,G,B));
    pixels.setPixelColor(T[4], pixels.Color(R,G,B));
    pixels.setPixelColor(T[4]+1, pixels.Color(R,G,B));
    
    pixels.show();}
    else {
    pixels.setPixelColor(T[4]-1, pixels.Color(0,0,0));
    pixels.setPixelColor(T[4], pixels.Color(0,0,0));
    pixels.setPixelColor(T[4]+1, pixels.Color(0,0,0));
    
    pixels.show();}
    
    if(!digitalRead(D6)) {
    pixels.setPixelColor(T[5]-1, pixels.Color(R,G,B));
    pixels.setPixelColor(T[5], pixels.Color(R,G,B));
    pixels.setPixelColor(T[5]+1, pixels.Color(R,G,B));
    
    pixels.show();}
    else {
    pixels.setPixelColor(T[5]-1, pixels.Color(0,0,0));
    pixels.setPixelColor(T[5], pixels.Color(0,0,0));
    pixels.setPixelColor(T[5]+1, pixels.Color(0,0,0));
    
    pixels.show();}
    
    if(!digitalRead(D7)) {
    pixels.setPixelColor(T[6]-1, pixels.Color(R,G,B));
    pixels.setPixelColor(T[6], pixels.Color(R,G,B));
    pixels.setPixelColor(T[6]+1, pixels.Color(R,G,B));
    
    pixels.show();}
    else {
    pixels.setPixelColor(T[6]-1, pixels.Color(0,0,0));
    pixels.setPixelColor(T[6], pixels.Color(0,0,0));
    pixels.setPixelColor(T[6]+1, pixels.Color(0,0,0));
    
    pixels.show();}       
}

void loop()
{
   if(Blynk.connected()){
       Blynk.run(); 
       TIMER.run();      
           }
  
  if (A == 0) {RND();}
}


BLYNK_WRITE(V0) {
  switch (param.asInt()) {
    case 1: {A = 0; LOAD();break;}
    case 2: {A = 1; FLUSH();break; }
    case 3: {TEST1(); A = 0; Blynk.virtualWrite(V0, 1);break;}
    case 4: {TEST2(); A = 0; Blynk.virtualWrite(V0, 1);break;}
  }
}

void TEST1() {

  colorWipe(pixels.Color(127, 0, 0), 20); // Red
  colorWipe(pixels.Color(0, 127, 0), 20); // Green
  colorWipe(pixels.Color(0, 0, 127), 20); // Blue
  colorWipe(pixels.Color(0, 0, 0), 20); // Black
  
}
void TEST2() { 
  
  theaterChase(pixels.Color(127, 127, 127), 50); // White
  theaterChase(pixels.Color(127,   0,   0), 50); // Red
  theaterChase(pixels.Color(  0,   0, 127), 50); // Blue
  theaterChase(pixels.Color(  0,   0, 0), 50); // Blue
  
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
/*
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 16; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < pixels.numPixels(); i=i+3) {
          pixels.setPixelColor(i+q, Wheel( (i+j*16) % 255));    //turn every third pixel on
        }
        pixels.show();

        delay(wait);

        for (int i=0; i < pixels.numPixels(); i=i+3) {
          pixels.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}


uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
*/
