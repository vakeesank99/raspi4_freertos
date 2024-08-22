/* Prototype of the vPortGetHeapStats() function. */
void vPortGetHeapStats( HeapStats_t *xHeapStats );

/* Definition of the HeapStats_t structure. All sizes specified in bytes. */
typedef struct xHeapStats
{
    /* The total heap size currently available - this is the sum of all the
    free blocks, not the largest available block. */
    size_t xAvailableHeapSpaceInBytes;
    /* The size of the largest free block within the heap at the time
    vPortGetHeapStats() is called. */
    size_t xSizeOfLargestFreeBlockInBytes;
    /* The size of the smallest free block within the heap at the time
    vPortGetHeapStats() is called. */
    size_t xSizeOfSmallestFreeBlockInBytes;
    /* The number of free memory blocks within the heap at the time
    vPortGetHeapStats() is called. */
    size_t xNumberOfFreeBlocks;
    /* The minimum amount of total free memory (sum of all free blocks)
    there has been in the heap since the system booted. */
    size_t xMinimumEverFreeBytesRemaining;
    /* The number of calls to pvPortMalloc() that have returned a valid
    memory block. */
    size_t xNumberOfSuccessfulAllocations;
    /* The number of calls to vPortFree() that has successfully freed a
    block of memory. */
    size_t xNumberOfSuccessfulFrees;
} HeapStats_t;