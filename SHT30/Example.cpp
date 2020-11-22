#include "mbed.h"
#include "SHT30.h"


SHT30  sens1(I2C_SDA, I2C_SCL);
Serial pc(USBTX, USBRX);
//bool enableHeater = false;

int main() 
{ 


    while(1) {
        
    float t = sens1.readTemperature();
    float h = sens1.readHumidity();
  

    if (! isnan(t)) {  // check if 'is not a number'
    pc.printf("Temp *C: %.4f\r\n", t);
 
    } else { 
    pc.printf("Failed to read temperature\n");
    }
  
    if (! isnan(h)) {  // check if 'is not a number'

    pc.printf("Humidity percentage: %.4f\r\n", h);
 
    } else { 
    pc.printf("Failed to read humidity\n");
    }
   wait(5); 
}
}
