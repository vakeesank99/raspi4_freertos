/*
 * FreeRTOS Kernel V10.3.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


/*
* Here are some comments created for my inderstanding from the book
* it will start with !! 
*/
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION					1                                       // !! defines whether FreeRTOS uses cooperative or pre-emptive scheduling
#define configUSE_IDLE_HOOK						1
#define configUSE_TICK_HOOK						1
#define configTICK_RATE_HZ	                    ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES					( 8 )                                   // !! 0 is the lowest priority and (configMAX_PRIORITIES – 1) is the highest priority
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 200 )
#define configTOTAL_HEAP_SIZE					( 124 * 1024 )                          // !! sets the array size in bytes

/* TickType_t bit size configuration*/
/*
* TickType_t can be an unsigned 16-bit type, an unsigned 32-bit type, or an unsigned 64-bit type
* The setting of configTICK_TYPE_WIDTH_IN_BITS is architecture dependent. FreeRTOS ports will also
* check if this setting is valid. Using a 16-bit type can greatly improve efficiency on 8-bit and 16-bit architectures, 
* but severely limits the maximum block time that can be specified in FreeRTOS API calls. 
* There is no reason to use a 16-bit TickType_t type on a 32-bit or 64-bit architecture.
* Previous use of configUSE_16_BIT_TICKS has been replaced by configTICK_TYPE_WIDTH_IN_BITS
*/
#define configUSE_16_BIT_TICKS					0 
// #define configTICK_TYPE_WIDTH_IN_BITS           TICK_TYPE_WIDTH_64_BITS


#define configIDLE_SHOULD_YIELD					1

#define configUSE_MUTEXES						1

/* ---------Heap memory allocation scheme------------------*/
/*
* 0 then do not include a heap memory allocation scheme in your project.
* Else include a heap memory allocation scheme in your project, either 
* one of the heap_n.c files, or one provided by yourself
*/
// #define configSUPPORT_DYNAMIC_ALLOCATION        0   
// #define configSUPPORT_STATIC_ALLOCATION         1       //!! static memory allocation 


/*---------------Task creation parameters------------------------------------*/
/*
** defines the maximum length a task name can be, including 
* the NULL terminator. Supplying a longer string results in 
* the string being truncated.
*/
// #define configMAX_TASK_NAME_LEN                 
/*
allows the application writer to specify the data type used to
hold stack sizes. 
defaults to uint16_t if left undefined,
alternatives are : unsigned long or size_t
*/
// #define configSTACK_DEPTH_TYPE                  uint16_t

/* Software timer definitions. */
#define configUSE_TIMERS						1
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH				5
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskDelay						1

#define INCLUDE_xSemaphoreGetMutexHolder		1

void vConfigureTickInterrupt( void );
#define configSETUP_TICK_INTERRUPT() vConfigureTickInterrupt()
void vClearTickInterrupt( void );
#define configCLEAR_TICK_INTERRUPT() vClearTickInterrupt()

#define configINTERRUPT_CONTROLLER_BASE_ADDRESS (0xFF841000U)
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET (0x1000U)
#define configUNIQUE_INTERRUPT_PRIORITIES		(16)
#define configMAX_API_CALL_INTERRUPT_PRIORITY	(14)

#endif /* FREERTOS_CONFIG_H */

