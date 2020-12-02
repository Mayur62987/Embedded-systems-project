#include "SHT30.h"

SHT30::SHT30(PinName sda, PinName scl) : i2c(sda,scl) 
{
     humidity = NAN;
     temp = NAN;
     i2c.frequency(400000);

}

uint16_t SHT30::readStatus(void) {
    writeCommand(SHT30_READSTATUS);
   
    char data[3];
    i2c.read((0x44 << 1), data, 3, false);
    uint16_t stat = data[0];
    stat <<= 8;
    stat |= data[1];
    //Serial.println(stat, HEX);
   return stat;
}

void SHT30::reset(void) {
   writeCommand(SHT30_SOFTRESET);
   wait_ms(10);
}

bool SHT30::writeCommand(uint16_t command) {
  //uint8_t cmd[2];
  char cmd[2];
  cmd[0] = command >> 8; //shifts the uint16 by 8bytes
  cmd[1] = command & 0xFF; //masks the variable so it leaves only the value in the last 8 bits, and ignores all the rest of the bits
return i2c.write((0x44 << 1), cmd, 2, false);
}

void SHT30::heater(bool h) {
  if (h)
  writeCommand(SHT30_HEATEREN);
  else
  writeCommand(SHT30_HEATERDIS);
  wait_ms(1);
}

bool SHT30::isHeaterEnabled() 
{
 uint16_t regValue = readStatus();
 return (bool)bitRead(regValue, SHT30_REG_HEATER_BIT);
}

float SHT30::readTemperature(void) {
  if (!readTempHum())
    return NAN;

  return temp;
}

float SHT30::readHumidity(void) {
  if (!readTempHum())
    return NAN;

  return humidity;
}

/*static uint8_t crc8(const char *data, int len) {
   /*
   *
   * CRC-8 formula from page 14 of SHT spec pdf
   *
   * Test data 0xBE, 0xEF should yield 0x92
   *
   * Initialization data 0xFF
   * Polynomial 0x31 (x8 + x5 +x4 +1)
   * Final XOR 0x00
   */

  /*const char POLYNOMIAL(0x31);
  char crc(0xFF);

  for (int j = len; j; --j) {
    crc ^= *data++;

    for (int i = 8; i; --i) {
    crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
 }
  return crc;
}


uint8_t SHT30::crc8(char *data, uint8_t len)
{
  // adapted from SHT21 sample code from
  // http://www.sensirion.com/en/products/humidity-temperature/download-center/

  uint8_t crc = 0xff;
  uint8_t byteCtr;
  for (byteCtr = 0; byteCtr < len; ++byteCtr) {
    crc ^= data[byteCtr];
    for (uint8_t bit = 8; bit > 0; --bit) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x31;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}*/

char SHT30::readbuffer[6];  
bool SHT30::readTempHum(void) {
  
  writeCommand(SHT30_MEAS_HIGHREP);
  //char cmd[2];

  //cmd[0] = SHT30_MEAS_HIGHREP_STRETCH >> 8; //shifts the uint16 by 8bytes
  //cmd[1] = SHT30_MEAS_HIGHREP_STRETCH & 0xFF; //masks the variable so it leaves only the value in the last 8 bits, and ignores all the rest of the bits 
   
   
   i2c.read((0x44 << 1), readbuffer, 6, false);
  
    //char config[2] = {0};
    //config[0] = 0x2C;
    //config[1] = 0x06;
   // i2c.write((0x44 << 1), config, 2);
    //wait_ms(500);
    
    //char readdata[6] = {0};
    //i2c.read(0x44, readdata, 6);
    //int tempi = (readdata[0] * 256 + readdata[1]);
    //temp = -45 + (175 * tempi / 65535.0);
    //int humi = (readdata[3] * 256 + readdata[4]);
    //humidity = 100 * (humi / 65535.0);
   
  
  //if (readbuffer[2] != crc8(readbuffer, 2) ||
      //readbuffer[5] != crc8(readbuffer + 3, 2))
  //return false;

   int32_t stemp = (int32_t)(((uint32_t)readbuffer[0] << 8) | readbuffer[1]);
  // simplified (65536 instead of 65535) integer version of:
  //temp = (stemp * 175.0f) / 65535.0f - 45.0f;
   stemp = ((4375 * stemp) >> 14) - 4500;
   temp = (float)stemp / 100.0f;
   //temp = -45 + 175 * ((((readbuffer[0]) + readbuffer[1] * 256)) / 65535.0);
  // temp = -45 + 175 * (((DataBuffer[0]<< 8)| DataBuffer[1])/65535.0);
   //char data1 = readbuffer[0];
   //char data2 = readbuffer[1];
    
  uint32_t shum = ((uint32_t)readbuffer[3] << 8) | readbuffer[4];
  // simplified (65536 instead of 65535) integer version of:
  //humidity = (shum * 100.0f) / 65535.0f;
  shum = (625 * shum) >> 12;
  humidity = (float)shum / 100.0f;
   //humidity = 100 * ((((readbuffer[3] * 256) + readbuffer[4])) / 65535.0);
  // humidity = 100 * (((DataBuffer[3] << 8)| DataBuffer[4])/65535.0);
  //unsigned short val1;
  //unsigned short val2;
   
  
  //val1 = (readbuffer[0] << 8) + readbuffer[1];
  //temp = -45 + 175 * (val1/65535.0);
  
  
  //val2 = (readbuffer[3] << 8) + readbuffer[4];
 //humidity = 100 * (val2/65535.0);
  
 
  return true;
}
 //status = i2c.write(BH1750_I2CADDR, data, sizeof(data), false);
    //read (int address, char *data, int length, bool repeated=false)
    //write (int address, const char *data, int length, bool repeated=false)







