
#ifndef SHT30_H
#define SHT30_H

#include "mbed.h"

//#define SHT30_DEFAULT_ADDR 0x44 << 1 /**< SHT30 Default Address */
#define SHT30_MEAS_HIGHREP_STRETCH 0x2C06 /**< Measurement High Repeatability with Clock Stretch Enabled */
#define SHT30_MEAS_MEDREP_STRETCH 0x2C0D /**< Measurement Medium Repeatability with Clock Stretch Enabled */
#define SHT30_MEAS_LOWREP_STRETCH 0x2C10 /**< Measurement Low Repeatability with Clock Stretch Enabled*/
#define SHT30_MEAS_HIGHREP 0x2400 /**< Measurement High Repeatability with Clock Stretch Disabled */
#define SHT30_MEAS_MEDREP 0x240B /**< Measurement Medium Repeatability with Clock Stretch Disabled */
#define SHT30_MEAS_LOWREP 0x2416 /**< Measurement Low Repeatability with Clock Stretch Disabled */
#define SHT30_READSTATUS 0xF32D   /**< Read Out of Status Register */
#define SHT30_CLEARSTATUS 0x3041  /**< Clear Status */
#define SHT30_SOFTRESET 0x30A2    /**< Soft Reset */
#define SHT30_HEATEREN 0x306D     /**< Heater Enable */
#define SHT30_HEATERDIS 0x3066    /**< Heater Disable */
#define SHT30_REG_HEATER_BIT 0x0d /**< Status Register Heater Bit */
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)




class SHT30
{
public:

    /**
    * @param sda
    * @param scl
    */
 // SHT30(PinName sda, PinName slc);
 // init(char mode = SHT30_MEAS_HIGHREP_STRETCH);

    /**
    * Configure sensor with specified mode.
    * This function is called also in init(char);
    * @param mode of sensor operation.
    */
  static char readbuffer[6];  
  SHT30(PinName sda, PinName slc);
  float readTemperature(void);
  float readHumidity(void);
  uint16_t readStatus(void);
  void reset(void);
  void heater(bool h);
  bool isHeaterEnabled();



private:
  /**
   * Placeholder to track humidity internally.
   */
    
  I2C i2c; 
  float humidity;
  //char readbuffer[6];

  /**
   * Placeholder to track temperature internally.
   */
  float temp;
  bool readTempHum(void);
  bool writeCommand(uint16_t cmd);
  static uint8_t crc8(const uint8_t *data, uint8_t len);
  //static bool readFromI2c(uint8_t i2cAddress,
                          //const uint8_t *i2cCommand,
                         // uint8_t commandLength, uint8_t *data,
                         //uint8_t dataLength, uint8_t duration);
 
  
};

#endif
