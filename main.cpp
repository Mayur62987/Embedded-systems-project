#include "mbed.h"
#include "BH1750.h"
#include "SHT30.h"

AnalogIn Ain(p15);
BH1750  lightSensor(I2C_SDA, I2C_SCL);
SHT30  sens1(I2C_SDA, I2C_SCL);
Serial pc(USBTX, USBRX);

int main() {
    
    float Rel_hum;
    int Raw = Ain.read_u16();
    lightSensor.init();
    while(1) 
    {    
    float T = sens1.readTemperature();
    float H = sens1.readHumidity();
    float L = lightSensor.readIntesity();
    int Raw = Ain.read_u16();
    Rel_hum =  ((abs(Raw-50124.0))/(50124-26342))*100.0f;
    pc.printf("Moisture data Raw: %d \r\n", Raw);
    pc.printf("Relative humidity: %.4f  \r\n", Rel_hum);
   
    if (! isnan(T)) {  // check if 'is not a number'
    pc.printf("Temp *C: %.4f\r\n", T);
 
    } else { 
    pc.printf("Failed to read temperature\n");
    }
  
    if (! isnan(H)) {  // check if 'is not a number'

    pc.printf("Humidity percentage: %.4f\r\n", H);
 
    } else { 
    pc.printf("Failed to read humidity\n");
    }
    
   pc.printf("Light intensity: %.4f Lux\r\n",L);
   wait(1); 
    
    
    }
}
