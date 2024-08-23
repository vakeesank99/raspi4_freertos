#include <stddef.h>
#include <stdint.h>

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


 // define functions
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );

static inline void io_halt(void)
{
    asm volatile ("wfi");
    return;
}
/*-----------------------------------------------------------*/
void vTask1( void * pvParameters )
{
        /* ulCount is declared volatile to ensure it is not optimized out. */
    volatile unsigned long ulCount;
    for( ;; )
    {
        /* Print out the name of the current task task. */
        uart_puts("\r\n  Task 1 is running \r\n " );
        /* Delay for a period. */
        for( ulCount = 0; ulCount < mainDELAY_LOOP_COUNT; ulCount++ )
            {
            /*
            * This loop is just a very crude delay implementation. There is
            * nothing to do in here. Later examples will replace this crude
            * loop with a proper delay/sleep function.
            */
            }
    }
}
/*-----------------------------------------------------------*/
void vTask2( void * pvParameters )
{
    /* ulCount is declared volatile to ensure it is not optimized out. */
    volatile unsigned long ulCount;
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        /* Print out the name of this task. */
        uart_puts("\r\n  Task 2 is running  \r\n " );
        /* Delay for a period. */
        for( ulCount = 0; ulCount < mainDELAY_LOOP_COUNT; ulCount++ )
        {
            /*
            * This loop is just a very crude delay implementation. There is
            * nothing to do in here. Later examples will replace this crude
            * loop with a proper delay/sleep function.
            */
        }
    }
}
/*-----------------------------------------------------------*/

void main(void)
{
    TaskHandle_t task_a;

    uart_init();
    uart_puts("\r\n****************************\r\n");
    uart_puts("\r\n    FreeRTOS UART Sample\r\n");
    uart_puts("\r\n  (This sample uses UART2)\r\n");
    uart_puts("\r\n****************************\r\n");

    xTaskCreate(    vTask1,     /* Pointer to the function that implements the task.*/
                    "Task 1",   /* Text name for the task. */
                    1000,       /* Stack depth in words. */
                    NULL,       /* This example does not use the task parameter. */
                    1,          /* This task will run at priority 1. */
                    NULL );     /* This example does not use the task handle. */

    /* Create the other task in exactly the same way and at the same priority.*/
    xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );

    vTaskStartScheduler();
}



/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
}

/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
}
