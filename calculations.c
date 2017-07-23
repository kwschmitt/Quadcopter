/* Includes */
#include <stdio.h>
#include <math.h>
#include "calculations.h"
#include "sensors.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/tmr2.h"

/* Private Variables */
float rollAcc = 0;
float pitchAcc = 0;  
    
/* Functions */
void computeRollPitch() {
    // Find the time that has past
    TMR0_StopTimer();
    uint16_t tmr0val = TMR0_Read16bitTimer();
    float dt = ((float)tmr0val) * .0000001666667;
    
    // Calculate the roll from the accelerometer and gyro
    rollAcc = rollAcc * (accelAlpha) + fastatan2(-ay, az)*(1-accelAlpha);    
    roll -= (gx*.0175) * dt;

    if (accCounter >= 20) {
        accCounter = 0;
        roll = roll*gyroAlpha + rollAcc*(1-gyroAlpha);
    }
    
    // Reset the timer
    TMR0_Write16bitTimer(0);
    TMR0_StartTimer();
}

float fastatan2( float x, float y ) {
    float a;
    float s;
    float r;
    
    a = minimum( fabs(x), fabs(y) ) / maximum( fabs(x), fabs(y) );
    s = a*a;
    r = ((-0.0464964749 * s + 0.15931422) * s - 0.327622764) * s * a + a;
    
    if ( fabs(y) > fabs(x) ) {
        r = 1.57079637 - r;
    }
    if ( x < 0 ) {
        r = 3.14159274 - r;
    }
    if ( y < 0 ) {
        r = -r;
    }
    
    r = (r * 180.0)/3.14159;
    r = -r + 90;
    
    return r;
}

float maximum( float x, float y ) {
    if ( x > y ) {
        return x;
    } else {
        return y;
    }
}

float minimum( float x, float y ) {
    if ( x < y ) {
        return x;
    } else {
        return y;
    }
}