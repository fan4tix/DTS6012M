#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DTS6012M.h>

/* OLED configuration */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1      // Reset pin not used
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DTS6012M tof;

void setup() {
  Serial.begin(115200);

  // ESP32 I2C pins (change if needed)
  Wire.begin(4, 5);

  /* Initialize OLED */
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("DTS6012M TOF");
  display.println("Initializing...");
  display.display();

  /* Initialize sensor */
  if (!tof.begin()) {
    display.clearDisplay();
    display.println("Sensor not found!");
    display.display();
    while (1);
  }

  delay(1000);
}

void loop() {
  float distance = tof.getDistance();

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("DTS6012M Distance");

  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(distance, 3);
  display.println(" m");

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Raw: ");
  display.print(tof.getRawDistance());

  display.display();
  delay(100);
}
