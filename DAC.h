/*
 * DAC.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Andrea Perez Huizar, ie69876@iteso.mx
 */

#ifndef DAC_H_
#define DAC_H_

#include "MK64F12.h"
#include "bits.h"


/*Value equal to zero*/
#define NULL 0x00
/*Shift for high part*/
#define HIGH_SHIFT 0x08
/*Data low mask*/
#define DAC_DATL_MASK 0x00FF
/*Data high mask*/
#define DAC_DATH_MASK 0xFF00


/*DAC Configuration**/
typedef const uint8_t ControlReg0;
typedef const uint8_t ControlReg1;

/*DAC clockgating*/
void DAC_ClockGating(void);

/*DAC main configuration*/
void DAC_init(ControlReg0 *C0, ControlReg1 *C1);

/*DAC writes in output wanted signal*/
void DAC_output(uint16_t signal);



#endif /* DAC_H_ */
