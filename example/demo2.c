/*
   demo.c 
   wade ryan
   3/17/2020

   Compile using:  

   $ gcc demo2.c -lwiringPi -lwiringPiBME280rpi -o demo2

*/
#include <stdio.h>
#include <wiringPi.h>
#include <bme280rpi.h>

bme280_calib_data cal[2];
int bme280_address[2] = { 0x76, 0x77 };
int bme280_fd[2]; 


int main() {
  bme280_raw_data raw[2];

  int32_t t_fine[2];
  float t[2];
  float p[2];
  float h[2];
  float a[2];



  for (int i=0;i<2;++i) {
    bme280_fd[i] = bme280_standardSetup(bme280_address[i], &cal[i]);
    if(bme280_fd[i] < 0) {
      fprintf(stderr, "device not found at address %02x\n",bme280_address[i]);
      return -1;
    }
  }
  

  
  while (1) { 
    for (int i=0;i<2;++i) {
      bme280_getRawData(bme280_fd[i], &raw[i]);

      t_fine[i] = bme280_getTemperatureCalibration(&cal[i], raw[i].temperature);
      t[i] = bme280_compensateTemperature(t_fine[i]); // C
      p[i] = bme280_compensatePressure(raw[i].pressure, &cal[i], t_fine[i]) / 100; // hPa
      h[i] = bme280_compensateHumidity(raw[i].humidity, &cal[i], t_fine[i]);       // %
      a[i] = bme280_getAltitude(p[i]);                         // meters
    }
    for (int i=0;i<2;++i) {
      printf("{\"sensor[0x%02x]\":\"bme280\", \"humidity\":%.2f, \"pressure\":%.2f,"
      " \"celsius\":%.2f, \"fahrenheit \":%.2f, \"altitude\":%.2f, \"timestamp\":%d}\n",
        bme280_address[i], h[i], p[i], t[i], t[i]*9/5 +32, a[i], (int)time(NULL));
    }
    printf("\n");

    delay(500);
  }
 
  return 0;
}


