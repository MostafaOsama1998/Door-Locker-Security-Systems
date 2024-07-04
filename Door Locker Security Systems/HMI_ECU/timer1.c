/******************************************************************************
 *
 * Module: timer1
 *
 * File Name: timer1.c
 *
 * Description: the timer1 implementation of MC2
 *
 * Author: Mostafa Osama
 *
 *******************************************************************************/

#include "timer1.h"
#include <avr/interrupt.h>
#include "common_macros.h"
#include "avr/io.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/*******************************************************************************
	 * COM1A1:0 : Compare Output Mode for Compare unit A
	 * COM1B1:0 :Compare Output Mode for Compare unit B
	 * FOC1A: Force Output Compare for Compare unit A
	 * FOC1B: Force Output Compare for Compare unit B
	 * WGM11:0: Waveform Generation Mode
	*******************************************************************************/
	TCCR1A =0;

	TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	 /******************************************************************************
	  * ICNC1: Input Capture Noise Canceler
	  * ICES1: Input Capture Edge Select
	  * WGM13:2: Waveform Generation Mode
	  * CS12:0: Clock Select
	  *******************************************************************************/
	TCCR1B = 0;

	TCCR1B |= ((Config_Ptr->prescaler)<<CS10);

	TCCR1B |= ((Config_Ptr->mode)<<WGM12);

	TCNT1 = Config_Ptr->initial_value;

	OCR1A = Config_Ptr->compare_value;

	if(Config_Ptr->mode == COMPARE)
	{
		SET_BIT(TIMSK,OCIE1A);
	}
	else
	{
		SET_BIT(TIMSK,TOIE1);
	}
}

void Timer1_deInit(void)
{
	TCCR1A =0;

	TCCR1B = 0;

	CLEAR_BIT(TIMSK,OCIE1A);

	CLEAR_BIT(TIMSK,TOIE1);
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
