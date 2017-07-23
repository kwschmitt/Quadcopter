/* Includes */
#include <stdio.h>
#include "sensors.h"
#include "i2c.h"

/* Functions */
void sensors_Init() {
    accel_Init();
    gyro_Init();
}

void accel_Init() {
    writei2cData( accelAdd, 0x20, 0x37 );
    writei2cData( accelAdd, 0x21, 0x00 );
    writei2cData( accelAdd, 0x22, 0x00 );
}

void gyro_Init() {
    writei2cData( gyroAdd, 0x20, 0xAF );
    writei2cData( gyroAdd, 0x23, 0x10 );
}

void readSensors() {
    readAccel();
    readGyro();
}

void readAccel() {
    // Declare variables
    uint8_t aData[6];
    
    // Get the data
    readi2cData( accelAdd, 0xA8, aData, 6 );

    // Compute the current acceleration
    ax = (float)((int)aData[0] | ((int)aData[1] << 8))/16;
    ay = (float)((int)aData[2] | ((int)aData[3] << 8))/16;
    az = (float)((int)aData[4] | ((int)aData[5] << 8))/16;
}

void readGyro() {
    // Declare variables   
    uint8_t gData[6];
    
    // Get the data
    readi2cData( gyroAdd, 0xA8, gData, 6 );
    
    // Combine bytes
    gx = (float)((int)gData[0] | ((int)gData[1] << 8));   
    gy = (float)((int)gData[2] | ((int)gData[3] << 8));
    gz = (float)((int)gData[4] | ((int)gData[5] << 8)); 
}