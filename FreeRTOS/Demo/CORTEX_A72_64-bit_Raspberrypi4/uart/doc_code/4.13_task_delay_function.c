void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );
    /*
    * The string to print out is passed in via the parameter. Cast this to a
    * character pointer.
    */
    pcTaskName = ( char * ) pvParameters;
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        /* Print out the name of this task. */
        vPrintLine( pcTaskName );
        /*
        * Delay for a period. This time a call to vTaskDelay() is used which
        * places the task into the Blocked state until the delay period has
        * expired. The parameter takes a time specified in 'ticks', and the
        * pdMS_TO_TICKS() macro is used (where the xDelay250ms constant is
        * declared) to convert 250 milliseconds into an equivalent time in
        * ticks.
        */
        vTaskDelay( xDelay250ms );
    }
}