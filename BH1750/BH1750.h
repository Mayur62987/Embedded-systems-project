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

#ifndef BH1750_h
#define BH1750_h

#include "mbed.h"

#define BH1750_I2CADDR 0x46

// No active state
#define BH1750_POWER_DOWN 0x00

// Wating for measurment command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2  0x11

// Start measurement at 4lx resolution. Measurement time is approx 16ms.
#define BH1750_CONTINUOUS_LOW_RES_MODE  0x13

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE  0x20

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE_2  0x21

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_LOW_RES_MODE  0x23

/**
* @code
* #include "mbed.h"
* #include "BH1750.h"
*
* BH1750 lightSensor(I2C_SDA, I2C_SCL);
* Serial pc(SERIAL_TX, SERIAL_RX);
*
* int main() 
* {
*    lightSensor.init();
*
*    while(1) {
*        pc.printf("Light intensity: %.4f Lux\r\n", lightSensor.readIntesity());
*        wait(5);
*    }
* }
* @endcode
*/

class BH1750
{
public:
    /**
    * @param sda
    * @param scl
    */
    static char rawDataBuffer[2];
    BH1750(PinName sda, PinName slc);

    /**
    * Initialize sensor with specified mode.
    * Default mode is set to BH1750_CONTINUOUS_HIGH_RES_MODE.
    * @param mode of sensor operation.
    */
    void init(char mode = BH1750_CONTINUOUS_HIGH_RES_MODE);

    /**
    * Configure sensor with specified mode.
    * This function is called also in init(char);
    * @param mode of sensor operation.
    */
    void configure(char mode);

    /**
    * Read light intensity.
    * In addition also error code and raw data are filled.
    * @return light intensity in Lux.
    */
    float readIntesity(void);

    /**
    * Get raw data obtained after sucessfull executing of readIntesity(void).
    * @return unprocessed raw data readed from sensor.
    */
    char* getRawData(void);

    /**
    * @returns
    *     0 no error.
    *     !=0 I2C error code.
    */
    int getStatus(void);

private:
    I2C i2c;
    
    int status;
};

#endif
