This library will retrieve temperature, humitidy, and pressure from a bme280 sensor.  

This library was forked from:  https://github.com/andreiva/raspberry-pi-bme280

Copyright (c) 2020 Wade Ryan


## Download

```
git clone https://github.com/wryan67/bme280_rpi_lib.git

```

## Dependencies
```
sudo apt-get install libi2c-dev i2c-tools wiringpi
```

## Installation
To compile and install this library, navigate into the src folder and use the make utility to compile 
and install the library.  Don't forget the sudo!
```
$ cd [project folder]
$ cd src
$ make && sudo make install
```

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
