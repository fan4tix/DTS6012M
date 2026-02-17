#ifndef DTS6012M_H
#define DTS6012M_H

#include <Arduino.h>
#include <Wire.h>

/*
 * I2C Address and register definitions
 */
#define DTS6012M_I2C_ADDR 0x51   // 7-bit I2C address
#define MSB_ADD           0x00
#define LSB_ADD           0x01
#define LASER_EN_ADD      0x02

/*
 * Scaling factor and offset
 */
#define DTS6012M_SCALING_FACTOR   0.001f
#define DTS6012M_OFFSET_DISTANCE  0.0f

class DTS6012M {
public:
    // Constructor
    DTS6012M(TwoWire &wire = Wire);

    // Initialization
    bool begin();

    // Laser control
    void startLaser();
    void stopLaser();

    // Measurement
    float getDistance();      // meters
    uint16_t getRawDistance();

private:
    TwoWire* _wire;
    uint16_t _rawDistance;

    bool readRegisters(uint8_t reg, uint8_t* buffer, uint8_t length);
    bool writeRegister(uint8_t reg, uint8_t data);
};

#endif // DTS6012M_H
