#include "kalman.h"
#include "sensors.h"
#include "mcc_generated_files/eusart1.h"

/* Private Variables */
kalman_state axState;
kalman_state ayState;
kalman_state azState;
kalman_state gxState;
kalman_state gyState;
kalman_state gzState;

/* Functions */
void kalman_Init() {
        
    // Acceleration Data
    axState.x = ax;
    axState.p = 1;
    axState.q = .1;
    axState.r = 7.5;
    
    ayState.x = ay;
    ayState.p = 1;
    ayState.q = .1;
    ayState.r = 7.5;
    
    azState.x = az;
    azState.p =1;
    azState.q = .1;
    azState.r = 7.5;
    
    // Gyroscope Data
    gxState.x = gx;
    gxState.p = 1;
    gxState.q = .75;
    gxState.r = 5;
    
    gyState.x = gy;
    gyState.p = 1;
    gyState.q = .75;
    gyState.r = 5;
    
    gzState.x = gz;
    gzState.p = 1;
    gzState.q = .75;
    gzState.r = 5;
    
}

void kalmanUpdate( kalman_state* state, float measurement ) {
    //prediction update
    //omit x = x
    state->p = state->p + state->q;

    //measurement update
    state->k = state->p / (state->p + state->r);
    state->x = state->x + state->k * (measurement - state->x);
    state->p = (1 - state->k) * state->p;
}

void filterData( void ) {
    kalmanUpdate(&axState, ax);
    kalmanUpdate(&ayState, ay);
    kalmanUpdate(&azState, az);
    kalmanUpdate(&gxState, gx);
    kalmanUpdate(&gyState, gy);
    kalmanUpdate(&gzState, gz);

    ax = axState.x;
    ay = ayState.x;
    az = azState.x;
   
    gx = gxState.x;    
    gy = gyState.x;
    gz = gzState.x;
}