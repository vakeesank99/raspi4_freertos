/* Functions provided by the application writer than allocate and free
memory from a fast area of RAM. */

void *pvMallocFastMemory( size_t xWantedSize );
void vPortFreeFastMemory( void *pvBlockToFree );
/* Add the following to FreeRTOSConfig.h to map the pvPortMallocStack()
and vPortFreeStack() macros to the functions that use fast memory. */

#define pvPortMallocStack( x ) pvMallocFastMemory( x )
#define vPortFreeStack( x ) vPortFreeFastMemory( x )