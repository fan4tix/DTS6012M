#include "DTS6012M.h"

/*
 * Constructor
 */
DTS6012M::DTS6012M(TwoWire &wire)
{
    _wire = &wire;
    _rawDistance = 0;
}

/*
 * Initialize sensor
 * Returns true if sensor is detected
 */
bool DTS6012M::begin()
{
    _wire->begin();

    // Check if device responds
    _wire->beginTransmission(DTS6012M_I2C_ADDR);
    if (_wire->endTransmission() != 0) {
        return false;
    }

    // Enable laser by default
    startLaser();
    return true;
}

/*
 * Enable laser (start measurement)
 */
void DTS6012M::startLaser()
{
    writeRegister(LASER_EN_ADD, 1);
}

/*
 * Disable laser (stop measurement)
 */
void DTS6012M::stopLaser()
{
    writeRegister(LASER_EN_ADD, 0);
}

/*
 * Read distance in meters
 */
float DTS6012M::getDistance()
{
    uint8_t data[2];

    if (!readRegisters(MSB_ADD, data, 2)) {
        return 0.0f;
    }

    _rawDistance = ((uint16_t)data[0] << 8) | data[1];

    return (_rawDistance * DTS6012M_SCALING_FACTOR)
           + DTS6012M_OFFSET_DISTANCE;
}

/*
 * Get last raw distance value
 */
uint16_t DTS6012M::getRawDistance() const
{
    return _rawDistance;
}

/*
 * Low-level I2C register read
 */
bool DTS6012M::readRegisters(uint8_t reg, uint8_t* buffer, uint8_t length)
{
    _wire->beginTransmission(DTS6012M_I2C_ADDR);
    _wire->write(reg);
    if (_wire->endTransmission(false) != 0) {
        return false;
    }

    uint8_t received = _wire->requestFrom(DTS6012M_I2C_ADDR, length);
    if (received != length) {
        return false;
    }

    for (uint8_t i = 0; i < length; i++) {
        buffer[i] = _wire->read();
    }

    return true;
}

/*
 * Low-level I2C register write
 */
bool DTS6012M::writeRegister(uint8_t reg, uint8_t data)
{
    _wire->beginTransmission(DTS6012M_I2C_ADDR);
    _wire->write(reg);
    _wire->write(data);
    return (_wire->endTransmission() == 0);
}
