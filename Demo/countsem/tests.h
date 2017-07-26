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

#include "countsem.h"

void createTests(){
	vStartCountingSemaphoreTasks();
}

unsigned long checkTests(){
	unsigned long ulErrorFound = pdFALSE;

	/* Check all the demo and test tasks to ensure that they are all still
	running, and that none have detected an error. */

	if( xAreCountingSemaphoreTasksStillRunning() != pdPASS )
	{
		printf("Error in countsem tasks \r\n");
		ulErrorFound |= ( 0x01UL << 1UL );
	}

	return ulErrorFound;
}

#endif /* TESTS_H_ */
