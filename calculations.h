/* 
 * File:   calculations.h
 * Author: Kenny
 *
 * Created on July 3, 2017, 5:15 PM
 */

#ifndef CALCULATIONS_H
#define	CALCULATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /* Constants */
    float accelAlpha = .8;
    float gyroAlpha = .995;

    /* Global Variables */    
    float roll = 0;
    float pitch = 0;
    float yaw = 0;
    
    /* Function Prototypes */
    void computeRollPitch(void);
    
    float fastatan2( float x, float y );
    float maximum( float x, float y );
    float minimum( float x, float y );
    
#ifdef	__cplusplus
}
#endif

#endif	/* CALCULATIONS_H */

