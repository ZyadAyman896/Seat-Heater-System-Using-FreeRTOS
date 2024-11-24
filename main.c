

#include "main.h"

int main()
{
    /*  The Hardware Setup Function  */
    prvSetupHardware();

    /********Creating Semaphores or MUTEXES********/

    /**/
    TEMPERATURE_TASK_SEMPHR = xSemaphoreCreateBinary() ;
    if(TEMPERATURE_TASK_SEMPHR != NULL)
    {
        UART0_SendString("Temp Semphr Created\r\n");
    }
    else
    {
        UART0_SendString("Temp Semphr Failed\r\n");
    }

    /**/
    SENSOR_TASK_SEMPHR = xSemaphoreCreateBinary() ;
    if(SENSOR_TASK_SEMPHR != NULL)
    {
        UART0_SendString("Sensor Semphr Created\r\n");
    }
    else
    {
        UART0_SendString("Sensor Semphr Failed\r\n");
    }

    /**/
    FAILURE_LED_TASK_SEMPHR = xSemaphoreCreateBinary() ;
    if(FAILURE_LED_TASK_SEMPHR != NULL)
    {
        UART0_SendString("Failure Semphr Created\r\n");
    }
    else
    {
        UART0_SendString("Failure Semphr Failed\r\n");
    }

    /**/
    RUN_TIME_MEASUREMENTS_TASK_SEMPHR = xSemaphoreCreateBinary() ;
    if(FAILURE_LED_TASK_SEMPHR != NULL)
    {
        UART0_SendString("RUN TIME Semphr Created\r\n");
    }
    else
    {
        UART0_SendString("RUN TIME Semphr Failed\r\n");
    }

    /**/
    UART_MUTEX = xSemaphoreCreateMutex();
    if( UART_MUTEX != NULL )
    {
        UART0_SendString("Uart Mutex Created\r\n");
    }
    else
    {
        UART0_SendString("Uart Mutex Failed\r\n");
    }

    /**/
    OFF_STATE_SEMPHR = xSemaphoreCreateBinary() ;
    if(OFF_STATE_SEMPHR != NULL)
    {
        UART0_SendString("OFF STATE Semphr Created\r\n");
    }
    else
    {
        UART0_SendString("OFF STATE Semphr Failed\r\n");
    }


    /*******Creating Queues*******/

    /**/
    xTemperatureQueue = xQueueCreate( SIZE_TEMPERATURE_QUEUE , sizeof( uint8 ) );
    if(xTemperatureQueue != NULL )
    {
        UART0_SendString("Temperature queue created\r\n");
    }
    else
    {
        UART0_SendString("Temperature queue Failed\r\n");
    }

    /**/
    xLevelOfHeatingQueue = xQueueCreate( SIZE_LEVEL_OF_HEATING_QUEUE , sizeof( uint8 ) );
    if(xLevelOfHeatingQueue != NULL )
    {
        UART0_SendString("Level of heating queue created\r\n");
    }
    else
    {
        UART0_SendString("Level of heating queue Failed\r\n");
    }
    /**/
    xStateOfHeatingQueue = xQueueCreate( SIZE_STATE_OF_HEATING_QUEUE , sizeof( uint8 ) );
    if(xStateOfHeatingQueue != NULL )
    {
        UART0_SendString("State of heating queue created\r\n");
    }
    else
    {
        UART0_SendString("State of heating queue Failed\r\n");
    }
    /**/
    xLevelOfHeatingForUARTQueue = xQueueCreate( SIZELEVEL_OF_HEATING_UART_QUEUE , sizeof( uint8 ) );
    if(xLevelOfHeatingForUARTQueue != NULL )
    {
        UART0_SendString("level of heating for uart queue created\r\n");
    }
    else
    {
        UART0_SendString("level of heating for uart queue Failed\r\n");
    }


    /*******Creating Queue Set******/

    /**/
    xLevelAndFailureQueue = xQueueCreateSet( SIZE_LEVEL_OF_HEATING_AND_FAILURE_QUEUE_SET ) ;
    if(xLevelAndFailureQueue != NULL )
    {
        UART0_SendString("Temp queue created\r\n");
    }
    else
    {
        UART0_SendString("Temp queue Failed\r\n");
    }



    /*******Adding Queues to Set******/

    /*  Adding Level of Heating Queue to Level and failure queue set    */
    xQueueAddToSet(xLevelOfHeatingQueue, xLevelAndFailureQueue);

    /*  Adding Failure Led Handling Semaphore to Level and failure queue set    */
    xQueueAddToSet(FAILURE_LED_TASK_SEMPHR, xLevelAndFailureQueue);

    /*  Adding Failure OFF STATE Semaphore to Level and failure queue set    */
    xQueueAddToSet(OFF_STATE_SEMPHR , xLevelAndFailureQueue);

    /*******Creating Events*******/

    /*  Event Group For Pressed Button and Failure Event    */
    xEventGroupPressedButton_FailureHandling  = xEventGroupCreate();


    /*******Creating Software Timers*******/
    /*  Create a software timer for Debouncing (50ms delay) */
    xDebounceTimerHandle = xTimerCreate("Debounce Timer",
                                           pdMS_TO_TICKS(DEBOUNCE_DELAY_MS),
                                           pdFALSE,
                                           (void *)0,
                                           DebounceTimerCallback);

    if( xDebounceTimerHandle != NULL )
    {
        UART0_SendString("Debounce Timer Created\r\n");
    }
    else
    {
        UART0_SendString("Debounce Timer Failed\r\n");
    }



    /******Creating FreeRTOS Tasks*******/

    /*  1 - vButtonControllerTask   */
    if ( xTaskCreate( vButtonControllerTask ,/**/
                 "Button Task" ,/**/
                 256 ,/**/
                 NULL ,/**/
                 2 ,/**/
                 NULL ) == pdPASS)
    {
        UART0_SendString("Button controller task Created \r\n");
    }   /**/
    else
    {
        UART0_SendString("Failed \r\n");
    }



    /*  2 - vTemperatureControllerTask  */
    if ( xTaskCreate( vTemperatureControllerTask , /**/
                 "Temperature Task" , /**/
                 256 ,/**/
                 NULL ,/**/
                 2 ,/**/
                 NULL ) == pdPASS)
    {
        UART0_SendString("Temperature task Created \r\n");
    }  /**/
    else
    {
        UART0_SendString("Failed \r\n");
    }


    /*  3 - vLedControllerTask  */
    if ( xTaskCreate( vLedControllerTask , /**/
                 "Led Task" ,/**/
                 256 ,/**/
                 NULL ,/**/
                 3 ,/**/
                 NULL ) == pdPASS ) /**/
    {
        UART0_SendString("Led task Created \r\n");
    }
    else
    {
        UART0_SendString("Failed \r\n");
    }


    /*  4 - vSensorControllerTask   */
    if ( xTaskCreate( vSensorControllerTask ,/**/
                 "Sensor Task" ,/**/
                 256 ,/**/
                 NULL ,/**/
                 3 ,/**/
                 NULL ) == pdPASS )
    {
        UART0_SendString("Sensor task Created \r\n");
    }/**/
    else
    {
        UART0_SendString("Failed \r\n");
    }


    /*  5 - vFailureHandlingTask    */
    if( xTaskCreate( vFailureHandlingTask ,/**/
                 "Failure Handling Task" ,/**/
                 256 ,/**/
                 NULL ,/**/
                 4 ,/**/
                 NULL ) == pdPASS )
    {
        UART0_SendString("Failure task Created \r\n");
    }/**/
    else
    {
        UART0_SendString("Failed \r\n");
    }


    /*  6 - vUARTTask   */
    if ( xTaskCreate( vUARTTask ,/**/
                 "Uart Task" ,/**/
                 256 ,/**/
                 NULL ,/**/
                 1 ,/**/
                 NULL ) == pdPASS )
    {
        UART0_SendString("UART task Created \r\n");
    }/**/
    else
    {
        UART0_SendString("Failed \r\n");
    }


    /*  7 - RunTimeMeasurementsTask */

    if ( xTaskCreate( vRunTimeMeasurementsTask ,
                 "Run-Time Measurements Task" ,
                 256 ,
                 NULL ,
                 0 ,
                 NULL ) == pdPASS )
    {
        UART0_SendString("Run-Time Measurements Task Created \r\n");
    }
    else
    {
        UART0_SendString("Failed \r\n");
    }


    /******Creating FreeRTOS Tasks Tags*******/


    vTaskSetApplicationTaskTag( vTemperatureControllerTask ,( TaskHookFunction_t ) TEMPERATURE_CONTROLLER_TAG );


    vTaskSetApplicationTaskTag( vButtonControllerTask ,( TaskHookFunction_t ) BUTTON_CONTROLLER_TAG );


    vTaskSetApplicationTaskTag( vLedControllerTask ,( TaskHookFunction_t ) LED_CONTROLLER_TAG );


    vTaskSetApplicationTaskTag( vSensorControllerTask ,( TaskHookFunction_t ) SENSOR_CONTROLLER_TAG );


    vTaskSetApplicationTaskTag( vFailureHandlingTask ,( TaskHookFunction_t ) FAILURE_HANDLING_TAG );


    vTaskSetApplicationTaskTag( vUARTTask ,( TaskHookFunction_t ) UART_CONTROLLER_TAG );


    vTaskSetApplicationTaskTag( vRunTimeMeasurementsTask ,( TaskHookFunction_t ) RUNTIME_CONTROLLER_TAG );


    /*  Start the scheduler so the created tasks start executing.   */
    vTaskStartScheduler();

    /*  The following line should never be reached.  */
    for (;;);

}





static void prvSetupHardware(void)
{
    /* Initializing UART */
    UART0_Init();

    /* Initializing GPIO Leds And Buttons*/
    GPIO_BuiltinButtonsLedsInit();

    /*  Initializing ADC*/
    ADC0_Init();

    /*  Initializing Interrupt for SW1  */
    GPIO_SW1EdgeTriggeredInterruptInit();

    /**/
    GPTM_WTimer0Init();



}
