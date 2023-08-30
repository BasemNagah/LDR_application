/*
 * main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	u32 ReadValue 		;
	u32 Real_Value		;
	u32 New_Value = 0	;
	ADC_Conf_t  LDR_VALUE = { ADC_AVCC ,ADC_FCPU_64};
	ADC_voidInit(&LDR_VALUE);
	ADC_voidChooseTrigSrc(ADC_FREE_RUNNING_MODE);

	CLCD_voidInit();

	u8 Hamok4a_morning[]= { 0x0E , 0x0E , 0x04 , 0x15 , 0x0E , 0x04 , 0x0E , 0x11 } ;
	u8 Hamok4a_night  []= { 0x00 , 0x00 , 0x00 , 0x00 , 0x18 , 0x1F , 0x1F , 0x00 } ;
	u8 Hamok4a_night2 []= { 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x1F , 0x1F , 0x00 } ;


	while(1)
	{
		ReadValue = ADC_u16SynchReadChannel(ADC_SINGLE_ENDED_0);
		Real_Value = (ReadValue*5000)/1024 ;
		Real_Value = Real_Value/1000 ;

		if (New_Value != Real_Value ){
			if(Real_Value >= 3 )
			{
				///morning
				CLCD_voidSendCommand(0x01);
				CLCD_voidSendString((u8*)"Good Morning" , 13);
				CLCD_voidCreateAndDispNew( 0 , Hamok4a_morning , 2 , 7 );
			}
			else
			{
				///night
				CLCD_voidSendCommand(0x01);
				CLCD_voidSendString((u8*)"Good Night" , 12);
				CLCD_voidCreateAndDispNew( 1 , Hamok4a_night  , 2 , 2 );
				CLCD_voidCreateAndDispNew( 2 , Hamok4a_night2 , 2 , 3 );
			}
			New_Value = Real_Value ;
		}
	}


	return 0 ;
}

