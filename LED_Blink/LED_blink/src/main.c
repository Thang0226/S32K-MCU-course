/* Copyright 2023 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

#include <stdio.h>
#include <stdint.h>

#if defined (__ghs__)
    #define __INTERRUPT_SVC  __interrupt
    #define __NO_RETURN _Pragma("ghs nowarning 111")
#elif defined (__ICCARM__)
    #define __INTERRUPT_SVC  __svc
    #define __NO_RETURN _Pragma("diag_suppress=Pe111")
#elif defined (__GNUC__)
    #define __INTERRUPT_SVC  __attribute__ ((interrupt ("SVC")))
    #define __NO_RETURN
#else
    #define __INTERRUPT_SVC
    #define __NO_RETURN
#endif

//0. Write delay(ms) function
void delay_ms (int ms);

int counter, accumulator = 0, limit_value = 1000000;

int main(void) {

	//1. Configure clock for GPIOD
	IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;	// bit 30 = 1

	//2. Configure PTD0, PTD15, PTD16 as GPIOs (Configure use IP_PORTx, Data use IP_PTx)
	IP_PORTD->PCR[0]  = PORT_PCR_MUX(1);
	IP_PORTD->PCR[15] = PORT_PCR_MUX(1);
	IP_PORTD->PCR[16] = PORT_PCR_MUX(1);

	/* Set pins as output */
	IP_PTD->PDDR |= (1 << 0) | (1 << 15) | (1 << 16);

	/* Turn off LEDs */
	IP_PTD->PSOR |= (1 << 0) | (1 << 15) | (1 << 16);

	//3. Write logic for controlling 3 LEDs
	while (1)
	{
		// Red
		IP_PTD->PCOR |= (1 << 0);	// Clear output pin to 0 (LED on when 0)
		delay_ms(3000);
		IP_PTD->PSOR |= (1 << 0);	// Set output pin to 1 (LED off when 1)

		// Green
		IP_PTD->PCOR |= (1 << 16);
		delay_ms(3000);
		IP_PTD->PSOR |= (1 << 16);

		// Blue
		IP_PTD->PCOR |= (1 << 15);
		delay_ms(3000);
		IP_PTD->PSOR |= (1 << 15);
	}

    return 0;
}

__INTERRUPT_SVC void SVC_Handler() {
    accumulator += counter;
    printf("counter is 0x%08x, accumulator is 0x%08x\n", counter, accumulator);
}



void delay_ms(int ms) {		// default 48MHz --> 1ms = loop 48000 times?
    for (int i = 0; i < ms; i++) {
    	int count = 48000;
        while (--count > 0);
    }
}
