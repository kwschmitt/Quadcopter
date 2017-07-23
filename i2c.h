/* 
 * File:   i2c.h
 * Author: Kenny
 *
 * Created on July 3, 2017, 7:40 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
    /* Includes */
    #include "mcc_generated_files/i2c1.h"
    
    /* Private Variables */
    
    /* Function prototypes */
    int checkI2Cbusy( void );
    void starti2c( void );
    void writei2c(unsigned char data);
    unsigned char readi2c( void );
    void acki2c( void );
    void nacki2c( void );
    void stopi2c( void );
    void writei2cData( uint8_t address, uint8_t reg, uint8_t data );
    void readi2cData( uint8_t address, uint8_t reg, uint8_t* data, uint8_t len );

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

