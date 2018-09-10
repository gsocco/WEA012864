/*
 * init.c
 *
 *  Created on: 7 de set. de 2018
 *      Author: root
 */
#include "SI_C8051F300_Register_Enums.h"
#include "init.h"

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
   PCA0MD &= ~0x40;                       	// WDTE = 0 (clear watchdog timer
}

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// This routine initializes the system clock to use the internal 24.5MHz / 8
// oscillator as its clock source.  Also enables missing clock detector reset.
//
void SYSCLK_Init (void)
{
   OSCICN = 0x04;                         // configure internal oscillator for
                                          // its lowest frequency
   RSTSRC = 0x04;                         // enable missing clock detector
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Configure the Crossbar and GPIO ports.
// P0.2 - LED (push-pull)

void PORT_Init (void)
{
   XBR0     = 0x04;                       // skip P0.2 (LED) in crossbar pin
                                          // assignments
   XBR1     = 0x00;                       // no digital peripherals selected
   XBR2     = 0x40;                       // Enable crossbar and weak pull-ups
   P0MDOUT |= 0xF7;                       // enable LED as a push-pull output in P0.2 y P0.0, P0.1, P0.4, P0.5, P0.6 y P0.7 todas push pull
}

//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// Configure Timer2 to 16-bit auto-reload and generate an interrupt at
// interval specified by <counts> using SYSCLK/12 as its time base.
//
void Timer2_Init (S16 counts)
{
   TMR2CN  = 0x00;                        // Stop Timer2; Clear TF2;
                                          // use SYSCLK/12 as timebase
   CKCON  &= ~(CKCON_T2MH__BMASK |
               CKCON_T2ML__BMASK );       // Timer2 clocked based on TMR2CN_T2XCLK

   TMR2RL  = -counts;                     // Init reload values
   TMR2    = 0xffff;                      // set to reload immediately
   IE_ET2  = 1;                           // enable Timer2 interrupts
   TMR2CN_TR2 = 1;                        // start Timer2
}
