/* Includes */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sensors.h"
#include "kalman.h"
#include "calculations.h"
#include "pid.h"
#include "mcc_generated_files/mcc.h"

/* Global Variables*/
int throttle = 0; /* 0 - 300 - can go up to 375 */

/* Function Prototypes */
void interrupt_Init(void);
void unlockI2C(void);

/* Functions */
void main(void)
{
    char c;
    int show = 0;
    
    // Unlock i2c bus
    unlockI2C();
    
    // Initialize the device
    SYSTEM_Initialize();
    interrupt_Init();
    sensors_Init();
    kalman_Init();
    pid_Init();
    TRISBbits.TRISB4 = 0;
    
    // Wait for 5 seconds to start
    while ( !begin ) {readSensors(); filterData(); computeRollPitch();}
    
    // Main loop
    while (1)
    {
        readSensors();
        filterData();
        computeRollPitch();    
        pid( -5.7, 0, 0 );
        
        if ( PIR3bits.RC1IF ) {
            c = EUSART1_Read(); 
        
            switch(c){
                case 'q':rollkp+=.01; break;
                case 'a':rollkp-=.01; break;
                case 'w':rollkd+=.05; break;
                case 's':rollkd-=.05; break;
                case 'e':rollki+=.001; break;
                case 'd':rollki-=.001; break;
                
                case 't':throttle+=2; break;
                case 'g':throttle-=2; break;
                                
                case 'z':show^=1; break;
                
                default: break;
            }
            printf( "kp: %.2f   kd: %.2f   ki: %.3f   throttle: %i \n\r", rollkp, rollkd, rollki, throttle );
        }
        if (show) {
            float val = roll*100;
            EUSART1_Write(0xAA);    
            EUSART1_Write(((int)(gx))>>8);
            EUSART1_Write(((int)(gx)));
            EUSART1_Write(((int)(val))>>8);
            EUSART1_Write((int)(val));
            
        }
        
        LATBbits.LATB4 ^= 1;
    }
}

void interrupt_Init() {
    // Turn on global interrupts
    INTCONbits.GIE = 1;
    
    // Turn on peripheral interrupts
    INTCONbits.PEIE = 1;
}

void unlockI2C(void) {
    unsigned int i = 0;
    TRISCbits.TRISC3 = 0;
    for ( i = 0; i < 40; i++ ) {
        LATCbits.LATC3 ^= 1;
        __delay_ms(10);
    }
}