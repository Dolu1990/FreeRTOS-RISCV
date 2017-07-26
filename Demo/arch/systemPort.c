/*
 * systemPort.c
 *
 *  Created on: Jul 24, 2017
 *      Author: spinalvm
 */


#import "../conf/FreeRTOSConfig.h"
#define mtime ((volatile uint64_t*)0xF00FFF40u)
#define mtime32 ((volatile uint32_t*) mtime)
#define timecmp ((volatile uint64_t*)0xF00FFF48u)

/*-----------------------------------------------------------*/

/* Sets the next timer interrupt
 */
void prvSetNextTimerInterrupt(void)
{
	uint32_t mtimeHigh, mtimeLow;

	//Get 64 bits mtime value via 32 bits access
	do{
		mtimeHigh = mtime32[1];
		mtimeLow = mtime32[0];
	}while(mtimeHigh != mtime32[1]);

	*timecmp = ((((uint64_t) mtimeHigh) << 32) | mtimeLow) + (configTICK_CLOCK_HZ / configTICK_RATE_HZ);

}
/*-----------------------------------------------------------*/

/* Sets and enable the timer interrupt */
void vPortSetupTimer(void)
{
	prvSetNextTimerInterrupt();

	/* Enable timer interupt */
	__asm volatile("csrs mie,%0"::"r"(0x80));
}


