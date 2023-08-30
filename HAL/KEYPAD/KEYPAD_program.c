
#include <util/delay.h>
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "KEYPAD_interface.h"


u8 buttons_array[4][4] = {
		{ '7' , '8' , '9' , '%'},
		{ '4' , '5' , '6' , '*'},
		{ '1' , '2' , '3' , '-'},
		{ 'c' , '0' , '=' , '+'}
};
void KEYPAD_voidInit(void)
{
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin4,DIO_INPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin5,DIO_INPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin6,DIO_INPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin7,DIO_INPUT);

	
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin0,DIO_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin1,DIO_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin2,DIO_OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT,KEYPAD_Pin3,DIO_OUTPUT);
	
}

u8 KEYPAD_u8GetButtonPressed(void)
{

	u8 Local_u8RetVal = 255;

	for(u8 row = 0; row<4 ; row++ ){

		DIO_voidSetPinValue(KEYPAD_PORT,row,DIO_HIGH);

		for(u8 col = 4 ; col<8 ; col++ ){

			if (DIO_u8GetPinValue(KEYPAD_PORT, col) == DIO_HIGH){

				_delay_ms(40);
				while(DIO_u8GetPinValue(KEYPAD_PORT, col) == DIO_HIGH){
					asm("NOP");
				}
				Local_u8RetVal = buttons_array[row][col-4];
			}

		}

		DIO_voidSetPinValue(KEYPAD_PORT,0,DIO_LOW);
		DIO_voidSetPinValue(KEYPAD_PORT,1,DIO_LOW);
		DIO_voidSetPinValue(KEYPAD_PORT,2,DIO_LOW);
		DIO_voidSetPinValue(KEYPAD_PORT,3,DIO_LOW);

		if(Local_u8RetVal != 255){
			break;
		}

	}

	return Local_u8RetVal;
}
