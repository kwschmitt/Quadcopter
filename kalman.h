/* 
 * File:   kalman.h
 * Author: Kenny
 *
 * Created on July 21, 2017, 10:08 PM
 */

#ifndef KALMAN_H
#define	KALMAN_H

#ifdef	__cplusplus
extern "C" {
#endif  
        
    /* Public Datatypes */
    typedef struct {
        float q; //process noise covariance
        float r; //measurement noise covariance
        float x; //value
        float p; //estimation error covariance
        float k; //kalman gain
    } kalman_state;

    /* Function Prototypes */
    void kalman_Init(void);
    void kalmanUpdate(kalman_state* state, float measurement);
    void filterData(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* KALMAN_H */