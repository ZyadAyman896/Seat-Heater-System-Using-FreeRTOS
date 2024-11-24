/*
 * -------------------------------------------------------------------------
 * FreeRTOS Kernel Configuration File V1.0.0
 * Copyright (C) 2024 Edges For Training.  All Rights Reserved.
 * -------------------------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 * -------------------------------------------------------------------------
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "std_types.h"
#include "GPTM.h"


/*******************************************************************************
 *                           Run-Time Measurements Variables                  *
 *******************************************************************************/


extern uint32 ullTasksOutTime[8];

extern uint32 ullTasksInTime[8];

extern uint32 ullTasksTotalTime[8];

extern uint32 ullTaskExecutiontime[8];



/******************************************************************************/
/* Scheduling behavior related definitions. **********************************/
/******************************************************************************/

/* configCPU_CLOCK_HZ must be set to the frequency of the clock that drives 
 * the peripheral used to generate the kernels periodic tick interrupt.
 * This is very often, but not always, equal to the main system clock frequency.
 * Default frequency in Tiva-C Micro-controllers is 16Mhz */
#define configCPU_CLOCK_HZ                    (( unsigned long )16000000)

/* configTICK_RATE_HZ sets frequency of the tick interrupt in Hz, so
 * in our case Tick time will be 10ms */
#define configTICK_RATE_HZ                    ((TickType_t)100)

/* Size of the stack allocated to the Idle task. 128 Words = 512 Bytes */
#define configMINIMAL_STACK_SIZE              (128)

/* configMAX_PRIORITIES Sets the number of available task priorities.  Tasks can
 * be assigned priorities of 0 to (configMAX_PRIORITIES - 1).  Zero is the lowest
 * priority. */
#define configMAX_PRIORITIES                  (5)

/* Set configUSE_PREEMPTION to 1 to use pre-emptive scheduling. Set
 * configUSE_PREEMPTION to 0 to use co-operative scheduling. */
#define configUSE_PREEMPTION                  (1)


#define configUSE_MUTEXES                     (1)



#define configIDLE_SHOULD_YIELD               (1)



/* Set configUSE_TIME_SLICING to 1 to have the scheduler switch between Ready
 * state tasks of equal priority on every tick interrupt.  Set
 * configUSE_TIME_SLICING to 0 to prevent the scheduler switching between Ready
 * state tasks just because there was a tick interrupt. */
#define configUSE_TIME_SLICING                (1)

/* When configUSE_16_BIT_TICKS is set to 1, TickType_t is defined
 * to be an unsigned 16-bit type. When configUSE_16_BIT_TICKS is set to 0, 
 * TickType_t is defined to be an unsigned 32-bit type. */
#define configUSE_16_BIT_TICKS                (0)


#define configUSE_APPLICATION_TASK_TAG (1)




/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

/* Sets the total size of the FreeRTOS heap, in bytes, when heap_1.c, heap_2.c
 * or heap_4.c are included in the build. This value is defaulted to 4096 bytes but
 * it must be tailored to each application. Note the heap will appear in the .bss
 * section. */
#define configTOTAL_HEAP_SIZE                 ((size_t)(16384))

/* Set the following configUSE_* constants to 1 to include the named feature in
 * the build, or 0 to exclude the named feature from the build. */
#define configUSE_QUEUE_SETS                   (1)

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

/* Set the following INCLUDE_* constants to 1 to incldue the named API function,
 * or 0 to exclude the named API function.  Most linkers will remove unused
 * functions even when the constant is 1. */
#define INCLUDE_vTaskDelay                     (1)


#define INCLUDE_vTaskDelete                    (1)

/*  For using software timers */
#define configUSE_TIMERS                       (1)


#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)


#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE)


#define configTIMER_QUEUE_LENGTH               (10)


#define INCLUDE_xTimerPendFunctionCall         (1)


/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

/* Set the following configUSE_* constants to 1 to include the named hook
 * functionality in the build.  Set to 0 to exclude the hook functionality from the
 * build.  The application writer is responsible for providing the hook function
 * for any set to 1. */
#define configUSE_IDLE_HOOK                   (0)
#define configUSE_TICK_HOOK                   (0)
#define configCHECK_FOR_STACK_OVERFLOW        (0)

/******************************************************************************/
/* ARM Cortex-M Specific Definitions. *****************************************/
/******************************************************************************/

/* Tiva-C Micro-controllers use 3-bits as priority bits for each interrupt in NVIC PRI registers - 8 priority levels */
#define configPRIO_BITS                               3

/* The lowest interrupt priority that can be used */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY       7

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  5

/* Interrupt priorities used by the kernel port layer itself (the tick and context switch performing interrupts).
 * This implementation is generic to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY               (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* It sets the interrupt priority above which FreeRTOS API calls must not be made.  
 * Interrupts above this priority are never disabled, so never delayed by RTOS activity. 
 * This implementation is generic to all Cortex-M ports, and do not rely on any particular library functions. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY          (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/******************************************************************************/
/* Debugging assistance. ******************************************************/
/******************************************************************************/

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }



/*******************************************************************************
 *                           Run-Time Measurements HOOKS                       *
 *******************************************************************************/

#define traceTASK_SWITCHED_IN()                                 \
do                                                              \
{                                                               \
    uint32 taskInTag = (uint32)(pxCurrentTCB->pxTaskTag);       \
    ullTasksInTime[taskInTag] = GPTM_WTimer0Read();             \
}while(0);

#define traceTASK_SWITCHED_OUT()                                \
do                                                              \
{                                                               \
    uint32 taskOutTag = (uint32)(pxCurrentTCB->pxTaskTag);      \
    ullTasksOutTime[taskOutTag] = GPTM_WTimer0Read();           \
    ullTaskExecutiontime[taskOutTag]=ullTasksOutTime[taskOutTag] - ullTasksInTime[taskOutTag];  \
    ullTasksTotalTime[taskOutTag] += ullTasksOutTime[taskOutTag] - ullTasksInTime[taskOutTag];  \
}while(0);










#endif /* FREERTOS_CONFIG_H */
