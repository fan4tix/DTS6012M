#include <Wire.h>
#include <TFT_eSPI.h>
#include <DTS6012M.h>

/* Display + Sensor objects */
TFT_eSPI tft = TFT_eSPI();
DTS6012M tof;
#define TFT_BL 4
void setup() {
  Serial.begin(115200);


  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  // I2C for DTS6012M
  Wire.begin(21, 22);

  // Initialize TFT
  tft.init();
  tft.setRotation(1);  // Landscape
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("DTS6012M TOF");
  tft.setTextSize(1);
  tft.println("Initializing...");
  Serial.println("Initializing...");
  // Initialize sensor
  if (!tof.begin()) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 30);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.println("Sensor not found!");
    while (1)
      ;
  }

  delay(1000);
  tft.fillScreen(TFT_BLACK);

  Serial.println("Setup OK...");
}

void loop() {
  float distance = tof.getDistance();

  // Clear only the data area to reduce flicker
  tft.fillRect(0, 30, 240, 105, TFT_BLACK);

  // Title
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 0);
  tft.println("Distance");

  // Distance value
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(4);
  tft.setCursor(10, 35);
  tft.print(distance, 3);
  tft.print(" m");

  // Raw value
  tft.setTextSize(1);
  tft.setCursor(10, 90);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.print("Raw: ");
  tft.print(tof.getRawDistance());

  Serial.println(distance);
  delay(100);
}
