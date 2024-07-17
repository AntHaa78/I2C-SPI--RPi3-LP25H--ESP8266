//#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
//#include <Adafruit_BusIO_Register.h>

// library for BME280 sensor
//#include <Adafruit_BME280.h>
//#include <Adafruit_Sensor.h>

//#include <ESP8266WiFi.h>
//#include <stdio.h>

//#include <Adafruit_ST7735.h> // include Adafruit ST7735S  library
//#include <Adafruit_GFX.h> // include Adafruit graphics library

//#include <allinonelib.h>

#include <RTClib.h> // RTC lib

#define TFT_RES   D0     // ST7735S RES pin is connected to ESP8266 D0 pin  (GPI16)   -- OPTIONAL
#define TFT_DC    D4     // ST7735S DC  pin is connected to ESP8266 D4 pin  (GPIO2)
#define TFT_CS    D8     // ST7735S CS  pin is connected to ESP8266 D8 pin  (GPI15)

//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RES);


// Don't need to define cause hardware fixed, but can change if we want? slower?
//#define TFT_SCLK 13  
//#define TFT_MOSI 11  

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme; // I2C

//unsigned long delayTime;


// LED STUFF -------------------------------------------------------------------------------------------------------------------------------------------------
/*
void setup()
{
  Serial.begin(115200);
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop()
{
  // turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);
  Serial.println("Led on for three seconds...");

  //Adafruit_BME280 bme; // I2Cturn the LED on by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for three seconds
  delay(3000);
  Serial.println("Led off for one second..");
}
*/
// CONNECT TO WIFI -----------------------------------------------------------------------------------------------------------
/* void setup()
{
  Serial.begin(921600);
  Serial.println();

  WiFi.begin("network", "***!!");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {} */

// SCAN WIFIS --------------------------------------------------------------------------------------------------------------------------------
/*void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.println("Setup done");
}

void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}*/

// GET SENSOR BME280 DATAS -----------------------------------------------------------------------------------------------------------------------------
// I2C com
/* void setup() {
    Serial.begin(115200);
    delay(3000);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin(0x76);  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 5000;

    Serial.println();
}

void printValues() {
    Serial.print("\nTemperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void loop() { 
    printValues();
    delay(delayTime);
} */





// I2C scanner ----------------------------------------------------------------------------------------------------------------------------------------------
/*
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}
 
void loop() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);          
}  
*/

// We get 0x76 for BME280
// for AT24C02:
//I2C device found at address 0x50
//I2C device found at address 0x51
//I2C device found at address 0x52
//I2C device found at address 0x53
//I2C device found at address 0x54
//I2C device found at address 0x55
//I2C device found at address 0x56
//I2C device found at address 0x57


// ICST7735S Display ------------------------------------------------------------------------------------------------------------
// SPI communication
/*
void setup(void) {
  Serial.begin(9600);

  delay(3000);
  while(!Serial);    // time to get serial running
  Serial.println(F("BME280 test"));

  unsigned status;
    
  // default settings
  status = bme.begin(0x76);  
    
  Serial.println("-- Default Test --");
  delayTime = 5000;

  Serial.println();

  Serial.print("Hello! ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  //tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  // This for 0.96"?
  tft.initR(INITR_MINI160x80);

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // Drawing OPTO

  tft.drawChar(30, 10, 79, ST7735_CYAN, ST7735_BLACK, 4); // O
  tft.drawChar(30, 50, 80, ST7735_CYAN, ST7735_BLACK, 4); // P
  tft.drawChar(30, 90, 84, ST7735_CYAN, ST7735_BLACK, 4); // T
  tft.drawChar(30, 130, 79, ST7735_CYAN, ST7735_BLACK, 4); // O

  // bot and top lines for letters
  uint16_t bottom_line = 20;
  uint16_t top_line = 60;
  uint16_t inner_spacing = 20;
  uint16_t outer_spacing = 20;
  uint16_t x_start = 10;
  uint16_t x_second_letter = x_start+inner_spacing+outer_spacing;
  uint16_t x_third_letter = x_second_letter+inner_spacing+outer_spacing;
  uint16_t x_fourth_letter = x_third_letter + inner_spacing + outer_spacing;

  // letter O
  tft.drawLine(bottom_line, x_start, bottom_line, x_start+inner_spacing, ST7735_BLUE);
  tft.drawLine(top_line, x_start, top_line, x_start+inner_spacing, ST7735_BLUE);
  tft.drawLine(bottom_line, x_start, top_line, x_start, ST7735_BLUE);
  tft.drawLine(bottom_line, x_start+inner_spacing, top_line, x_start+inner_spacing, ST7735_BLUE);
  delay(500);

  // letter P
  tft.drawLine(bottom_line, x_second_letter, top_line, x_second_letter, ST7735_BLUE);
  tft.drawLine(top_line, x_second_letter, 50, x_second_letter+inner_spacing, ST7735_BLUE);
  tft.drawLine(40, x_second_letter, 50, x_second_letter+inner_spacing, ST7735_BLUE);
  delay(500);

  // letter T
  tft.drawLine(bottom_line, x_third_letter+10, top_line, x_third_letter+10, ST7735_BLUE);
  tft.drawLine(top_line, x_third_letter, top_line, x_third_letter+inner_spacing, ST7735_BLUE);
  delay(500);

  // letter O
  tft.drawLine(bottom_line, x_fourth_letter, bottom_line, x_fourth_letter+inner_spacing, ST7735_BLUE);
  tft.drawLine(top_line, x_fourth_letter, top_line, x_fourth_letter+inner_spacing, ST7735_BLUE);
  tft.drawLine(bottom_line, x_fourth_letter, top_line, x_fourth_letter, ST7735_BLUE);
  tft.drawLine(bottom_line, x_fourth_letter+inner_spacing, top_line, x_fourth_letter+inner_spacing, ST7735_BLUE);
  delay(500);

  // large block of text
  tft.fillScreen(ST7735_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE);
  delay(1000);

  // tft print function!
  tftPrintTest();
  delay(4000); 

  // a single pixel
  //tft.drawPixel(tft.width()/2, tft.height()/2, ST7735_GREEN);
  //delay(500);

  // circle
  //tft.drawCircle(tft.width()/2, tft.height()/2, tft.height()/4, ST7735_BLUE);
  //delay(500);

  // Rectangle
  tft.drawLine(10, 10, 10, 150, ST7735_BLUE);
  tft.drawLine(10, 10, 70, 10, ST7735_BLUE);
  tft.drawLine(70, 10, 70, 150, ST7735_BLUE);
  tft.drawLine(10, 150, 70, 150, ST7735_BLUE);
  delay(500);
 
 
Letter "P":

    Vertical line: drawLine(55, 70, 55, 90)
    Top horizontal line: drawLine(55, 70, 65, 70)
    Middle horizontal line: drawLine(55, 80, 65, 80)

Letter "T":

    Horizontal line: drawLine(70, 70, 90, 70)
    Vertical line: drawLine(80, 70, 80, 90)

Letter "O":

    Horizontal line: drawLine(95, 70, 115, 70)
    Vertical lines: drawLine(95, 70, 95, 90) and drawLine(115, 70, 115, 90)
    Horizontal line: drawLine(95, 90, 115, 90)

Letter "M":

    drawLine(120, 70, 120, 90)
    drawLine(120, 70, 125, 80)
    drawLine(125, 80, 130, 70)
    drawLine(130, 70, 130, 90)

Letter "E":

    Vertical line: drawLine(135, 70, 135, 90)
    Horizontal lines: drawLine(135, 70, 145, 70) and drawLine(135, 80, 145, 80)
    Bottom horizontal line: drawLine(135, 90, 145, 90)




   // line draw test
  testlines(ST7735_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST7735_RED, ST7735_BLUE);
  delay(500);

  testdrawrects(ST7735_GREEN);
  delay(500);

  testfillrects(ST7735_YELLOW, ST7735_MAGENTA);
  delay(500);

  tft.fillScreen(ST7735_BLACK);
  testfillcircles(10, ST7735_BLUE);
  testdrawcircles(10, ST7735_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500); 

  Serial.println("done");
  delay(1000);
}

void printValues() {
  Serial.print("\nTemperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

int16_t getTemperature(){
  int16_t temperature;
  temperature = int(bme.readTemperature()+0.5);
  return temperature;
  //Temp_firstDigit = temperature/10;
  //Temp_firstDigit = temperature%10;
  //return Temp_firstDigit, Temp_firstDigit;
}

void printTemperature(){
  int16_t temperature, Temp_firstDigit, Temp_secondDigit;
  temperature = getTemperature();
  Temp_firstDigit = temperature/10 + 48; // get the number ascii decimal ( 48=0)
  Temp_secondDigit = temperature%10 + 48;

  tft.drawChar(30, 10, 84, ST7735_CYAN, ST7735_BLACK, 4); // T
  tft.drawChar(30, 60, 61, ST7735_CYAN, ST7735_BLACK, 4); // =
  tft.drawChar(10, 110, Temp_firstDigit, ST7735_CYAN, ST7735_BLACK, 2); // first digit
  tft.drawChar(25, 110, Temp_secondDigit, ST7735_CYAN, ST7735_BLACK, 2); // first digit
  tft.drawChar(40, 110, 167, ST7735_CYAN, ST7735_BLACK, 2); // °
  tft.drawChar(55, 110, 67, ST7735_CYAN, ST7735_BLACK, 2); // C


  Serial.print("\nTemperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
}

void loop() {
// Invert colors and print values of sensor
  Serial.println("Inverted colors");  
  tft.invertDisplay(true);
  printTemperature();
  delay(2000);

  Serial.println("True colors");
  tft.invertDisplay(false);
  delay(2000);
}*/

// EEPROM AT24C02 (I2C) ----------------------------------------------------------------------------------------------------------------------------------------
// 2x 6.9kOhms resistors

/*
#define ADDR_Ax 0b000 //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax

void writeI2CByte(byte data_addr, byte data){
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr){
  byte data = NULL;
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1); //retrieve 1 returned byte
  delay(100);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  //writeI2CByte(0, 64);
  //delay(500);
  uint8_t i;
  Serial.println("Writing on 50 first bytes");
  for (i=0;i<50;i++){
    writeI2CByte(i, i+100);
    delay(10);
  }
  Serial.println(readI2CByte(35));
  delay(1000);
  Serial.println("Initialization completed beep boop");
}

void loop() {
  delay(5000);
  uint8_t i;
  Serial.println("50 first bytes: ");
  for (i=0;i<50;i++){
    Serial.println(String(i) + " : " + String(readI2CByte(i)));
    delay(50);
  }
}*/

// Real Time Clock DS1307 ------------------------------------------------------------------------------------------------------------------------
// I2C

RTC_DS1307 rtc;

// days start from 0 = sunday
char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void setup(){
  Serial.begin(115200);

  //Setup RTC module
  if (!rtc.begin()){
    Serial.println("Could not find RTC");
    Serial.flush();
    while(1);
  }

  //adjust RTC to PC time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // for manualy adjusting
  // rtc.adjust(DateTime(2024, 12, 31, 15, 0, 0));
  delay(1000);
  Serial.print("Initialization complete.");
}

void loop(){
  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  delay(5000);
}
