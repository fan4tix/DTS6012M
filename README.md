# DTS6012M Arduino Library

Arduino library for the **DTS6012M dToF (Direct Time-of-Flight) rangefinder module**.

This library enables distance measurement using the DTS6012M sensor via **I2C communication**.

## Features

* I2C communication interface
* Distance measurement in meters
* Lightweight and easy-to-use

> Currently only **I2C communication** is supported.

---

## Background

This library is based on the STM32 implementation:

* STM32 library by [eggsacc](https://github.com/eggsacc):
  [https://github.com/eggsacc/STM32-DTS6012M](https://github.com/eggsacc/STM32-DTS6012M)

The implementation also follows the official DTS6012M datasheet:

* English Datasheet:
  [https://www.polarisic.com/uploads/soft/20240814/1723611422.pdf](https://www.polarisic.com/uploads/soft/20240814/1723611422.pdf)
* Chinese Datasheet (Contains Pinout):
  [https://github.com/eggsacc/STM32-DTS6012M/blob/main/Attachments/DTS6012Mdatasheet.pdf](https://github.com/eggsacc/STM32-DTS6012M/blob/main/Attachments/DTS6012Mdatasheet.pdf)

---

## Hardware

**Sensor:** DTS6012M dToF Rangefinder Module
**Interface:** Currently only I2C is supported


### Typical I2C Wiring

| DTS6012M | Arduino                  |
| -------- | ------------------------ |
| VCC      | 3.3V                     |
| GND      | GND                      |
| SDA      | SDA                      |
| SCL      | SCL                      |

---

## Installation

### Option 1 – Manual Installation

1. Download the repository as ZIP
2. In Arduino IDE:
   **Sketch → Include Library → Add .ZIP Library**
3. Select the downloaded ZIP file

### Option 2 – Clone into Libraries Folder

```bash
git clone https://github.com/fan4tix/DTS6012M.git
```

Place it inside your Arduino `libraries` folder.

---

## Basic Usage Example

```cpp
#include <Wire.h>
#include "DTS6012M.h"

DTS6012M tof;

void setup() {
  Serial.begin(115200);
  Wire.begin();   

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
```

---

## API Overview

### `bool begin()`

Initializes the sensor and checks communication.

Returns:

* `true` if sensor detected
* `false` if communication failed

### `float readDistance()`

Reads the current measured distance in meters.

---

## Compatibility

* All Arduino boards
* Any board supporting I2C (`Wire` library)

---

## License

MIT license, all text above must be included in any redistribution.

---
