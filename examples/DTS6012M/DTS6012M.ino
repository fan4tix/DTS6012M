#include <Wire.h>
#include <DTS6012M.h>

DTS6012M tof;

void setup() {
  Serial.begin(115200);
  Wire.begin();   // ESP32: Wire.begin(SDA, SCL) if needed

  if (!tof.begin()) {
    Serial.println("DTS6012M not detected!");
    while (1);
  }

  Serial.println("DTS6012M ready");
}

void loop() {
  float distance = tof.getDistance();
  Serial.print("Distance: ");
  Serial.print(distance, 3);
  Serial.println(" m");
  delay(100);
}
