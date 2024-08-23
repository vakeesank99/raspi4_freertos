TaskHandle_t xTask2Handle = NULL;
void vTask1( void * pvParameters )
{
    const TickType_t xDelay100ms = pdMS_TO_TICKS( 100UL );
    for( ;; )
    {
        /* Print out the name of this task. */
        vPrintLine( "Task 1 is running" );
        /*
        * Create task 2 at a higher priority.
        * Pass the address of xTask2Handle as the pxCreatedTask parameter so
        * that xTaskCreate write the resulting task handle to that variable.
        */
        xTaskCreate( vTask2, "Task 2", 1000, NULL, 2, &xTask2Handle );
        /*
        * Task 2 has/had the higher priority. For Task 1 to reach here, Task 2
        * must have already executed and deleted itself.
        */
        vTaskDelay( xDelay100ms );
    }
}

void vTask2( void * pvParameters )
{
    /*
    * Task 2 immediately deletes itself upon starting.
    * To do this it could call vTaskDelete() using NULL as the parameter.
    * For demonstration purposes, it instead calls vTaskDelete() with its own
    * task handle.
    */
    vPrintLine( "Task 2 is running and about to delete itself" );
    vTaskDelete( xTask2Handle );
}

int main( void )
{
    /* Create the first task at priority 1. */
    xTaskCreate( vTask1, "Task 1", 1000, NULL, 1, NULL );
    /* Start the scheduler so the task starts executing. */
    vTaskStartScheduler();
    /* main() should never reach here as the scheduler has been started. */
    for( ;; )
    {
    }
}

