/* Declare a variable that will be incremented by the hook function. */
volatile unsigned long ulIdleCycleCount = 0UL;
/*
* Idle hook functions MUST be called vApplicationIdleHook(), take no
* parameters, and return void.
*/
void vApplicationIdleHook( void )
{
    /* This hook function does nothing but increment a counter. */
    ulIdleCycleCount++;
}

void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );
    /*
    * The string to print out is passed in via the parameter. Cast this to
    * a character pointer.
    */
    pcTaskName = ( char * ) pvParameters;
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        /*
        * Print out the name of this task AND the number of times
        * ulIdleCycleCount has been incremented.
        */
        vPrintLineAndNumber( pcTaskName, ulIdleCycleCount );
        /* Delay for a period of 250 milliseconds. */
        vTaskDelay( xDelay250ms );
    }
}