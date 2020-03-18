
/*
   demo.c 
   wade ryan
   3/17/2020

   Compile using:  

   $ gcc demo.c -lwiringPi -lwiringPiBME280rpi -o bme280

*/
#include <stdio.h>

#define BME280_ADDRESS                0x76

#include <bme280rpi.h>


int main() {

  int fd = wiringPiI2CSetup(BME280_ADDRESS);
  if(fd < 0) {
    printf("Device not found");
    return -1;
  }

  bme280_calib_data cal;
  bme280_raw_data raw;
  bme280_standardSetup(fd, &cal);

  bme280_getRawData(fd, &raw);
  int32_t t_fine = bme280_getTemperatureCalibration(&cal, raw.temperature);
  float t = bme280_compensateTemperature(t_fine); // C
  float p = bme280_compensatePressure(raw.pressure, &cal, t_fine) / 100; // hPa
  float h = bme280_compensateHumidity(raw.humidity, &cal, t_fine);       // %
  float a = bme280_getAltitude(p);                         // meters

  printf("{\"sensor\":\"bme280\", \"humidity\":%.2f, \"pressure\":%.2f,"
    " \"celsius\":%.2f, \"fahrenheit \":%.2f, \"altitude\":%.2f, \"timestamp\":%d}\n",
    h, p, t, t*9/5 +32, a, (int)time(NULL));

  return 0;
}

