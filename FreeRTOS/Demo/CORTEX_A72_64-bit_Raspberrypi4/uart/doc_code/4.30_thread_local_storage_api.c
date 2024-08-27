void * pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                            BaseType_t xIndex )
                                            
void vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                        BaseType_t xIndex,
                                        void * pvValue );