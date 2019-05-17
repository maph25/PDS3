/**
 * @file    P3.c
 * @brief   Application entry point.
 */

#include "stdint.h"
#include "NVIC.h"
#include "MCG.h"
#include "GPIO.h"
#include "DAC.h"
#include "MK64F12.h"
#include "bits.h"

#define CLK_FREQ 50000000
#define F_IRC_SLOW 32768
#define F_IRC_FAST 4000000
#define ENABLE_PLL 0x01
#define DISABLE_PLL 0x00
#define CRYS_OSC 0x01
#define POWER_LOW 0x00
#define IRC_SLOW 0x00
#define CLK0 0x00
#define PLL_DIV 25
#define PLL_MULT 30
#define RESOL_BIT 0x01
#define DISABLE_ADC 0x01F
#define AVERAGE_SAMPLE 0x03
#define INPUT 0x0C /*PORT B PIN 2*/
#define SAMPLE_TIME 0.025F
#define SYS_CLK 120000000

#define ALPHA 0.7F
#define ALPHA_2 0.357F
#define ALPHA_3 0.249F
#define OFFSET 0X77F
#define SAMPLES 25000U
#define ALPHA_SQRT 0.51F

uint8_t flag = FALSE;
void read(void);

int main(void) {
	/*MCG*/
	int mcg_clk;
	uint8_t mcg = 0;

	#ifndef PLL_DIRECT
		mcg_clk = fei_fbi(F_IRC_SLOW, IRC_SLOW); //64Hz
		mcg_clk = fbi_fbe(CLK_FREQ, POWER_LOW, CLK0); //97KHz
	#else
		mcg_clk = pll_init(CLK_FREQ, POWER_LOW, CLK0,PLL_DIV, PLL_MULT,ENABLE_PLL);
	#endif
		mcg = what_mcg_mode();
	/*End MCG*/

float adc_val;
uint16_t output;
int16_t n = 0;
float x[SAMPLES] = {0};
float y = 0;
int16_t echo1 = 2500;
int16_t echo2 = 5000;
int16_t echo3 = 7500;

/*Clock gating*/
GPIO_clock_gating(GPIO_B);

/*ADC*/
SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
ADC0->CFG1 |= ADC_CFG1_MODE(RESOL_BIT);
ADC0->SC1[0] |= DISABLE_ADC;
ADC0->SC3 |= ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVERAGE_SAMPLE);


/*DAC*/
ControlReg0 config0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK |DAC_C0_DACTRGSEL_MASK|DAC_C0_LPEN_MASK;
ControlReg1 config1 = NULL;
DAC_ClockGating();
DAC_init(&config0, &config1);
  	 while(1) {
  		 ADC0->SC1[0] = INPUT & ADC_SC1_ADCH_MASK;
  		 while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
  		 {

  		 }
  		 adc_val = (ADC0->R[0]) - OFFSET;
  		 x[n] = adc_val;
  		 y = (ALPHA_SQRT * x[echo1]) + (ALPHA_2 * x[echo2]) +(ALPHA_3 * x[echo3]) - (ALPHA * x[n]);
  		 y *= 0.5;
  		 y += OFFSET;
  		output = y;
  		if((80 < output) && (output < 4096))
		{
  			DAC_output(output);
		}

  		(SAMPLES < n) ? n = 0 : n++;
		(SAMPLES < echo1) ? echo1 = 0 : echo1++;
		(SAMPLES < echo2) ? echo2= 0 : echo2++;
		(SAMPLES < echo3) ? echo3 = 0 : echo3++;

    }
    return 0 ;
}
