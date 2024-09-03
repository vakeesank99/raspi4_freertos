TaskHandle_t xHandle;

xTaskCreate(task1,
             "led",
              configMINIMAL_STACK_SIZE,
              (void *)mainTASK_LED1,
              mainLED_TASK_PRIORITY,
              &(xHandle));
vTaskCoreAffinitySet(xHandle, (1<<0));

xTaskCreate(task2,
             "led2",
              configMINIMAL_STACK_SIZE,
              (void *)mainTASK_LED2,
              mainLED_TASK_PRIORITY,
              &(xHandle));
vTaskCoreAffinitySet(xHandle, (1<<1));

vTaskStartScheduler();