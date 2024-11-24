/*
 * main.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Zyad Ayman
 */

#ifndef MAIN_H_
#define MAIN_H_


/*******************************************************************************
 *                           C Libraries Includes                          *
 *******************************************************************************/
#include <stdlib.h>


/*******************************************************************************
 *                           Kernel Includes                          *
 *******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"
#include "semphr.h"
#include "queue.h"


/*******************************************************************************
 *                           MCAL Includes                          *
 *******************************************************************************/
#include "uart0.h"
#include "gpio.h"
#include "ADC/ADC0.h"
#include "GPTM.h"

/*******************************************************************************
 *                           Registers                               *
 *******************************************************************************/
#include "tm4c123gh6pm_registers.h"


/*******************************************************************************
 *                           The HW Setup Function                          *
 *******************************************************************************/

static void prvSetupHardware(void);


/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

/*  Used For Iterations per Mili second for DelayMS Function*/
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND    (36U)

/*  Valid Range of the Temperature Sensor   */
#define MAX_RANGE_OF_SENSOR                         (45U)
#define MIN_RANGE_OF_SENSOR                         (0U)

/*  Valid Range of Potentiometer    */
#define MAX_VALID_RANGE_OF_SENSOR                            (40U)
#define MIN_VALID_RANGE_OF_SENSOR                            (5U)


/*  MACROS FOR STATES OF HEATING    */
#define OFF_STATE                                   (0U)
#define LOW_STATE                                   (1U)
#define MEDIUM_STATE                                (2U)
#define HIGH_STATE                                  (3U)

/*  MACROS FOR STATES TEMPERATURE'S OF HEATING    */

#define LOW_STATE_TEMP                                   (25U)
#define MEDIUM_STATE_TEMP                                (30U)
#define HIGH_STATE_TEMP                                  (35U)

/*  MACROS FOR LEVELS OF HEATING    */

#define LOW_INTENSITY_LEVEL                                 (1U)
#define MEDIUM_INTENSITY_LEVEL                              (2U)
#define HIGH_INTENSITY_LEVEL                                (3U)


/*  MACROS FOR SIZES OF QUEUES AND QUEUE SETS   */

#define SIZE_TEMPERATURE_QUEUE                              (2)

#define SIZE_LEVEL_OF_HEATING_QUEUE                         (2)

#define SIZE_STATE_OF_HEATING_QUEUE                         (2)

#define SIZELEVEL_OF_HEATING_UART_QUEUE                     (2)

#define SIZE_LEVEL_OF_HEATING_AND_FAILURE_QUEUE_SET         (2)



/*  MACRO FOR THE EVENT BIT OF PESSED BUTTON    */
#define BUTTON_PRESSED_BIT                              ( 1UL << 0UL )

/*  MACRO FOR THE EVENT BIT OF PESSED BUTTON    */
#define FAILURE_EVENT_BIT                               ( 1UL << 1UL )



/*  Degrees Macros */

#define TEN_DEGREES                 (10)
#define FIVE_DEGREES                (5)
#define TWO_DEGREES                 (2)
#define NINE_DEGREES                (9)
#define FOUR_DEGREES                (4)


/*   Adjust this value based on the bouncing time     */
#define DEBOUNCE_DELAY_MS           (100)

/*  Macros For Presses*/
#define FIRST_PRESS                 (1)
#define SECOND_PRESS                (2)
#define THIRD_PRESS                 (3)


/*******************************************************************************
 *                           FreeRTOS Tasks Prototypes                         *
 *******************************************************************************/

/**/
void vButtonControllerTask(void *pvParameters);

/**/
void vTemperatureControllerTask(void *pvParameters);

/**/
void vLedControllerTask(void *pvParameters);

/**/
void vSensorControllerTask(void *pvParameters);

/**/
void vFailureHandlingTask(void *pvParameters);

/**/
void vUARTTask(void *pvParameters);

/**/
void vRunTimeMeasurementsTask(void *pvParameters);

/*******************************************************************************
 *                           FreeRTOS Tasks Tags Macros                         *
 *******************************************************************************/

#define TEMPERATURE_CONTROLLER_TAG  (1U)

#define BUTTON_CONTROLLER_TAG       (2U)

#define LED_CONTROLLER_TAG          (3U)

#define SENSOR_CONTROLLER_TAG       (4U)

#define FAILURE_HANDLING_TAG        (5U)

#define UART_CONTROLLER_TAG         (6U)

#define RUNTIME_CONTROLLER_TAG         (7U)


/*******************************************************************************
 *                           FreeRTOS Task Handles                          *
 *******************************************************************************/

TaskHandle_t ButtonTask ;

TaskHandle_t TemperatureTask ;

TaskHandle_t LedTask ;

TaskHandle_t SensorTask ;

TaskHandle_t FailureHandlingTask ;

TaskHandle_t UartTask ;

TaskHandle_t RunTimeMeasurementsTask ;

/*******************************************************************************
 *                           FreeRTOS Queues HANDLES                         *
 *******************************************************************************/

/**/
QueueHandle_t xTemperatureQueue ;

/**/
QueueHandle_t xLevelOfHeatingQueue ;

/**/
QueueHandle_t xStateOfHeatingQueue ;

/**/
QueueHandle_t xLevelOfHeatingForUARTQueue ;



/*******************************************************************************
 *                           FreeRTOS Queue Sets HANDLES                         *
 *******************************************************************************/


/*  Contains 3 objects == > 1- Level of heating queue 2 - Failure Semaphore 3 - OFF STATE Semaphore */
QueueSetHandle_t xLevelAndFailureQueue ;




/*******************************************************************************
 *                           FreeRTOS Events HANDLES                         *
 *******************************************************************************/

/*  First Event Group contains Pressed Button Event */
EventGroupHandle_t xEventGroupPressedButton_FailureHandling ;


/*******************************    EVENTS BITS     ****************************/
/*
  EVENT BIT FOR THE EVENT OF PRESSING THE STATE OF HEATING BUTTON
const EventBits_t BUTTON_PRESSED_EVENT_BIT = ( BUTTON_PRESSED_BIT ) ;

  EVENT BIT FOR THE EVENT OF FAILURE IN THE RANGE OF THE SENSOR
const EventBits_t FAILURE_RANGE_EVENT_BIT = ( FAILURE_EVENT_BIT ) ;
*/


/*******************************************************************************
 *                           FreeRTOS Semaphores or MUTEXES HANDLES          *
 *******************************************************************************/

/**/
SemaphoreHandle_t TEMPERATURE_TASK_SEMPHR ;

/**/
SemaphoreHandle_t SENSOR_TASK_SEMPHR ;

/**/
SemaphoreHandle_t FAILURE_LED_TASK_SEMPHR ;

/**/
SemaphoreHandle_t UART_MUTEX ;

/**/
SemaphoreHandle_t OFF_STATE_SEMPHR ;

/**/
SemaphoreHandle_t RUN_TIME_MEASUREMENTS_TASK_SEMPHR ;



/*******************************************************************************
 *                 FreeRTOS Software Timers HANDLES                          *
 *******************************************************************************/

/*  Software Timer handle that is used for debouncing the interrupt */
TimerHandle_t xDebounceTimerHandle ;


/*******************************************************************************
 *                           Used Functions Prototypes                          *
 *******************************************************************************/

void Delay_MS(unsigned long long n);

/*******************************************************************************
 *                           Global Variables                          *
 *******************************************************************************/

/*  Counter for Presses pressed by the user  */
static uint8 PressesCounter = OFF_STATE;


/*  Debouncing Flag     */
static volatile uint8 isDebounce = FALSE ;

/*******************************************************************************
 *                           Handlers prototypes                          *
 *******************************************************************************/
void GPIOPORTFHandler(void);

void DebounceTimerCallback(TimerHandle_t xTimer);

/*******************************************************************************
 *                           MISCALLENOUS ADDRESSES                          *
 *******************************************************************************/

#define GPIO_PORTF_ICR_REG        (*((volatile uint32 *)0x4002541C))






/*******************************************************************************
 *                           Run-Time Measurements Variables                  *
 *******************************************************************************/


uint32 ullTasksOutTime[8];

uint32 ullTasksInTime[8];

uint32 ullTasksTotalTime[8];

uint32 ullTaskExecutiontime[8];






#endif /* MAIN_H_ */
