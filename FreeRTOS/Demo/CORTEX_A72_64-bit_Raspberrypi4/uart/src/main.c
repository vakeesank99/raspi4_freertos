#include <stddef.h>
#include <stdint.h>
// #include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "uart.h"

/* 
 * Prototypes for the standard FreeRTOS callback/hook functions implemented
 * within this file.
 */

 // define vaiables
 unsigned long const mainDELAY_LOOP_COUNT = 20000000;
/* Define the strings that the tasks and interrupt will print out via the
gatekeeper. */
static char *pcStringsToPrint[] =
                                {
                                    "Task 1 ****************************************************\r\n",
                                    "Task 2 ----------------------------------------------------\r\n",
                                    "Message printed from the tick hook interrupt ##############\r\n"
                                                                                                        };
/*-----------------------------------------------------------*/
/* Declare a variable of type QueueHandle_t. The queue is used to send messages
from the print tasks and the tick interrupt to the gatekeeper task. */
QueueHandle_t xPrintQueue;

 // define functions
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );

static inline void io_halt(void)
{
    asm volatile ("wfi");
    return;
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
static void prvStdioGatekeeperTask( void *pvParameters )
{
    char *pcMessageToPrint;
    /* This is the only task that is allowed to write to standard out. Any
    other task wanting to write a string to the output does not access
    standard out directly, but instead sends the string to this task. As
    only this task accesses standard out there are no mutual exclusion or
    serialization issues to consider within the implementation of the task
    itself. */

    for( ;; )
    {
        /* Wait for a message to arrive. An indefinite block time is specified
        so there is no need to check the return value – the function will
        only return when a message has been successfully received. */
        xQueueReceive( xPrintQueue, &pcMessageToPrint, portMAX_DELAY );

        /* Output the received string. */
        uart_puts("\r\n");
        uart_puts(pcMessageToPrint);
        uart_puts("\r\n");

        /* Loop back to wait for the next message. */
    }
}
/*-----------------------------------------------------------*/
static void prvPrintTask( void *pvParameters )
{
    int iIndexToString;
    const TickType_t xMaxBlockTimeTicks = 0x20;
    /* Two instances of this task are created. The task parameter is used to
    pass an index into an array of strings into the task. Cast this to the
    required type. */

    iIndexToString = ( int ) pvParameters;
    for( ;; )
    {
        /* Print out the string, not directly, but instead by passing a pointer
        to the string to the gatekeeper task via a queue. The queue is
        created before the scheduler is started so will already exist by the
        time this task executes for the first time. A block time is not
        specified because there should always be space in the queue. */
        xQueueSendToBack( xPrintQueue, &( pcStringsToPrint[ iIndexToString ]), 0 );

        /* Wait a pseudo random time. Note that rand() is not necessarily
        reentrant, but in this case it does not really matter as the code
        does not care what value is returned. In a more secure application
        a version of rand() that is known to be reentrant should be used -
        or calls to rand() should be protected using a critical section. */
        // vTaskDelay( ( rand() % xMaxBlockTimeTicks ) );
         vTaskDelay( xMaxBlockTimeTicks  );
    }
}
/*-----------------------------------------------------------*/

void main(void)
{

    uart_init();
    uart_puts("\r\n****************************\r\n");
    uart_puts("\r\n    FreeRTOS UART Sample\r\n");
    uart_puts("\r\n  (This sample uses UART2)\r\n");
    uart_puts("\r\n****************************\r\n");

  xPrintQueue = xQueueCreate( 5, sizeof( char * ) );
    /* Check the queue was created successfully. */

    if( xPrintQueue != NULL )
    {
        /* Create two instances of the tasks that send messages to the
        gatekeeper. The index to the string the task uses is passed to the
        task via the task parameter (the 4th parameter to xTaskCreate()).
        The tasks are created at different priorities so the higher priority
        task will occasionally preempt the lower priority task. */
        xTaskCreate( prvPrintTask, "Print1", 1000, ( void * ) 0, 1, NULL );
        xTaskCreate( prvPrintTask, "Print2", 1000, ( void * ) 1, 2, NULL );
        /* Create the gatekeeper task. This is the only task that is permitted
        to directly access standard out. */
        xTaskCreate( prvStdioGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL );
        /* Start the scheduler so the created tasks start executing. */
        vTaskStartScheduler();
    }

    /* If all is well then main() will never reach here as the scheduler will
    now be running the tasks. If main() does reach here then it is likely
    that there was insufficient heap memory available for the idle task to
    be created. Chapter 3 provides more information on heap memory
    management. */
    for( ;; );
}



/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
}

/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
    /*
    Tick hook functions execute within the context of the tick interrupt, 
    and so must be kept very short, must use only a moderate amount of stack space, 
    and must not call any FreeRTOS API functions that do not end with 'FromISR()'.
    */

    static int iCount = 0;
    /* Print out a message every 200 ticks. The message is not written out
    directly, but sent to the gatekeeper task. */

    iCount++;
    if( iCount >= 200 )
    {
        /* As xQueueSendToFrontFromISR() is being called from the tick hook, it
        is not necessary to use the xHigherPriorityTaskWoken parameter (the
        third parameter), and the parameter is set to NULL. */
        xQueueSendToFrontFromISR(   xPrintQueue,
                                    &( pcStringsToPrint[ 2 ] ),
                                    NULL );
        /* Reset the count ready to print out the string again in 200 ticks
        time. */
        iCount = 0;
    }
}
