/*

This is a library for the BH1750FVI (GY-30) Digital Light Sensor
breakout board.

The board uses I2C for communication. 2 pins are required to
interface to the device and in most cases also pull up resistors.

Datasheet:
http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1750fvi-e.pdf

Inspired by Christopher Laws, March, 2013.
Written by Michal Stehlik, August, 2014.

*/

#include "BH1750.h"

BH1750::BH1750(PinName sda, PinName scl) : i2c(sda,scl)
{
    rawDataBuffer[0] = 0;
    rawDataBuffer[1] = 0;
    status = -1;
}

void BH1750::init(char mode)
{
    configure(mode);
}


void BH1750::configure(char mode)
{
    char data[1];
    switch (mode) {
        case BH1750_CONTINUOUS_HIGH_RES_MODE:
        case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
        case BH1750_CONTINUOUS_LOW_RES_MODE:
        case BH1750_ONE_TIME_HIGH_RES_MODE:
        case BH1750_ONE_TIME_HIGH_RES_MODE_2:
        case BH1750_ONE_TIME_LOW_RES_MODE:
            data[0] = mode;
            status = i2c.write(BH1750_I2CADDR, data, sizeof(data), false);
            wait_ms(10);
            break;
        default:
            break;
    }
}


float BH1750::readIntesity(void)
{
    status = i2c.read(BH1750_I2CADDR, rawDataBuffer, 2, false);
    if(status != 0) {
        return -1;
    }
    //success
    float result = 0;
    result = ((rawDataBuffer[0]<<8)|rawDataBuffer[1])/1.2;
    return result;
}

int BH1750::getStatus(void)
{
    return status;
}

char* BH1750::getRawData(void)
{
    return rawDataBuffer;
}
