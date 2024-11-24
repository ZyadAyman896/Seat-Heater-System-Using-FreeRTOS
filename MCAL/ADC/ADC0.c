


#include "ADC0.h"




void ADC0_Init()
{


    /*  1   */
    /*  Enable the ADC0 clock using the RCGCADC register and waiting  */

    SET_PIN(ADC0_RCGCADC_REG , PIN_NO_0);
    while (!READ_PIN(SYSCTL_PRADC_REG, PIN_NO_0)); // Wait for ADC0 to be ready


    /*  2   */
    /*  Enabling the Clock For PortE    */

    SET_PIN(SYSCTL_RCGCGPIO_REG , PIN_NO_4);
    while(!READ_PIN(SYSCTL_PRGPIO_REG, PIN_NO_4));

    /*  3   */
    /*  Choosing Analog Mode For Pins PE3 & PE2   */

    SET_PIN(GPIO_PORTE_AFSEL_REG , PIN_NO_2); // PE2 == > AIN1
    SET_PIN(GPIO_PORTE_AFSEL_REG , PIN_NO_3); // PE3 == > AIN0

    /*  4   */
    /*  Configure the AINx signals to be Analog Inputs  */

    CLR_PIN(GPIO_PORTE_DEN_REG , PIN_NO_2); // PE2 == > AIN1
    CLR_PIN(GPIO_PORTE_DEN_REG , PIN_NO_3); // PE3 == > AIN0

    /*  5   */
    /*   Disable the analog isolation circuit for all ADC input pins    */

    SET_PIN(GPIO_PORTE_AMSEL_REG , PIN_NO_2); // PE2 == > AIN1
    SET_PIN(GPIO_PORTE_AMSEL_REG , PIN_NO_3); // PE3 == > AIN0

    /*  For Module Clocking , Adjusting ADC Clock on PIOSC providing a 16-MHz clock source  */

        ADC0_ADCCC_REG = ( ( ADC0_ADCCC_REG & 0x00000000 ) | 0x1 ) ;


    /*  Programming Sample Sequencer  SS2  */

    /*  1- Disabling Sample Sequencer To Program It */

    CLR_PIN(ADC0_ADCACTSS_REG , PIN_NO_2);


    /*  2- Configure the trigger event for the sample sequencer in the ADCEMUX register.    */

    ADC0_ADCEMUX_REG = ( (ADC0_ADCEMUX_REG & 0xFFFFFFF0) | 0xF ) ;

    /*  3- Configure the corresponding input source in the ADCSSMUXn register   */

    /*    Clearing it     */
    /*  Choosing MUX0 (PE3) == > AIN0 and MUX1 (PE2) == > AIN1    */

    ADC0_ADCSSMUX2_REG = ( ( ADC0_ADCSSMUX2_REG & 0x00000000 ) | 0x0010 ) ;


    /*  4- configure the sample control bits in the corresponding nibble in the ADCSSCTLn register  */

    ADC0_ADCSSCTL2_REG = 0x006 ;

    /*  5- Enabling Sample Sequencer SS2   */

    SET_PIN(ADC0_ADCACTSS_REG , PIN_NO_2);


}


uint16 ADC0_Read_AIN0_PE3()
{
    /*  1. Configure SS2 for AIN0 (PE3) */
    ADC0_ADCSSMUX2_REG = 0x0; // MUX0 selects AIN0 (PE3)
    ADC0_ADCSSCTL2_REG = 0x6; // Set SS2 for single-ended input and EOS for AIN0

    /*  2. Trigger the conversion on Sample Sequencer 2 (SS2) */
    SET_PIN(ADC0_ADCPSSI_REG, PIN_NO_2); // Start conversion for SS2

    /*  3. Wait for the conversion to complete */
    while (!READ_PIN(ADC0_ADCRIS_REG, PIN_NO_2)); // Wait until conversion is complete

    /*  4. Read the conversion result from the FIFO for SS2 */
    uint16 result = ADC0_ADCSSFIFO2_REG; // Read AIN0 result (PE3)

    /*  5. Clear the interrupt flag for SS2 */
    SET_PIN(ADC0_ADCISC_REG, PIN_NO_2); // Clear the completion flag for SS2

    return result; // Return the AIN0 result
}




uint16 ADC0_Read_AIN1_PE2()
{
    /*  1. Configure SS2 for AIN1 (PE2) */
    ADC0_ADCSSMUX2_REG = 0x1; // MUX0 selects AIN1 (PE2)
    ADC0_ADCSSCTL2_REG = 0x6; // Set SS2 for single-ended input and EOS for AIN1

    /*  2. Trigger the conversion on Sample Sequencer 2 (SS2) */
    SET_PIN(ADC0_ADCPSSI_REG, PIN_NO_2); // Start conversion for SS2

    /*  3. Wait for the conversion to complete */
    while (!READ_PIN(ADC0_ADCRIS_REG, PIN_NO_2)); // Wait until conversion is complete

    /*  4. Read the conversion result from the FIFO for SS2 */
    uint16 result = ADC0_ADCSSFIFO2_REG; // Read AIN1 result (PE2)

    /*  5. Clear the interrupt flag for SS2 */
    SET_PIN(ADC0_ADCISC_REG, PIN_NO_2); // Clear the completion flag for SS2

    return result; // Return the AIN1 result
}

