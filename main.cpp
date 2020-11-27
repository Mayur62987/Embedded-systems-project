#include "mbed.h"
#include "DHT.h"
#include "BH1750.h"
#include "SHT30.h"
  
Serial pc(USBTX, USBRX);
DHT sensor(p14,DHT11);
AnalogIn Ain(p15);
SHT30  sens1(I2C_SDA, I2C_SCL);
BH1750  lightSensor(I2C_SDA, I2C_SCL);

  
  int main() {
      int err;
      //float surftemp;
      //float surfhumi;
      float Rel_hum;
      int Raw = Ain.read_u16();
      wait(1);
      
      while(1)
      {
      err = sensor.readData();    
      //surftemp = sensor.ReadTemperature(CELCIUS);
     // surfhumi = sensor.ReadHumidity();
        if (err == 0) {
            printf("Temperature is %4.2f C \r\n",sensor.ReadTemperature(CELCIUS));
            printf("Humidity is %4.2f \r\n",sensor.ReadHumidity());
           // printf("Dew point is %4.2f  \r\n",sensor.CalcdewPoint(sensor.ReadTemperature(CELCIUS), sensor.ReadHumidity()));
            printf("Dew point (fast) is %4.2f  \r\n",sensor.CalcdewPointFast(sensor.ReadTemperature(CELCIUS), sensor.ReadHumidity()));
        } else
            printf("\r\nErr %i \n",err);
          wait(5);
      float TS = sens1.readTemperature();
      float HS = sens1.readHumidity();
      lightSensor.init(BH1750_ONE_TIME_HIGH_RES_MODE);
      float L = lightSensor.readIntesity();
    //int T = dht.getCelsius();
    //int H = dht.getHumidity();
    
      int Raw = Ain.read_u16();
      Rel_hum =  ((abs(Raw-50124.0))/(50124-26342))*100.0f;
      pc.printf("Moisture data Raw: %d \r\n", Raw);
      pc.printf("Relative humidity: %.4f  \r\n", Rel_hum);
   
    if (! isnan(TS)) {  // check if 'is not a number'
       pc.printf("Temp *C: %.4f\r\n", TS);
 
    } 
    else { 
    pc.printf("Failed to read temperature\n");
    }
  
    if (! isnan(HS)) {  // check if 'is not a number'

    pc.printf("Humidity percentage: %.4f\r\n", HS);
 
    } else 
    { 
    pc.printf("Failed to read humidity\n");
    }
    pc.printf("Light intensity: %.4f Lux\r\n",L);

      }
      }
