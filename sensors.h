/* 
 * File:   sensors.h
 * Author: Kenny
 *
 * Created on July 3, 2017, 5:10 PM
 */

#ifndef SENSORS_H
#define	SENSORS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /* Constants */
    #define accelAdd 0b00110010
    #define gyroAdd  0b11010110
    
    /* Global Variables */
    float ax;
    float ay;
    float az;
    
    float gx;
    float gy;
    float gz;
    
    /* Function Prototypes */
    void sensors_Init(void);
    void accel_Init(void);
    void gyro_Init(void);
    void readSensors(void);
    void readAccel(void);
    void readGyro(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SENSORS_H */

