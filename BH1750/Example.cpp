#include "mbed.h"
#include "BH1750.h"


BH1750  lightSensor(I2C_SDA, I2C_SCL);
Serial pc(USBTX, USBRX);


int main() 
{
   lightSensor.init();

   while(1) {
       pc.printf("Light intensity: %.4f Lux\r\n", lightSensor.readIntesity());
       wait(1);
   }
}
