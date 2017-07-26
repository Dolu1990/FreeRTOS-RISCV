/*
 * tests.h
 *
 *  Created on: Jul 25, 2017
 *      Author: spinalvm
 */

#ifndef TESTS_H_
#define TESTS_H_

#define CHECK_PERIOD_MS 2000
#define CHECK_COUNT 3

#include "QueueSetPolling.h"

void tickTimer( TimerHandle_t xTimer ){
	//printf("event");
	for(int idx = 0;idx < 10;idx++){
		vQueueSetPollingInterruptAccess();
	}
}






void createTests(){
	vStartQueueSetPollingTask();
	TimerHandle_t printTimer = xTimerCreate
				   (
					 "Timer2",
					 ( 50UL / portTICK_PERIOD_MS ),
					 pdTRUE,
					 ( void * ) 0,
					 tickTimer
				   );
	xTimerStart( printTimer, 0 );
}

unsigned long checkTests(){
	unsigned long ulErrorFound = pdFALSE;

	/* Check all the demo and test tasks to ensure that they are all still
	running, and that none have detected an error. */

	if( xAreQueueSetPollTasksStillRunning() != pdPASS )
	{
		printf("Error in xxx tasks \r\n");
		ulErrorFound |= ( 0x01UL << 1UL );
	}

	return ulErrorFound;
}

#endif /* TESTS_H_ */
