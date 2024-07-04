 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mostafa Osama
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                        Type Declaration                                      *
 *******************************************************************************/

typedef enum
{
	NORMAL,DOUBLE
}UART_Speed;

typedef enum
{
	ASYNCH,SYNCH
}UART_Mood;

typedef enum
{
	DISAPLE,RESERVED,EVEN,ODD
}UART_Parity;

typedef enum
{
	ONE_BIT,TWO_BITS
}UART_Stop;

typedef enum
{
	FIVE_BITS,SIX_BITS,SEVEN_BITS,EIGHT_BITS
}UART_BitsNumber;

typedef struct
{
	UART_Speed speed;
	UART_Mood mood;
	UART_Parity paritySelect;
	UART_Stop stopBits;
	UART_BitsNumber numberOfBits;
}UART_Setup;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_Setup* UART_config,uint32 baud_rate);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
