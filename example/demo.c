
/*
   demo.c 
   wade ryan
   3/17/2020

   Compile using:  

   $ gcc demo.c -lwiringPi -lwiringPiBME280rpi -o bme280

*/
#include <stdio.h>
#include <wiringPi.h>
#include <bme280rpi.h>

bme280_calib_data cal;
int bme280_address = 0x76;
int bme280_fd; 


int main() {
  bme280_raw_data raw;

  bme280_fd = bme280_standardSetup(bme280_address, &cal);
  if(bme280_fd < 0) {
    fprintf(stderr, "device not found at address %02x\n",bme280_address);
    return -1;
  }

  
  while (1) {

    bme280_getRawData(bme280_fd, &raw);
    int32_t t_fine = bme280_getTemperatureCalibration(&cal, raw.temperature);
    float t = bme280_compensateTemperature(t_fine); // C
    float p = bme280_compensatePressure(raw.pressure, &cal, t_fine) / 100; // hPa
    float h = bme280_compensateHumidity(raw.humidity, &cal, t_fine);       // %
    float a = bme280_getAltitude(p);                         // meters

    printf("{\"sensor\":\"bme280\", \"humidity\":%.2f, \"pressure\":%.2f,"
      " \"celsius\":%.2f, \"fahrenheit \":%.2f, \"altitude\":%.2f, \"timestamp\":%d}\n",
      h, p, t, t*9/5 +32, a, (int)time(NULL));

    delay(500);
  }
 
  return 0;
}

