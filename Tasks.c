/*
 * Tasks.c
 *
 *  Created on: Oct 5, 2024
 *      Author: Zyad Ayman
 */




/*GIT STATUS : NOT L
 * NEW UPDATE 17/10/2024 5:38PM
 * 1- CREATING A SEMAPHORE (OFF_STATE_SEMPHR) & ADDING IT TO LEVEL AND FAILURE QUEUE SET
 * 2- ADDED FEATURE TO HANDLE OFF STATE PRESS == > BY OPENNING THE YELLOW LED (GREEN + RED LEDS OPENED)
 *
 *
 * */


#include "main.h"


/**/
void vButtonControllerTask(void *pvParameters)
{

    if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
    {
        UART0_SendString("Button task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);

    /*  Buffer to receive the number OF Presses */
    uint8 PressesCounter ;

    /*  Variable to be sent in queue of heating state   */
    uint8 StateOfHeating ;

    /**/
    const EventBits_t xBitsToWaitFor = (BUTTON_PRESSED_BIT) ;
    EventBits_t xEventGroupValue ;


    for(;;)
    {
        /* Block to wait for button pressed event to become set within the event group. */
        xEventGroupValue = xEventGroupWaitBits(             xEventGroupPressedButton_FailureHandling , /* The event group to read. */
                                                            xBitsToWaitFor , /* Bits to test. */
                                                            pdTRUE , /* Clear bits on exit if the unblock condition is met. */
                                                            pdTRUE , /* Wait for all bits. */
                                                            portMAX_DELAY); /* Don't time out. */

        if( ( xEventGroupValue & xBitsToWaitFor ) != 0 )
        {


            /*  Decide the user want which state if heating according to his number of presses  */
            if ( xQueueReceive(xStateOfHeatingQueue, &PressesCounter, portMAX_DELAY) == pdPASS )
            {
                switch(PressesCounter)
                {
                        /*  if One presses then user wants medium state of heating  */
                    case FIRST_PRESS :
                        StateOfHeating = LOW_STATE ;
                        if( xQueueSend(xStateOfHeatingQueue , &StateOfHeating , portMAX_DELAY) == pdPASS )
                        {
                            /*  Giving Binary semaphore to Start Temperature Controller Task */
                            xSemaphoreGive(TEMPERATURE_TASK_SEMPHR);
                        }
                        break;
                        /*  if Two presses then user wants medium state of heating  */
                    case SECOND_PRESS :
                        StateOfHeating = MEDIUM_STATE ;
                        if( xQueueSend(xStateOfHeatingQueue , &StateOfHeating , portMAX_DELAY) == pdPASS )
                        {
                            /*  Giving Binary semaphore to Start Temperature Controller Task */
                            xSemaphoreGive(TEMPERATURE_TASK_SEMPHR);
                        }
                        break;
                        /*  if Three presses then user wants medium state of heating  */
                    case THIRD_PRESS :
                        StateOfHeating = HIGH_STATE ;
                        if( xQueueSend(xStateOfHeatingQueue , &StateOfHeating , portMAX_DELAY) == pdPASS )
                        {
                            /*  Giving Binary semaphore to Start Temperature Controller Task */
                            xSemaphoreGive(TEMPERATURE_TASK_SEMPHR);
                        }
                        break;
                    case OFF_STATE :
                        /*  Giving Binary semaphore to Start Led Task to open yellow led to indicate off state */
                        xSemaphoreGive(OFF_STATE_SEMPHR);
                        break ;
                }

            }

        }

    }

}


/**/
void vTemperatureControllerTask(void *pvParameters)
{
    if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
    {
        UART0_SendString("Temperature task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);


    /*  Buffer To Receive The State of The Heating  */
    uint8 StateOfHeating ;

    /*  Buffer To Receive The Current Temperature  */
    uint8 CurrentTemperature ;

    /*  Buffer for Difference Between current Temperature and state of heating */
    uint8 DifferenceBuffer ;

    /*  Variable for putting in it temperature of state desired */
    uint8 TempDegreeOfState ;

    /*  Variable for Storing the Level of Heating Should be enabled */
    uint8 LevelOfHeating ;

    for(;;)
    {
        /*  Disabling All interrupts    */
        //taskENTER_CRITICAL();

        /*  Taking Semaphore To Start the Task  */
        if( xSemaphoreTake(TEMPERATURE_TASK_SEMPHR , portMAX_DELAY) == pdPASS )
        {
            /*  Receiving State of Heating which was sent by Button Task Sent on xStateOfHeatingQueue   */
            if(xQueueReceive(xStateOfHeatingQueue, &StateOfHeating, portMAX_DELAY) == pdPASS )
            {
                /*  Giving The Semaphore Of the Sensor Task To Start it and get the current Temperature     */
                xSemaphoreGive(SENSOR_TASK_SEMPHR);
            }



            /*  Receiving Current Temperature  which was sent by Sensor Task Sent on xTemperatureQueue   */
            if(xQueueReceive(xTemperatureQueue, &CurrentTemperature, portMAX_DELAY) == pdPASS )
            {

            }



            /*  Applying The Algorithm  */

            /*  Pre-step    */
            switch(StateOfHeating)
            {
                case LOW_STATE :
                    TempDegreeOfState = LOW_STATE_TEMP ;
                    break;

                case MEDIUM_STATE :
                    TempDegreeOfState = MEDIUM_STATE_TEMP ;
                    break;

                case HIGH_STATE :
                    TempDegreeOfState = HIGH_STATE_TEMP ;
                    break;
            }

            /************************************************/
            /*  Handling a corner case if cureent temp is greater than needed state so intensity should be off  */
            if (CurrentTemperature >= TempDegreeOfState)
            {
                /*  Heater should be off    */
                DifferenceBuffer = 0;
                /*  Must Give The semaphore of the OFF STATE    */
                xSemaphoreGive(OFF_STATE_SEMPHR);
            }
            else
            {
                /*  Calculating the difference  between TempDegreeOfState and CurrentTemperature to decide which intensity to be able  */
                DifferenceBuffer = ( TempDegreeOfState - CurrentTemperature ) ;
                /************************************************/
                /*  switching on DifferenceBuffer to apply the needed algorithm to decide which intensity to be able   */
                if( ( DifferenceBuffer >= TWO_DEGREES ) && ( DifferenceBuffer <= FIVE_DEGREES ) )
                {
                    LevelOfHeating = LOW_INTENSITY_LEVEL ;
                }
                else if ( ( DifferenceBuffer >= FIVE_DEGREES ) && ( DifferenceBuffer <= TEN_DEGREES ) )
                {
                    LevelOfHeating = MEDIUM_INTENSITY_LEVEL ;
                }
                else if( DifferenceBuffer > TEN_DEGREES )
                {
                    LevelOfHeating = HIGH_INTENSITY_LEVEL ;
                }


                /*  Sending The level of heating required to be enabled to be used by Led task  */
                if ( xQueueSend(xLevelOfHeatingQueue , &LevelOfHeating , portMAX_DELAY) == pdPASS )
                {
                    /*                                  */
                }



                /************Sending in Queues that will be used by UART TASK************/


                /*  Sending The State of heating required to be enabled to be used by UART task*/
                if ( xQueueSend(xStateOfHeatingQueue , &StateOfHeating , portMAX_DELAY) == pdPASS )
                {
                    /*                                  */
                }

                /*  Sending The Current temperature to be used by UART task  */
                if ( xQueueSend(xTemperatureQueue , &CurrentTemperature , portMAX_DELAY) == pdPASS )
                {
                    /*                                  */
                }

                /*  Sending The level of heating required to be enabled to be used by UART task  */
                if ( xQueueSend(xLevelOfHeatingForUARTQueue , &LevelOfHeating , portMAX_DELAY) == pdPASS )
                {
                    /*                                  */
                }
            }




        }

        /*  Enabling All interrupts    */
        //taskEXIT_CRITICAL();

    }



}


/**/
void vLedControllerTask(void *pvParameters)
{

    if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
    {
        UART0_SendString("Led task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);


    /*  a handle to differentiate which had me out of blocked state (Semaphore or Queue) ? */
    QueueSetMemberHandle_t xActivatedMember ;

    /*  Buffer to store level of heating and switch on it   */
    uint8 LevelOfHeating ;



    for(;;)
    {
        /*  Disabling All interrupts    */
        //taskENTER_CRITICAL();

        /*  Blocking on a Queue set which contains Level of heating queue and Led failure semaphore */
        /*  Block to wait for something to be available from the queue or the semaphore */
        xActivatedMember = xQueueSelectFromSet( xLevelAndFailureQueue , portMAX_DELAY );

        /*if the activated member handle was level of heating queue
         * so we receive from level of heating queue and decide which led to open  */
        if( xActivatedMember == xLevelOfHeatingQueue )
        {
            /*  Receiving level of heating from queue to decide which led to turn on */
            xQueueReceive(xLevelOfHeatingQueue , &LevelOfHeating , portMAX_DELAY );

            /*  Switching on Heating level to decide opening which Led  */
            switch(LevelOfHeating)
            {
                        /*  Opening Green Led at Low Level Intensity */
                case LOW_INTENSITY_LEVEL :
                        GPIO_BlueLedOff();

                        GPIO_GreenLedOn();

                        GPIO_RedLedOff();
                        break;
                        /*  Opening Blue Led at Medium Level Intensity */
                case MEDIUM_INTENSITY_LEVEL :
                        GPIO_GreenLedOff();

                        GPIO_BlueLedOn();

                        GPIO_RedLedOff();
                        break;
                        /*  Opening Cyan = (Green + Blue) Led at High Level Intensity */
                case HIGH_INTENSITY_LEVEL :
                        GPIO_GreenLedOn();

                        GPIO_BlueLedOn();

                        GPIO_RedLedOff();
                        break;
            }

        }
        /*  In case of Sensor's range failure we have to open Red led To inform the user    */
        else if( xActivatedMember == FAILURE_LED_TASK_SEMPHR )
        {
            GPIO_GreenLedOff();

            GPIO_BlueLedOff();

            GPIO_RedLedOn();

            if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
            {
                UART0_SendString("/*****************************************************************************/\r\n");
                UART0_SendString("................................SYSTEM FAILURE.................................\r\n");
                UART0_SendString("/*****************************************************************************/\r\n");
            }
            xSemaphoreGive(UART_MUTEX);

        }
        /*  In case of OFF STATE Option we have to open Yellow led ( RED + GREEN ) To inform the user we are in OFF STATE    */
        else if ( xActivatedMember == OFF_STATE_SEMPHR )
        {
            GPIO_GreenLedOn();

            GPIO_BlueLedOff();

            GPIO_RedLedOn();


            if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
            {
                UART0_SendString("/*****************************************************************************/\r\n");
                UART0_SendString("....................................OFF STATE..................................\r\n");
                UART0_SendString("/*****************************************************************************/\r\n");
            }
            xSemaphoreGive(UART_MUTEX);
        }

        /*  Enabling All interrupts    */
        //taskEXIT_CRITICAL();
    }



}


/*Channel of Reading ADC Value == > PE2
 *
 *
 *
 * */
void vSensorControllerTask(void *pvParameters)
{

    if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
    {
        UART0_SendString("sensor task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);


    /*  Variable of CurrentTemperature  */
    uint16 CurrentTemperature ;


    for(;;)
    {
        /*  Disabling All interrupts    */
        //taskENTER_CRITICAL();

        /*  Taking The Semaphore Of the Sensor Task To Start it and get the current Temperature     */
        if( xQueueSemaphoreTake(SENSOR_TASK_SEMPHR , portMAX_DELAY) == pdPASS )
        {

            /*  Reading ADC Value of the Sensor   */
            CurrentTemperature = ADC0_Read_AIN1_PE2();

            /*  Mapping Sensor Reading to be in Range of == > MIN = 5 ... MAX = 40 C  */
            CurrentTemperature = ( ( CurrentTemperature * MAX_RANGE_OF_SENSOR ) / ADC0_MAX_RES );


            /*  if Sensor Gives Readings out of range so we Set The event of the Failure in range to start Failure task to inform user by the error  */
            if( ( CurrentTemperature < MIN_VALID_RANGE_OF_SENSOR ) || ( CurrentTemperature > MAX_VALID_RANGE_OF_SENSOR ) )
            {
                /*  Setting the event of failure if detected in sensor's range  */
                xEventGroupSetBits( xEventGroupPressedButton_FailureHandling , FAILURE_EVENT_BIT );

            }
            /*  if there is no error in range send the current temperature in its queue */
            else
            {

                /*  Sending the current temperature measured from the sensor in the temperature queue   */
                if( xQueueSend(xTemperatureQueue , &CurrentTemperature , portMAX_DELAY) == pdPASS )
                {
                /*  for debugging                  */
                }

            }

        /*  Enabling All interrupts    */
        //taskEXIT_CRITICAL();
        }
    }


}


/**/
void vUARTTask(void *pvParameters)
{

    if( xSemaphoreTake( UART_MUTEX , portMAX_DELAY ) == pdPASS )
    {
        UART0_SendString("Uart task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);




    /*  Buffer to read CurrentTemperature from queue    */
    uint8 CurrentTemperature ;
    /*  Buffer to read LevelOfHeating from queue    */
    uint8 LevelOfHeating ;
    /*  Buffer to read StateOfHeating from queue    */
    uint8 StateOfHeating ;





    for(;;)
    {
        /*  Disabling All interrupts    */
        //taskENTER_CRITICAL();

        /*  Receiving from current temperature queue to print it on screen  */
        if ( xQueueReceive(xTemperatureQueue, &CurrentTemperature , portMAX_DELAY) == pdPASS )
        {
            /*  Outline for Every Start of a Printed Block   */
            UART0_SendString("..........................................................\r\n");


            /*  1 - Printing the Current Temperature   */
            UART0_SendString("Current Temperature is = ");
            UART0_SendInteger(CurrentTemperature);
            /*  To Start a new line */
            UART0_SendString("\r\n");

            /*  End of First Part  */
            UART0_SendString(".............................\r\n");

        }

        /*  Receiving from Level Of Heating queue to print it on screen  */
        if( xQueueReceive(xLevelOfHeatingForUARTQueue, &LevelOfHeating , portMAX_DELAY) == pdPASS )
        {

            /*  2 - Printing the Level Of Heating   */
            UART0_SendString("Current Level of Heating is ");

            switch(LevelOfHeating)
            {
                case LOW_INTENSITY_LEVEL :
                    UART0_SendString("Low Intensity");
                    break;
                case MEDIUM_INTENSITY_LEVEL :
                    UART0_SendString("Medium Intensity");
                    break;
                case HIGH_INTENSITY_LEVEL :
                    UART0_SendString("High Intensity");
                    break;

            }
            /*  To Start a new line */
            UART0_SendString("\r\n");


            /*   End of Second Part  */
            UART0_SendString(".............................\r\n");
        }

        /*  Receiving from State Of Heating queue to print it on screen  */
        if( xQueueReceive(xStateOfHeatingQueue, &StateOfHeating , portMAX_DELAY) == pdPASS )
        {
            /*  3 - Printing the State Of Heating   */
            UART0_SendString("State of Heating is ");

            switch(StateOfHeating)
            {
                case LOW_STATE :
                    UART0_SendString("Low State");
                    break;
                case MEDIUM_STATE :
                    UART0_SendString("Medium State");
                    break;
                case HIGH_STATE :
                    UART0_SendString("High State");
                    break;

            }

            /*  To Start a new line */
            UART0_SendString("\r\n");

            /*  Third and last Part  */

            UART0_SendString("..........................................................\r\n");
            /*  Outline for Every End of a Printed Block   */

        }
        //xSemaphoreGive(RUN_TIME_MEASUREMENTS_TASK_SEMPHR);
        /*  Enabling All interrupts    */
        //taskEXIT_CRITICAL();
    }



}

/*  GPIO PORTF HANDLER FOR SW1 */

/*
     * PF0 --> SW2
     * PF1 --> Red LED
     * PF2 --> Blue LED
     * PF3 --> Green LED
     * PF4 --> SW1
     */


void GPIOPORTFHandler(void)
{

    /*  Counter for Presses pressed by the user  */
    static uint8 PressesCounter = OFF_STATE;


    /*  Interrupt Debouncing    */


    /* checking if we are already in a Debouncing period or not
     * if not so we have to execute the code   */
    if(isDebounce == FALSE )
    {

        /*  Clearing the interrupt flag for PF4 == > SW1    */
        SET_PIN(GPIO_PORTF_ICR_REG , PIN_NO_4);
        /*  Clearing the interrupt flag for PF0 == > SW2    */
        //SET_PIN(GPIO_PORTF_ICR_REG , PIN_NO_0);

        /*  Starting the timer  */
        xTimerStartFromISR(xDebounceTimerHandle , 0 );



        /*  For Debugging   */
        UART0_SendString("Interrupt is fired\r\n");

        /*  xHigherPriorityTaskWoken variable to indicate a switch is required  */
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;


        /*  Checking if this is press is more than the third press so the user wants the system to be off   */
        if(PressesCounter == HIGH_STATE)
        {
            PressesCounter = OFF_STATE ;
            /*  You Should turn Off The system  */

            /******************* ACTION MUST BE DONE ************************************/

        }
        /* if this press is lower than the third press */
        else
        {
            /*  increment the counter   */
            PressesCounter++ ;
        }

        /*  Sending the presses counter to the queue of state of heating to make Temperature controller task decides    */
        xQueueSendFromISR(xStateOfHeatingQueue , &PressesCounter , &xHigherPriorityTaskWoken);


        /*  If the button is pressed ==> Set event of the pressing the button   */
        xEventGroupSetBitsFromISR(xEventGroupPressedButton_FailureHandling , BUTTON_PRESSED_BIT , &xHigherPriorityTaskWoken);

        /*  Setting the flag that we are in a Debouncing period */
        isDebounce = TRUE ;

        /*  Perform a context switch if necessary    */
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    }

}




/**/

void vFailureHandlingTask(void *pvParameters)
{
    /*  Printing that the task is entered   */
    /*  using MUTEX For critical section to not be interrupted by another task  */
    if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
    {
        UART0_SendString("Failure handling task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);

    /*  Variable to store the group of the event group  */
    EventBits_t xEventGroupValue ;

    for(;;)
    {
        /*  Disabling All interrupts    */
        //taskENTER_CRITICAL();

        /*  Waiting for event of failure in sensor's range  */
        xEventGroupValue = xEventGroupWaitBits(xEventGroupPressedButton_FailureHandling, /* Event group which we wait on    */
                                               FAILURE_EVENT_BIT, /*  bits to wait for    */
                                               pdTRUE , /*  Clear event bits on exit    */
                                               pdFALSE, /*  Waiting for only one bit which is second one (Bit 1)    */
                                               portMAX_DELAY);/*    wait max time in blocked state before timeout   */

        /*  checking if the event bit is set    */
        if( ( xEventGroupValue & FAILURE_EVENT_BIT ) != 0 )
        {
            /*  Doing the Logic required    */

            /*  Giving Semaphore to start the Led Task to inform the user there is error in system by opening the RED LED   */
            xSemaphoreGive(FAILURE_LED_TASK_SEMPHR);

        }

        /*  to give a chance for another tasks if they have to go running instead   */
        vTaskDelay(pdMS_TO_TICKS(10));


        /*  Enabling All interrupts    */
        //taskEXIT_CRITICAL();

    }



}


/*  Timer callback to reset Debounce flag    */
void DebounceTimerCallback(TimerHandle_t xTimer)
{

    /* Reset the Debouncing flag, allowing new interrupts to be processed   */
    isDebounce = FALSE ;

}


void vRunTimeMeasurementsTask(void *pvParameters)
{

    if( xSemaphoreTake(UART_MUTEX,portMAX_DELAY) == pdPASS )
    {
        UART0_SendString("RunTimeMeasurements task is started\r\n");
    }
    xSemaphoreGive(UART_MUTEX);

    for(;;)
    {
        if( xSemaphoreTake(RUN_TIME_MEASUREMENTS_TASK_SEMPHR,portMAX_DELAY) == pdPASS )
        {
            uint8 ucCounter, ucCPU_Load;

            uint32 ullTotalTasksTime = 0;

            for(ucCounter = 1 ; ucCounter <= 7; ucCounter++)
            {
                switch(ucCounter)
                {
                    case TEMPERATURE_CONTROLLER_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("TEMPERATURE_CONTROLLER_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();

                    break;

                    case BUTTON_CONTROLLER_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("BUTTON_CONTROLLER_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();

                    break;

                    case LED_CONTROLLER_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("LED_CONTROLLER_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();

                    break;

                    case UART_CONTROLLER_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("UART_CONTROLLER_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();

                    break;

                    case FAILURE_HANDLING_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("FAILURE_HANDLING_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();

                    break;

                    case SENSOR_CONTROLLER_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("SENSOR_CONTROLLER_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();
                    break;

                    case RUNTIME_CONTROLLER_TAG:

                        taskENTER_CRITICAL();

                        UART0_SendString("RUNTIME_CONTROLLER_TASK Execution time = ");

                        UART0_SendInteger(ullTaskExecutiontime[ucCounter]);

                        UART0_SendString("% \r\n");

                        taskEXIT_CRITICAL();
                    break;
                }
                ullTotalTasksTime += ullTasksTotalTime[ ucCounter ];
            }

            ucCPU_Load = ( (ullTotalTasksTime * 100) /  GPTM_WTimer0Read() ) ;

            taskENTER_CRITICAL();

            UART0_SendString("CPU Load is ");

            UART0_SendInteger(ucCPU_Load);

            UART0_SendString("% \r\n");

            taskEXIT_CRITICAL();
        }
    }


}








