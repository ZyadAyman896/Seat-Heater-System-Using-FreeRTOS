/*
 * ADC0.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Zyad Ayman
 */

#ifndef ADC0_H_
#define ADC0_H_

/*******************************************************************************
 *                           Inclusions                                    *
 *******************************************************************************/
#include "Utils.h"
#include "std_types.h"


/*******************************************************************************
 *                           Functions Prototypes                          *
 *******************************************************************************/
void ADC0_Init();
uint16 ADC0_Read_AIN1_PE2();
uint16 ADC0_Read_AIN0_PE3();

/*******************************************************************************
 *                           Registers                                     *
 *******************************************************************************/

/*  GPIO registers (PORTE)   */
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTE_DIR_REG        (*((volatile uint32 *)0x40024400))
#define GPIO_PORTE_AFSEL_REG      (*((volatile uint32 *)0x40024420))
#define GPIO_PORTE_PUR_REG        (*((volatile uint32 *)0x40024510))
#define GPIO_PORTE_PDR_REG        (*((volatile uint32 *)0x40024514))
#define GPIO_PORTE_DEN_REG        (*((volatile uint32 *)0x4002451C))
#define GPIO_PORTE_LOCK_REG       (*((volatile uint32 *)0x40024520))
#define GPIO_PORTE_CR_REG         (*((volatile uint32 *)0x40024524))
#define GPIO_PORTE_AMSEL_REG      (*((volatile uint32 *)0x40024528))
#define GPIO_PORTE_PCTL_REG       (*((volatile uint32 *)0x4002452C))


/**/
#define SYSCTL_RCGCGPIO_REG       (*((volatile uint32 *)0x400FE608))

/**/
#define SYSCTL_PRGPIO_REG         (*((volatile uint32 *)0x400FEA08))

/*  Analog-to-Digital Converter RunMode Clock Gating Control (RCGCADC)  */
#define ADC0_RCGCADC_REG          (*((volatile uint32 *)0x400FE638))

/*  Base Address of ADC0 Registers  */
#define ADC0_BASEADDRESS_REG      (*((volatile uint32 *)0x40038000))

/*  ADC Active Sample Sequencer  */
#define ADC0_ADCACTSS_REG         (*((volatile uint32 *)0x40038000))

/*  ADC Event Multiplexer Select   */
#define ADC0_ADCEMUX_REG          (*((volatile uint32 *)0x40038014))

/*  ADC Sample Sequence Input Multiplexer Select 2    */
#define ADC0_ADCSSMUX2_REG        (*((volatile uint32 *)0x40038060))

/*  ADC Sample Sequence Control 2     */
#define ADC0_ADCSSCTL2_REG        (*((volatile uint32 *)0x40038084))

/*  ADC Clock Configuration   */
#define ADC0_ADCCC_REG            (*((volatile uint32 *)0x40038FC8))

/*  Analog-to-Digital Converter Peripheral Ready (PRADC)    */
#define SYSCTL_PRADC_REG                (*((volatile uint32 *)0x400FEA38))

/*  ADC Processor Sample Sequence Initiate (ADCPSSI) */
#define ADC0_ADCPSSI_REG                (*((volatile uint32 *)0x40038028))

/*  ADC Raw Interrupt Status (ADCRIS)   */
#define ADC0_ADCRIS_REG                 (*((volatile uint32 *)0x40038004))

/*  ADC Sample Sequence Result FIFO 2    */
#define ADC0_ADCSSFIFO2_REG             (*((volatile uint32 *)0x40038088))

/*  ADC Interrupt Status and Clear  */
#define ADC0_ADCISC_REG                 (*((volatile uint32 *)0x4003800C))


/*******************************************************************************
 *                           MACROS                                     *
 *******************************************************************************/

/*  Maximum Resolution of ADC0 = 2 power 12 == 4096 */
#define ADC0_MAX_RES 4095





/**/
#define ADC0_ _REG







#endif /* ADC0_H_ */








