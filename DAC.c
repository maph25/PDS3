/*
 * DAC.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Andrea Perez Huizar, ie69876@iteso.mx
 */

#include "DAC.h"

void DAC_ClockGating()
{
	/** Writes the clock gating bit for the DAC0**/
	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
}

/*Initial configuration for DAC*/
void DAC_init(ControlReg0 *C0, ControlReg1 *C1)
{
	/*Writes the configurations specified*/
	DAC0->C0 = *C0;
	DAC0->C1 = *C1;
}

void DAC_output(uint16_t signal)
{
	uint16_t high;
	/*Shift and mask needed for DAC HIGH*/
	high = ((DAC_DATH_MASK)&(signal)) >> HIGH_SHIFT;
	/*Output for DAC LOW*/
	DAC0->DAT[NULL].DATL = ((DAC_DATL_MASK & signal));
	/*Output for DAC HIGH*/
	DAC0->DAT[NULL].DATH = high;
}
