/* Includes */
#include "pid.h"
#include "calculations.h"
#include "sensors.h"
#include "stdio.h"

/* Functions */
void pid_Init() {
    rollkp = 0;
    rollki = 0;
    rollkd = 0;
    rollPreviousError = 0;
    rollIntegral = 0;
    
    pitchkp = 0;
    pitchki = 0;
    pitchkd = 0;
    pitchPreviousError = 0;
    pitchIntegral = 0;
    
    yawkp = 0;
    yawki = 0;
    yawkd = 0; 
    yawPreviousError = 0;
    yawIntegral = 0;
}

void pid( float desiredRoll, float desiredPitch, float desiredYaw ) {
    // Do pid on each axis
    rollPid( desiredRoll );
    pitchPid( desiredPitch );
    yawPid( desiredYaw );
    
    // Adjust each throttle
    extern int throttle;
    throttle1 = throttle - rollAdj;
    throttle2 = throttle + rollAdj;
    throttle3 = throttle + rollAdj;
    throttle4 = throttle - rollAdj;
    
    // Check boundaries
    if ( throttle1 < 0 ) {
        throttle1 = 0;
        throttle4 = 0;
    }
    if ( throttle1 > 300 ) {
        throttle1 = 300;
        throttle4 = 300;
    }
    
    if ( throttle2 < 0 ) {
        throttle2 = 0;
        throttle3 = 0;
    }
    if ( throttle2 > 300 ) {
        throttle2 = 300;
        throttle3 = 300;
    }
}

void rollPid( float desiredRoll ) {
    // Declare variables
    float rollError;
    float changeInError;

    // Find the P.I.D terms
    rollError = desiredRoll - roll;
    changeInError = rollPreviousError - rollError;
    rollIntegral += rollError;
    
    // Calculate the adjustment
    rollAdj = (int)((rollkp*rollError) - (rollkd*changeInError) + (rollki * rollIntegral));

    // Update previous error
    rollPreviousError = rollError;
}

void pitchPid( float desiredPitch ) {
    
}

void yawPid( float desiredYaw ) {
    
}
