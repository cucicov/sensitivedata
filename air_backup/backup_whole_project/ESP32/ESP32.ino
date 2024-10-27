
#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>

const int inputPin = 2; // Digital input pin on Receiver Arduino
const int resetPin = 3; // Digital input pin on Receiver Arduino

#define RXD2 16
#define TXD2 17

#define PIN        2 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 118 // Popular NeoPixel ring size

#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colorArray[30] = {
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 150, 0),
  strip.Color(0, 50, 0),     // Green
  strip.Color(50, 50, 0),   // Yellow
  strip.Color(100, 100, 0),
  strip.Color(200, 200, 0),
  strip.Color(255, 200, 0),   
  strip.Color(255, 165, 0),     // orange
  strip.Color(200, 0, 0), // red
  strip.Color(100, 0, 50) // violet
};

struct DayData {
  const char* date;
  float originalPM;
  float mappedPM;
};

DayData data[] = {
  {"1 January", 68.00, 5.00},
  {"2 January", 35.00, 3.00},
  {"3 January", 39.00, 3.00},
  {"4 January", 34.00, 3.00},
  {"5 January", 39.00, 3.00},
  {"6 January", 48.00, 4.00},
  {"7 January", 39.00, 3.00},
  {"8 January", 23.00, 2.00},
  {"9 January", 23.00, 2.00},
  {"10 January", 26.00, 2.00},
  {"11 January", 29.00, 2.00},
  {"12 January", 23.00, 2.00},
  {"13 January", 24.00, 2.00},
  {"14 January", 30.00, 2.00},
  {"15 January", 55.00, 4.00},
  {"16 January", 36.00, 3.00},
  {"17 January", 53.00, 4.00},
  {"18 January", 34.00, 3.00},
  {"19 January", 35.00, 3.00},
  {"20 January", 27.00, 2.00},
  {"21 January", 34.00, 3.00},
  {"22 January", 32.00, 2.00},
  {"23 January", 23.00, 2.00},
  {"24 January", 32.00, 2.00},
  {"25 January", 29.00, 2.00},
  {"26 January", 22.00, 2.00},
  {"27 January", 26.00, 2.00},
  {"28 January", 25.00, 2.00},
  {"29 January", 25.00, 2.00},
  {"30 January", 38.00, 3.00},
  {"31 January", 75.00, 6.00}
};

uint32_t currentColor = strip.Color(0, 0, 0);
String incoming;

void updateDisplay(const char* date, float pmValue, int colorStart, int colorEnd) {
  lcd.setCursor(0, 0);
  lcd.print(date);
  lcd.setCursor(0, 1);
  lcd.print("PM10: " + String(pmValue));
  fadeBetweenColors(colorStart, colorEnd, 1000);
  delay(3000);
  lcd.clear();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Started the receiver (black board");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

int counter = 0;

void loop() {

  counter += 1;
  
  if (counter == 31) {
    counter = 1;
  }
  
  int dataSize = sizeof(data) / sizeof(data[0]);

  if (counter >= 1 && counter <= sizeof(data) + 1) {
    Serial.print("next received: ");
    Serial.println(counter);

    int previousIndex = counter - 2; // Previous day index
    int currentIndex = counter - 1;  // Current day index

    // Check if the previous index is smaller than 0
    if (previousIndex < 0) {
      previousIndex = dataSize - 1; // Wrap around to the last index
    }

    int previousMappedIndex = round(data[previousIndex].mappedPM);
    int currentMappedIndex = round(data[currentIndex].mappedPM);

    updateDisplay(data[currentIndex].date, data[currentIndex].originalPM,
                  colorArray[previousMappedIndex], colorArray[currentMappedIndex]);
  }
  
//  if (Serial2.available() >= 1) {
//    //Serial.print(char(Serial2.read()));
//    incoming = Serial2.readStringUntil('\n');
//    Serial.println(incoming);
//    
//    if (incoming == "reset") {
//      Serial.println("reset received");
//      lcd.setCursor(0, 0);
//      // print message     
//      lcd.print("reset received");
//      delay(1000);
//      // clears the display to print new message
//      lcd.clear();
//    } else {
////      fadeBetweenColors(colorArray[incoming.toInt() - 1], colorArray[incoming.toInt()], 1000);
//      for (int i = 0; i < strip.numPixels(); i++) {
//        strip.setPixelColor(i, colorArray[incoming.toInt()]);
//      }
//      Serial.print("next received: ");
//      Serial.println(incoming.toInt());
//      lcd.setCursor(0, 0);
//      // print message     
//      lcd.print(incoming.toInt());
//      delay(1000);
//      strip.show();
//      // clears the display to print new message
//      lcd.clear();
//    }
//  }



  delay(100); // Delay for 100 milliseconds between readings
}

void fadeBetweenColors(uint32_t colorFrom, uint32_t colorTo, uint32_t duration) {
  uint32_t startTime = millis();
  while (millis() - startTime <= duration) {
    float progress = (float)(millis() - startTime) / (float)duration; // Calculate fade progress (0.0 to 1.0)
    
    // Interpolate color components
    uint8_t r = ((uint8_t)((1.0 - progress) * ((colorFrom >> 16) & 0xFF) + progress * ((colorTo >> 16) & 0xFF)));
    uint8_t g = ((uint8_t)((1.0 - progress) * ((colorFrom >> 8) & 0xFF) + progress * ((colorTo >> 8) & 0xFF)));
    uint8_t b = ((uint8_t)((1.0 - progress) * (colorFrom & 0xFF) + progress * (colorTo & 0xFF)));
    
    // Set each pixel to the interpolated color
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    
    strip.show(); // Update NeoPixel strip with interpolated color
  }
}
