//-----------------------------------------------------------------------------
// F30x_Blinky.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Tomando el ejemplo de parpadeo de led de la placa de C8051F30x, que hace encender el led 5
// veces por segundo usando el interrupt handler del Timer2, agregamos la rutinas para manejar
// El display OLED de Winstar WEA012864
// Este display tiene una interfaz SPI que está implementada por SW.
// Se imprime un mensaje de texto y se muestran 5 imágenes
//
//
// How To Test:
// ------------
// 1) Ensure shorting blocks are place on the following:
//    - J3: P0.2 - P0.2_LED
// 2) Connect the USB Debug Adapter to J4.
// 3) Connect the 9V power adapter to P1.
// 4) Compile and download code to a 'F300 device on a C8051F300-TB development
//    board selecting Run -> Debug from the menus, clicking the Debug button in
//    the quick menu, or pressing F11.
// 5) Run the code by selecting Run -> Resume from the menus, clicking the
//    Resume button in the quick menu, or pressing F8.
// 6) The LED should blink at 5 Hz.
//
// Target:         C8051F30x
// Tool chain:     Simplicity Studio / Keil C51 9.51
// Command Line:   None
//
// Release 1.1 (BL)
//    - Updated Description / How to Test
//    - Replaced C51 code with compiler agnostic code
//    - 09 JAN 2014
//
// Release 1.0
//    -Initial Revision BW
//    -11-Oct-01
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "SI_C8051F300_Register_Enums.h"
#include "init.h"
#include "wea012864.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK       24500000 / 8          	// SYSCLK frequency in Hz

SBIT (LED, SFR_P0, 2);                     	// LED='1' means ON

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
INTERRUPT_PROTO(Timer2_ISR, TIMER2_IRQn);
void SYSCLK_Init (void);
void PORT_Init (void);
void Timer2_Init (S16 counts);

void uDelay(unsigned char);
void delay(unsigned char);

// RPI
const char str[]={"*HOLA*"};
const char str_Winstar[]={"WINSTAR"};
const char str_Electro[]={"ELECTROCOMPONENTES"};


extern unsigned char code picture4[8][128];
extern unsigned char code picture5[8][128];
extern unsigned char code picture6[8][128];
extern unsigned char code picture7[8][128];
extern unsigned char code Winstar[8][128];



 
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {

	SYSCLK_Init ();                        	// Initialize system clock to 24.5MHz
	PORT_Init ();                          	// Initialize crossbar and GPIO
	Timer2_Init (SYSCLK / 12 / 10);        	// Init Timer2 to generate interrupts at a 10Hz rate.

	Initial_SSD1306BZ();					// Inicializa display

	IE_EA = 1;                             	// enable global interrupts

    while (1) {                            	// spin forever
    	///*	DEMO
    	clean();
    	delay(100);

    	write_Word(str_Electro);	// Escribe un texto
    	delay(75);

    	show_pic(&picture4[0]);
    	delay(75);

    	show_pic(&picture5[0]);
    	delay(75);

    	show_pic(&picture6[0]);
    	delay(75);

    	show_pic(&picture7[0]);
    	delay(75);

    	show_pic(&Winstar[0]);
    	delay(75);
   }
}




//-------------------------------------------------
//     uDelay
//-------------------------------------------------
// Delay us
void uDelay(unsigned char l)
{
	while(l--);
}

//-------------------------------------------------
//     delay
//-------------------------------------------------
// Delay ms
void delay(unsigned char coun)
{
	unsigned char i,j,k;

	for(k = 0 ;k<coun;k++)
	{
		for(j = 0 ;j<150;j++)
		{
			for(i = 0 ;i< 200;i++)
			{}
		}
	}
}



//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer2_ISR
//-----------------------------------------------------------------------------
// This routine changes the state of the LED whenever Timer2 overflows.
//
INTERRUPT(Timer2_ISR, TIMER2_IRQn)
{
   TMR2CN_TF2H = 0;                       // clear Timer2 interrupt flag
   LED = ~LED;                            // change state of LED
}





//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
