/* Recursive mutexes are variables of type SemaphoreHandle_t. */
SemaphoreHandle_t xRecursiveMutex;
/* The implementation of a task that creates and uses a recursive mutex. */
void vTaskFunction( void *pvParameters )
{
    const TickType_t xMaxBlock20ms = pdMS_TO_TICKS( 20 );
    /* Before a recursive mutex is used it must be explicitly created. */

    xRecursiveMutex = xSemaphoreCreateRecursiveMutex();
    /* Check the semaphore was created successfully. configASSERT() is
    described in section 11.2. */

    configASSERT( xRecursiveMutex );
    /* As per most tasks, this task is implemented as an infinite loop. */

    for( ;; )
    {
        /* ... */
        /* Take the recursive mutex. */
        if( xSemaphoreTakeRecursive( xRecursiveMutex, xMaxBlock20ms ) == pdPASS )
        {
            /* The recursive mutex was successfully obtained. The task can now
            access the resource the mutex is protecting. At this point the
            recursive call count (which is the number of nested calls to
            xSemaphoreTakeRecursive()) is 1, as the recursive mutex has
            only been taken once. */
            /* While it already holds the recursive mutex, the task takes the
            mutex again. In a real application, this is only likely to occur
            inside a sub-function called by this task, as there is no
            practical reason to knowingly take the same mutex more than
            once. The calling task is already the mutex holder, so the
            second call to xSemaphoreTakeRecursive() does nothing more than
            increment the recursive call count to 2. */
            xSemaphoreTakeRecursive( xRecursiveMutex, xMaxBlock20ms );

            /* ... */
            /* The task returns the mutex after it has finished accessing the
            resource the mutex is protecting. At this point the recursive
            call count is 2, so the first call to xSemaphoreGiveRecursive()
            does not return the mutex. Instead, it simply decrements the
            recursive call count back to 1. */

            xSemaphoreGiveRecursive( xRecursiveMutex );
            /* The next call to xSemaphoreGiveRecursive() decrements the
            recursive call count to 0, so this time the recursive mutex is
            returned. */

            xSemaphoreGiveRecursive( xRecursiveMutex );
            /* Now one call to xSemaphoreGiveRecursive() has been executed for
            every proceeding call to xSemaphoreTakeRecursive(), so the task
            is no longer the mutex holder. */
        }
    }
}

/*-------------------------------------------------------------------------------------*/
/*taskYIELD() is called if the tick count changed
while the task held the mutex.*/
void vFunction( void *pvParameter )
    {
    extern SemaphoreHandle_t xMutex;
    char cTextBuffer[ 128 ];
    TickType_t xTimeAtWhichMutexWasTaken;
    for( ;; )
    {
        /* Generate the text string – this is a fast operation. */
        vGenerateTextInALocalBuffer( cTextBuffer );
        /* Obtain the mutex that is protecting access to the display. */
        xSemaphoreTake( xMutex, portMAX_DELAY );
        /* Record the time at which the mutex was taken. */
        xTimeAtWhichMutexWasTaken = xTaskGetTickCount();
        /* Write the generated text to the display–this is a slow operation. */
        vCopyTextToFrameBuffer( cTextBuffer );
        /* The text has been written to the display, so return the mutex. */
        xSemaphoreGive( xMutex );
        /* If taskYIELD() was called on each iteration then this task would
        only ever remain in the Running state for a short period of time,
        and processing time would be wasted by rapidly switching between
        tasks. Therefore, only call taskYIELD() if the tick count changed
        while the mutex was held. */
        if( xTaskGetTickCount() != xTimeAtWhichMutexWasTaken )
        {
            taskYIELD();
        }
    }
}