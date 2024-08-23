void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    TickType_t xLastWakeTime;
    /*
    * The string to print out is passed in via the parameter. Cast this to a
    * character pointer.
    */
    pcTaskName = ( char * ) pvParameters;
    /*
    * The xLastWakeTime variable needs to be initialized with the current tick
    * count. Note that this is the only time the variable is written to
    * explicitly. After this xLastWakeTime is automatically updated within
    * vTaskDelayUntil().
    */
    xLastWakeTime = xTaskGetTickCount();
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        /* Print out the name of this task. */
        vPrintLine( pcTaskName );
        /*
        * This task should execute every 250 milliseconds exactly. As per
        * the vTaskDelay() function, time is measured in ticks, and the
        * pdMS_TO_TICKS() macro is used to convert milliseconds into ticks.
        * xLastWakeTime is automatically updated within vTaskDelayUntil(), so
        * is not explicitly updated by the task.
        */
        vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 250 ) );
    }
}