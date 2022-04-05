This library will retrieve temperature, humitidy, and pressure from a bme280 sensor.  

This library was forked from:  https://github.com/andreiva/raspberry-pi-bme280

Copyright (c) 2020 Wade Ryan


## Download

```
git clone https://github.com/wryan67/bme280_rpi_lib.git
```

## Requirements
On your Raspberry Pi, please use the raspi-config program to enable the I2C interface.
Then use the gpio command to make sure your i2c devices can be found.  The default address 
for an BME280 chip is 0x76.  
```
$ sudo raspi-config
$ gpio i2cd
```

## Installation
To compile and install this library, navigate into the src folder and use the make utility to compile 
and install the library.  Don't forget the sudo!
```
$ cd [project folder]
$ cd src
$ make && sudo make install
```

## Prerequisites

    cd ~/projects
    sudo git clone git@github.com:wryan67/udd_rpi_lib.git
    cd udd_rpi_lib
    make install

## Compling
```
Complie your applications using these command line arguments: -lwiringPi -lwiringBME280rpi
```

## Demo
```
$ cd ../example
$ make 
$ ./bme280
{"sensor":"bme280", "humidity":34.86, "pressure":1008.16, "celsius":24.25, "fahrenheit ":75.65, "altitude":40.37, "timestamp":1584501597}
```
