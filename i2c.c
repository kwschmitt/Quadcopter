/* Includes */
#include <stdio.h>
#include "i2c.h"

/* Functions */
int checkI2Cbusy() {
    while ( ( SSP1CON2 & 0x1F ) || ( SSP1STATbits.R_W ) )
        continue; 
}

void starti2c() {
    checkI2Cbusy();
    SSP1CON2bits.SEN = 1;   
    checkI2Cbusy();
}

void writei2c( unsigned char data ) {
    checkI2Cbusy();
    SSP1BUF = data;
    while( SSP1STATbits.BF );   
	checkI2Cbusy();
}

unsigned char readi2c() {
  SSP1CON2bits.RCEN = 1;
  while ( !SSP1STATbits.BF );
  
  SSP1STATbits.BF = 0;
  PIR3bits.SSP1IF = 0;
  
  return ( SSP1BUF );  
}

void acki2c( void ) {
  SSP1CON2bits.ACKDT = 0;
  SSP1CON2bits.ACKEN = 1;
}

void nacki2c( void ) {
  SSP1CON2bits.ACKDT = 1;
  SSP1CON2bits.ACKEN = 1;
}

void stopi2c( void ) {
    SSP1CON2bits.PEN = 1;
}

void writei2cData( uint8_t address, uint8_t reg, uint8_t data ) {
    starti2c();
    writei2c( address );
    writei2c( reg );
    writei2c( data );
    stopi2c();
}

void readi2cData( uint8_t address, uint8_t reg, uint8_t* data, uint8_t len ) {    
    unsigned int i = 0;
    
    starti2c();
    writei2c(address & ~0x01);
    writei2c(reg);
    stopi2c();

    starti2c();    
    writei2c(address | 0x01);
   
    for ( i = 0; i < len-1; i++) {
        data[i] = readi2c();
        checkI2Cbusy();
        acki2c();
        checkI2Cbusy();
    }
    
    data[len-1] = readi2c();
    checkI2Cbusy();
    stopi2c();
}