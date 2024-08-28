/*
Basic critical sections protect a region of code from access 
by other tasks and by interrupts, but a critical section
implemented by suspending the scheduler only protects a 
region of code from access by other tasks, because interrupts 
remain enabled
*/

void vPrintString( const char *pcString )
{
    /* Write the string to stdout, suspending the scheduler as a method of
    mutual exclusion. */
    vTaskSuspendScheduler();
    {
    printf( "%s", pcString );
    fflush( stdout );
    }
    xTaskResumeScheduler();
}

/*--------------------using mutex----------------------*/
static void prvNewPrintString( const char *pcString )
{
    /* The mutex is created before the scheduler is started, so already exists
    by the time this task executes.
    Attempt to take the mutex, blocking indefinitely to wait for the mutex
    if it is not available straight away. The call to xSemaphoreTake() will
    only return when the mutex has been successfully obtained, so there is
    no need to check the function return value. If any other delay period
    was used then the code must check that xSemaphoreTake() returns pdTRUE
    before accessing the shared resource (which in this case is standard
    out). As noted earlier in this book, indefinite time outs are not
    recommended for production code. */
    xSemaphoreTake( xMutex, portMAX_DELAY );
    {
        /* The following line will only execute once the mutex has been
        successfully obtained. Standard out can be accessed freely now as
        only one task can have the mutex at any one time. */
        printf( "%s", pcString );
        fflush( stdout );
        /* The mutex MUST be given back! */
    }
    xSemaphoreGive( xMutex );
}