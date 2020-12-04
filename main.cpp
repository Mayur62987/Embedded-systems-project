#include "mbed.h"
#include "DHT.h"
#include "BH1750.h"
#include "SHT30.h"
 #include "SHT21_ncleee.h"


DHT sensor(p14, DHT11);
BH1750  lightSensor(I2C_SDA, I2C_SCL);
Serial pc(USBTX, USBRX);
//SHT30  sens1(I2C_SDA, I2C_SCL);
AnalogIn Ain(p15);
I2C i2c2(I2C_SDA, I2C_SCL);
SHT21 groundSensor(&i2c2);

float h = 0.0f, c = 0.0f, dp = 0.0f, L = 0.0f, TS = 0.0f, HS = 0.0f;
float Rel_soilhum;

int main()
{  
    int error = 0;
    while(1) {
        wait(5.0f);
        error = sensor.readData();
        if (0 == error) {
            c   = sensor.ReadTemperature(CELCIUS);
            h   = sensor.ReadHumidity();
            dp  = sensor.CalcdewPoint(c, h);
            pc.printf("Surface Temperature *C: %4.2f\n", c);
            pc.printf("Surface Humidity is %4.2f\n", h);
            pc.printf("Surface Dewpoint: %4.2f\n",dp);
        } else {
            printf("Error: %d\n", error);
        }
    lightSensor.init(BH1750_ONE_TIME_HIGH_RES_MODE);    
    L = lightSensor.readIntesity();
    pc.printf("Light intensity: %.4f Lux\r\n",L);
    TS = groundSensor.readTemp();
    pc.printf("Temp *C: %.4f\r\n", TS);
    HS = groundSensor.readHumidity();
    pc.printf("Humidity percentage: %.4f\r\n", HS);
    //if (! isnan(TS)) {  // check if 'is not a number'
    //pc.printf("Temp *C: %.4f\r\n", TS);
    //} else { 
    //pc.printf("Failed to read soil temperature\n");
    //}
    //if (! isnan(HS)) {  // check if 'is not a number'
    //pc.printf("Humidity percentage: %.4f\r\n", HS);
    //} else { 
   // pc.printf("Failed to read soil humidity\n");
    //}
    int Raw = Ain.read_u16();
    Rel_soilhum =  ((abs(Raw-50124.0))/(50124-26342))*100.0f;
    pc.printf("Moisture data Raw: %d\r\n", Raw);
    pc.printf("Relative moisture percentage: %.4f \r\n", Rel_soilhum);
        
    }

}
