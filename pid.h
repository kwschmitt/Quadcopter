/* 
 * File:   pid.h
 * Author: Kenny
 *
 * Created on July 6, 2017, 9:56 PM
 */

#ifndef PID_H
#define	PID_H

#ifdef	__cplusplus
extern "C" {
#endif

    /* Global Variables */
    float rollkp;
    float rollki;
    float rollkd;
    int rollAdj;
    float rollPreviousError;
    float rollIntegral;
    
    float pitchkp;
    float pitchki;
    float pitchkd;
    int pitchAdj;
    float pitchPreviousError;
    float pitchIntegral;
    
    float yawkp;
    float yawki;
    float yawkd;
    int yawAdj;
    float yawPreviousError;
    float yawIntegral;
    
    int throttle1 = 0;
    int throttle2 = 0;
    int throttle3 = 0;
    int throttle4 = 0;
    
    /* Function Prototypes */
    void pid_Init();
    void pid( float desiredRoll, float desiredPitch, float desiredYaw );
    void rollPid( float desiredRoll );
    void pitchPid( float desiredPitch );
    void yawPid( float desiredYaw );
    
#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

