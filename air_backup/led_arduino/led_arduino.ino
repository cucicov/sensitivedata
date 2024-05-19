
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
  strip.Color(0, 200, 0),
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 50, 0),
  strip.Color(0, 150, 0),
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 200, 0),
  strip.Color(0, 100, 0),
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 200, 0),      // Green
  strip.Color(0, 100, 0),
  strip.Color(0, 50, 0),
  strip.Color(100, 100, 0),
  strip.Color(150, 150, 0),
  strip.Color(200, 200, 0),
  strip.Color(255, 255, 0),   // Yellow
  strip.Color(50, 50, 0),
  strip.Color(50, 50, 0),
  strip.Color(150, 150, 0),
  strip.Color(200, 200, 0),   // Yellow
  strip.Color(255, 255, 0),
  strip.Color(255, 0, 0),     // Red
  strip.Color(200, 0, 0),
  strip.Color(150, 0, 0),
  strip.Color(100, 0, 0),
  strip.Color(255, 0, 0),     // Red
  strip.Color(200, 0, 0),
  strip.Color(100, 0, 0),
  strip.Color(200, 0, 0)     // Red
};

uint32_t currentColor = strip.Color(0, 0, 0);
String incoming;

void setup() {
  Serial.begin(115200);
  Serial.println("Started the receiver (black board");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop() {
  
  if (Serial2.available() >= 1) {
    //Serial.print(char(Serial2.read()));
    incoming = Serial2.readStringUntil('\n');
    Serial.println(incoming);
    
    if (incoming == "reset") {
      Serial.println("reset received");
      lcd.setCursor(0, 0);
      // print message     
      lcd.print("reset received");
      delay(1000);
      // clears the display to print new message
      lcd.clear();
    } else {
      fadeBetweenColors(colorArray[incoming.toInt() - 1], colorArray[incoming.toInt()], 1000);
      Serial.print("next received: ");
      Serial.println(incoming.toInt());
      lcd.setCursor(0, 0);
      // print message     
      lcd.print(incoming.toInt());
      delay(1000);
      // clears the display to print new message
      lcd.clear();
    }
  }



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
