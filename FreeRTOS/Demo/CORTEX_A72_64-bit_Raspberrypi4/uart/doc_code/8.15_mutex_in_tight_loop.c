/* The implementation of a task that uses a mutex in a tight loop. The task
creates a text string in a local buffer, then writes the string to a display.
Access to the display is protected by a mutex. */
void vATask( void *pvParameter )
{
    extern SemaphoreHandle_t xMutex;
    char cTextBuffer[ 128 ];
    for( ;; )
    {
        /* Generate the text string – this is a fast operation. */
        vGenerateTextInALocalBuffer( cTextBuffer );
        /* Obtain the mutex that is protecting access to the display. */
        xSemaphoreTake( xMutex, portMAX_DELAY );
        /* Write the generated text to the display–this is a slow operation. */
        vCopyTextToFrameBuffer( cTextBuffer );
        /* The text has been written to the display, so return the mutex. */
        xSemaphoreGive( xMutex );
    }
}