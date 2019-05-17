/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author Andrea Perez Huizar, ie698276@iteso.mx & Alvaro A. Rocha Robles, ie703585@iteso.mx
	\date	18/02/2019
*/

#include "MK64F12.h"
#include "GPIO.h"

static uint8_t flagPortC = FALSE;
static uint8_t flagPortA = FALSE;
static uint8_t flagPortB = FALSE;

void PORTA_IRQHandler()
{
	flagPortA = TRUE;
	GPIO_clear_interrupt(GPIO_A);
}

void PORTB_IRQHandler()
{
	flagPortB = TRUE;
	GPIO_clear_interrupt (GPIO_B);
}

void PORTC_IRQHandler()
{
	flagPortC = TRUE;
	GPIO_clear_interrupt(GPIO_C);
}

void GPIO_clear_interrupt_flag(gpio_port_name_t port_name)
{
	switch(port_name)
	{
		case GPIO_A:
			flagPortA = FALSE;
			break;
		case GPIO_B:
			flagPortB = FALSE;
			break;
		case GPIO_C:
			flagPortC = FALSE;
			break;
		default:
			break;
	}
}
uint8_t GPIO_get_interrupt_status(gpio_port_name_t port_name)
{
	uint8_t status = NULL;
	switch(port_name)
	{
		case GPIO_A:
			status = flagPortA;
			break;
		case GPIO_B:
			status = flagPortB;
			break;
		case GPIO_C:
			status = flagPortC;
			break;
		default:
			break;
	}

	GPIO_clear_interrupt_flag(port_name);
	return (status);
}
void GPIO_clear_interrupt(gpio_port_name_t portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR = CLEAR;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR = CLEAR;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = CLEAR;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR = CLEAR;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR = CLEAR;
			break;
	}
}

uint8_t GPIO_clock_gating(gpio_port_name_t port_name)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8_t GPIO_pin_control_register(gpio_port_name_t port_name, uint8_t pin,const gpio_pin_control_register_t*  pin_control_register)
{
	switch(port_name)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pin_control_register;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pin_control_register;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pin_control_register;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pin_control_register;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pin_control_register;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

/* Uses PDOR to write port*/
void GPIO_write_port(gpio_port_name_t port_name, uint32_t data)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
				{
					case GPIO_A: /** GPIO A is selected*/
						GPIOA->PDOR = data;
						break;
					case GPIO_B: /** GPIO B is selected*/
						GPIOB->PDOR = data;
						break;
					case GPIO_C: /** GPIO C is selected*/
						GPIOC->PDOR = data;
						break;
					case GPIO_D: /** GPIO D is selected*/
						GPIOD->PDOR = data;
						break;
					case GPIO_E: /** GPIO E is selected*/
						GPIOE->PDOR = data;
						break;
					default: /**If doesn't exist the option*/
						break;
				}// end switch
}

/* Uses PDIR to read port*/
uint32_t GPIO_read_port(gpio_port_name_t port_name)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					return GPIOA->PDIR;
					break;
				case GPIO_B: /** GPIO B is selected*/
					return GPIOB->PDIR;
					break;
				case GPIO_C: /** GPIO C is selected*/
					return GPIOC->PDIR;
					break;
				case GPIO_D: /** GPIO D is selected*/
					return GPIOD->PDIR;
					break;
				case GPIO_E: /** GPIO E is selected*/
					return GPIOE->PDIR;
					break;
				default:
					return(FALSE);/**If doesn't exist the option*/
					break;
			}// end switch
}

/* Uses PDIR to read pins */
uint8_t GPIO_read_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					return GPIOA->PDIR & (GPIO_SET_BIT << pin);
					break;
				case GPIO_B: /** GPIO B is selected*/
					return GPIOB->PDIR & (GPIO_SET_BIT << pin);
					break;
				case GPIO_C: /** GPIO C is selected*/
					return GPIOC->PDIR & (GPIO_SET_BIT << pin);
					break;
				case GPIO_D: /** GPIO D is selected*/
					return GPIOD->PDIR & (GPIO_SET_BIT << pin);
					break;
				case GPIO_E: /** GPIO E is selected*/
					return GPIOE->PDIR & (GPIO_SET_BIT << pin);
					break;
				default:
					return(FALSE);/**If doesn't exist the option*/
					break;
			}// end switch
}

/* Uses PSOR to set pins*/
void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					GPIOA->PSOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_B: /** GPIO B is selected*/
					GPIOB->PSOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_C: /** GPIO C is selected*/
					GPIOC->PSOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_D: /** GPIO D is selected*/
					GPIOD->PSOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PSOR |= (GPIO_SET_BIT << pin);
					break;
				default: /**If doesn't exist the option*/
					break;
			}// end switch
}

/* Uses PCOR to clear pins*/
void GPIO_clear_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					GPIOA->PCOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_B: /** GPIO B is selected*/
					GPIOB->PCOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_C: /** GPIO C is selected*/
					GPIOC->PCOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_D: /** GPIO D is selected*/
					GPIOD->PCOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PCOR |= (GPIO_SET_BIT << pin);
					break;
				default: /**If doesn't exist the option*/
					break;
			}// end switch
}

/*Uses PTOR to toggle pins*/
void GPIO_toogle_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					GPIOA->PTOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_B: /** GPIO B is selected*/
					GPIOB->PTOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_C: /** GPIO C is selected*/
					GPIOC->PTOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_D: /** GPIO D is selected*/
					GPIOD->PTOR |= (GPIO_SET_BIT << pin);
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PTOR |= (GPIO_SET_BIT << pin);
					break;
				default: /**If doesn't exist the option*/
					break;
			}// end switch
}

/* Uses PDDR to set port to output or input*/
void GPIO_data_direction_port(gpio_port_name_t port_name ,uint32_t direction)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					GPIOA->PDDR = direction;
					break;
				case GPIO_B: /** GPIO B is selected*/
					GPIOB->PDDR = direction;
					break;
				case GPIO_C: /** GPIO C is selected*/
					GPIOC->PDDR = direction;
					break;
				case GPIO_D: /** GPIO D is selected*/
					GPIOD->PDDR = direction;
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR = direction;
					break;
				default: /**If doesn't exist the option*/
					break;
			}// end switch
}

void GPIO_data_direction_pin(gpio_port_name_t port_name, uint8_t state, uint8_t pin)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					GPIOA->PDDR |= (state << pin);
					break;
				case GPIO_B: /** GPIO B is selected*/
					GPIOB->PDDR |= (state << pin);
					break;
				case GPIO_C: /** GPIO C is selected*/
					GPIOC->PDDR |= (state << pin);
					break;
				case GPIO_D: /** GPIO D is selected*/
					GPIOD->PDDR |= (state << pin);
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR |= (state << pin);
					break;
				default: /**If doesn't exist the option*/
					break;
			}// end switch
}
