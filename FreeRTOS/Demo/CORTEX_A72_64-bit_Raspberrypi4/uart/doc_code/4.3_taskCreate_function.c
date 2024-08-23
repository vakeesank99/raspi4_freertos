/*
Return values
There are two possible return values:
pdPASS
This indicates the task was created successfully.
pdFAIL
This indicates there was not enough heap memory available to create the task.
*/
BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,                  // !! simply a pointer to the function that implements the task
                        const char * const pcName,                  // !! human-readable name is much simpler than identifying it by its handle.
                        configSTACK_DEPTH_TYPE usStackDepth,        // !! number of words the stack can hold, not the number of bytes.usStackDepth is 128, then 128 * 4 bytes.
                        void * pvParameters,                        // !! single void pointer (void *) parameter. pvParameters is the value passed into the task using that parameter
                        UBaseType_t uxPriority,                     // !! 0 is the lowest priority and (configMAX_PRIORITIES – 1) is the highest priority
                        TaskHandle_t * pxCreatedTask );             // !! This handle may be used in future API calls to, for example, change the task's priority or delete the task