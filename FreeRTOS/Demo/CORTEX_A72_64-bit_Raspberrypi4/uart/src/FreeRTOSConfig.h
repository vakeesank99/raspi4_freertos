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
* Here are some comments created for my understanding from the book
* it will start with !! 
*/
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*--------------------Selecting the Scheduling Algorithm----------------*/
#define configUSE_PREEMPTION					1                                       // !! defines whether FreeRTOS uses cooperative or pre-emptive scheduling
// #define configUSE_TIME_SLICING                  1
// #define configUSE_TICKLESS_IDLE                 1                                    // tick interrupt being turned off completely for extended periods
                                                                                        // specifically for use in applications that must minimize their power consumption
#define configUSE_IDLE_HOOK						1
#define configUSE_TICK_HOOK						1

/*tick rate
compile-time configuration constant sets
the frequency of the tick interrupt, and so also the length of each time slice. For example, setting
configTICK_RATE_HZ to 100 (Hz) results in each time slice lasting 10 milliseconds.
typical value is 100
pdMS_TO_TICKS() cannot be used, if onfigTICK_RATE_HZ is greater than 1000
*/
#define configTICK_RATE_HZ	                    ( ( TickType_t ) 1000 )

/*
*    minimize configMAX_PRIORITIES because
*    more values require more RAM and will 
*    result in a longer worst-case execution time.
*/
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
// #define configTICK_TYPE_WIDTH_IN_BITS        32   // only if 64 = TICK_TYPE_WIDTH_64_BITS

/*
--------------how the Idle task is scheduled------------------- 
    0 then the Idle task remains in the Running state for the entirety of
    its time slice, unless it is preempted by a higher priority task.

    1 then the Idle task yields (voluntarily gives up whatever remains of
    its allocated time slice) on each iteration of its loop if there are other 
    Idle priority tasks in the Ready state.
*/
#define configIDLE_SHOULD_YIELD					1
//---------------------------------------------------------------
#define configUSE_MUTEXES						1                   // enable mutex

/* ---------Heap memory allocation scheme------------------*/
/*
* 0 then do not include a heap memory allocation scheme in your project.
* Else include a heap memory allocation scheme in your project, either 
* one of the heap_n.c files, or one provided by yourself
*/
// #define configSUPPORT_DYNAMIC_ALLOCATION        0   
// #define configSUPPORT_STATIC_ALLOCATION         1       //!! static memory allocation 
//---------------------------------------------------------------

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

/*architecture optimized
* Architecture optimized implementations are written in architecture-specific assembly code and are more
performant than the generic c implementation, and the worst-case execution time is the same for all
configMAX_PRIORITIES values. 
Not all FreeRTOS ports have an architecture optimized implementation
*/
// #define configUSE_PORT_optimized_TASK_SELECTION 1

/* Software timer definitions. */
#define configUSE_TIMERS						1
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH				5
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

/*
Note that the vTaskDelay() API function is available
 only when INCLUDE_vTaskDelay is set to 1
 */
#define INCLUDE_vTaskDelay						1

/*
vTaskPrioritySet() API function is only available 
when INCLUDE_vTaskPrioritySet is set to 1
*/
#define INCLUDE_vTaskPrioritySet                1

/*
uxTaskPriorityGet() API function is
only available when INCLUDE_uxTaskPriorityGet is set to 1
*/

/*
vTaskDelete() API function is only available when
INCLUDE_vTaskDelete is set to 1
It is not good practice to continuously create and delete tasks at run time, 
so consider other design options, such as re-using tasks, 
if you find yourself needing this function
*/
#define INCLUDE_vTaskDelete                     1

#define INCLUDE_uxTaskPriorityGet               1

#define INCLUDE_xSemaphoreGetMutexHolder		1

/*-----------C Runtime Thread Local Storage------------------------------*/
/*
newlib and picolibc. These pre-built C Runtime Thread Local Storage 
implementations can be enabled by by defining the respective macro
*/
#define configUSE_NEWLIB_REENTRANT              1           //newlib
#define configUSE_PICOLIBC_TLS                  1           //picolib

/*-----------Custom C Runtime Thread Local Storage---------------------*/
#define configUSE_C_RUNTIME_TLS_SUPPORT         1   //enable C Runtime Thread Local Storage support
#define configTLS_BLOCK_TYPE                        //the c type which should be used for storing C Runtime Thread Local Storage data
#define configINIT_TLS_BLOCK                        //the c code which should be run when initializing the C Runtime Thread Local Storage block.   
#define configSET_TLS_BLOCK                         //c code which should be run when switching in a new task
#define configDEINIT_TLS_BLOCK                      //c code which should be run when de-initializing the C Runtime Thread Local Storage block

/*-------------Application Thread Local Storage------------------------*/
/*
In addition to C Runtime Thread Local Storage, application developers 
may also define a set of application specific pointers to be included 
in the task control block
*/
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS         8  // non zero number to enable





void vConfigureTickInterrupt( void );
#define configSETUP_TICK_INTERRUPT() vConfigureTickInterrupt()
void vClearTickInterrupt( void );
#define configCLEAR_TICK_INTERRUPT() vClearTickInterrupt()

#define configINTERRUPT_CONTROLLER_BASE_ADDRESS (0xFF841000U)
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET (0x1000U)
#define configUNIQUE_INTERRUPT_PRIORITIES		(16)
#define configMAX_API_CALL_INTERRUPT_PRIORITY	(14)

#endif /* FREERTOS_CONFIG_H */

