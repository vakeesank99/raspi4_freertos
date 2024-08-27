/* A parameter is passed into the function. This will either be passed on the
stack, or in a processor register. Either way is safe as each task or
interrupt that calls the function maintains its own stack and its own set
of register values, so each task or interrupt that calls the function will
have its own copy of lVar1. */
long lAddOneHundred( long lVar1 )
{
    /* This function scope variable will also be allocated to the stack or a
    register, depending on the compiler and optimization level. Each task
    or interrupt that calls this function will have its own copy of lVar2.
    */
    long lVar2;
    lVar2 = lVar1 + 100;
    return lVar2;
}

/*-----------Not reentrant function----------------------*/
/* In this case lVar1 is a global variable, so every task that calls
lNonsenseFunction will access the same single copy of the variable. */
long lVar1;
long lNonsenseFunction( void )
{
    /* lState is static, so is not allocated on the stack. Each task that
    calls this function will access the same single copy of the variable. */
    static long lState = 0;
    long lReturn;
    switch( lState )
    {
        case 0 :    lReturn = lVar1 + 10;
                    lState = 1;
                    break;
        case 1 :    lReturn = lVar1 + 20;
                    lState = 0;
                    break;
    }
}