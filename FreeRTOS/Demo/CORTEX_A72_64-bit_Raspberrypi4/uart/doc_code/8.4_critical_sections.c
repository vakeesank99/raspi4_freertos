/* Ensure access to the PORTA register cannot be interrupted by placing
it within a critical section. Enter the critical section. */
taskENTER_CRITICAL();

/* A switch to another task cannot occur between the call to
taskENTER_CRITICAL() and the call to taskEXIT_CRITICAL(). Interrupts may
still execute on FreeRTOS ports that allow interrupt nesting, but only
interrupts whose logical priority is above the value assigned to the
configMAX_SYSCALL_INTERRUPT_PRIORITY constant – and those interrupts are
not permitted to call FreeRTOS API functions. */
PORTA |= 0x01;

/* Access to PORTA has finished, so it is safe to exit the critical section. */
taskEXIT_CRITICAL();




/*vPrintString() is called
from many different tasks; so, in theory, its implementation 
could protect access to standard out using a critical
section*/
void vPrintString( const char *pcString )
{
/* Write the string to stdout, using a critical section as a crude method of
mutual exclusion. */
taskENTER_CRITICAL();
{
printf( "%s", pcString );
fflush( stdout );
}
taskEXIT_CRITICAL();
}


/*---------------------------interrupt safe version----------------------*/
void vAnInterruptServiceRoutine( void )
{
    /* Declare a variable in which the return value from
    taskENTER_CRITICAL_FROM_ISR() will be saved. */
    UBaseType_t uxSavedInterruptStatus;

    /* This part of the ISR can be interrupted by any higher priority
    interrupt. */
    /* Use taskENTER_CRITICAL_FROM_ISR() to protect a region of this ISR.
    Save the value returned from taskENTER_CRITICAL_FROM_ISR() so it can
    be passed into the matching call to taskEXIT_CRITICAL_FROM_ISR(). */
    uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

    /* This part of the ISR is between the call to
    taskENTER_CRITICAL_FROM_ISR() and taskEXIT_CRITICAL_FROM_ISR(), so can
    only be interrupted by interrupts that have a priority above that set
    by the configMAX_SYSCALL_INTERRUPT_PRIORITY constant. */
    /* Exit the critical section again by calling taskEXIT_CRITICAL_FROM_ISR(),
    passing in the value returned by the matching call to
    taskENTER_CRITICAL_FROM_ISR(). */
    taskEXIT_CRITICAL_FROM_ISR( uxSavedInterruptStatus );
    
    /* This part of the ISR can be interrupted by any higher priority
    interrupt. */
}