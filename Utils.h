/*
 * Utils.h
 *
 * Created: 11/3/2023 1:04:40 PM
 *  Author: Zyad Ayman
 */ 


#ifndef UTILS_H_
#define UTILS_H_
//MACROS FOR KEYPAD
#define ZERO_KEYPAD 13
#define ONE_KEYPAD 8
#define TWO_KEYPAD 9
#define THREE_KEYPAD 10
#define FOUR_KEYPAD 4
#define FIVE_KEYPAD 5
#define SIX_KEYPAD 6
#define SEVEN_KEYPAD 0
#define EIGHT_KEYPAD 1
#define NINE_KEYPAD 2
#define DIVIDE_KEYPAD 3
#define MULTIPLY_KEYPAD 7
#define MINUS_KEYPAD 11
#define PLUS_KEYPAD 15
#define EQUAL_KEYPAD 14
#define ON_C_KEYPAD  12
//MACROS FOR NUMBERS
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
//FOR LEDS ON/OFF
#define LED_ON 1
#define LED_OFF 0
//For Push Buttons
//CONSIDERING PULLUP ACTIVATION
#define NOT_PRESSED 1
#define PRESSED_ 0
//MACROS FOR SEVEN SEGMENTS OPERATION 
/* ORDER OF SGEMENTS LETTERS
	   			     hgfedcba
*/	
//for common cathode
#define ZERO_SEG_K 0b00111111
#define ONE_SEG_K	 0b00000110
#define TWO_SEG_K  0b01011011
#define THREE_SEG_K 0b01001111
#define FOUR_SEG_K 0b01100110
#define FIVE_SEG_K 0b00101111
#define SIX_SEG_K  0b01111101
#define SEVEN_SEG_K 0b00000111
#define EIGHT_SEG_K 0b01111111
#define NINE_SEG_K 0b01100111

/*********************************/

//for common anode
//ORDER OF SGEMENTS LETTERS
//				     hgfedcba

#define ZERO_SEG_A 0b01000000
#define ONE_SEG_A  0b01111001
#define TWO_SEG_A  0b00100100
#define THREE_SEG_A 0b00110000
#define FOUR_SEG_A 0b00011001
#define FIVE_SEG_A 0b01010000
#define SIX_SEG_A  0b00000010
#define SEVEN_SEG_A 0b01111000
#define EIGHT_SEG_A 0b00000000
#define NINE_SEG_A 0b00011000


/********************************************/

//MACROS FOR ELIMINATING THE MAGIC NUMBERS FOR THE DIRECTION PORTS >> INPUT | OUTPUT
#define INPUT 0
#define OUTPUT 1
//MACROS FOR PIN NUMBER TO ELIMINATE MAGIC NUMBERS FOR USAGE WITH PORTS AND DDRS REGISTERS INSTEAD OF WRITING 0 >> 7
#define PIN_NO_0 0
#define PIN_NO_1 1
#define PIN_NO_2 2
#define PIN_NO_3 3
#define PIN_NO_4 4
#define PIN_NO_5 5
#define PIN_NO_6 6
#define PIN_NO_7 7











#define BIT_NO_0 0
#define BIT_NO_1 1
#define BIT_NO_2 2
#define BIT_NO_3 3
#define BIT_NO_4 4
#define BIT_NO_5 5
#define BIT_NO_6 6
#define BIT_NO_7 7
#define BIT_NO_8 8
#define BIT_NO_9 9
#define BIT_NO_10 10
#define BIT_NO_11 11
#define BIT_NO_12 12
#define BIT_NO_13 13
#define BIT_NO_14 14
#define BIT_NO_15 15
#define BIT_NO_16 16
#define BIT_NO_17 17
#define BIT_NO_18 18
#define BIT_NO_19 19
#define BIT_NO_20 20
#define BIT_NO_21 21
#define BIT_NO_22 22
#define BIT_NO_23 23
#define BIT_NO_24 24
#define BIT_NO_25 25
#define BIT_NO_26 26
#define BIT_NO_27 27
#define BIT_NO_28 28
#define BIT_NO_29 29
#define BIT_NO_30 30
#define BIT_NO_31 31


//MACROS FOR BITWISE OPERATIONS
#define READ_WHOLE_REG(REG) REG
#define READ_PIN(REG,PIN_NO) ((REG & (1<<PIN_NO))>>PIN_NO)
#define SET_PIN(REG,PIN_NO) (REG |= (1<<PIN_NO))
#define WRITE_BIT(REG,PIN_NO,PIN_Value) (REG = (PIN_Value<<PIN_NO))
#define WRITE_REG(REG,REG_VALUE) (REG = REG_VALUE)
#define CLR_PIN(REG,PIN_NO) (REG &= ~(1<<PIN_NO))
#define TOGGLE_BIT(REG,PIN_NO) (REG ^= (1<<PIN_NO))
#define TOGGLE_REG(REG) (REG ^= 0xFFFFFFFF)








#endif /* UTILS_H_ */
