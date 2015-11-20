/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*
 * 
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * + Pin number +  Rivet Board pin |  PIN   | Label/Name      | Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital Low      |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 0          | 0 -> RX          |  PA00  |                 | EIC/EXTINT[0] 				         	      *SERCOM0/PAD[0]                  TCC2/WO[0]
 * | 1          | 1 <- TX          |  PA01  |                 | EIC/EXTINT[1] 								  *SERCOM0/PAD[1]                  TCC2/WO[1]
 * | 2          | 2                |  PA14  |                 | EIC/EXTINT[14]                                 SERCOM2/PAD[2]  SERCOM4/PAD[2]  TC3/WO[0]   TCC0/WO[4]
 * | 3          | ~3               |  PA05  |                 | EIC/EXTINT[5]  ADC/AIN[5]            PTC/Y[3]  SERCOM0/PAD[1]  				  *TCC0/WO[1]
 * | 4          | ~4               |  PB17  |                 | EIC/EXTINT[1]  								   SERCOM5/PAD[1]				  *TC6/WO[0]   TCC0/WO[5]
 * | 5          | ~5               |  PA22  |                 | EIC/EXTINT[6]                        PTC/X[10] SERCOM3/PAD[0]  SERCOM5/PAD[0] *TC4/WO[0]   TCC0/WO[4]
 * | 6          | ~6               |  PA21  |                 | EIC/EXTINT[5]                        PTC/X[9]  SERCOM5/PAD[3]  SERCOM3/PAD[3] *TC7/WO[1]   TCC0/WO[7]
 * | 7          | 7                |  PB23  |                 | EIC/EXTINT[7]                         		   SERCOM5/PAD[3]  				   TC7/WO[0]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Digital High     |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 8          | ~8               |  PB30  |                 | EIC/EXTINT[14]								   SERCOM5/PAD[0]                 *TCC0/WO[0]
 * | 9          | ~9               |  PA20  |                 | EIC/EXTINT[4]								   SERCOM5/PAD[2]  SERCOM3/PAD[2] *TC7/WO[0]    TCC0/WO[6]
 * | 10         | ~10              |  PA16  | SS              | EIC/EXTINT[0]                        PTC/X[4]  SERCOM1/PAD[0]  SERCOM3/PAD[0] *TCC2/WO[0]   TCC0/WO[6]
 * | 11         | ~11              |  PA17  | MOSI            | EIC/EXTINT[1]                        PTC/X[5]  SERCOM1/PAD[1] +SERCOM3/PAD[1] *TCC2/WO[1]   TCC0/WO[7]
 * | 12         | ~12              |  PA18  | MISO            | EIC/EXTINT[2]                        PTC/X[6]  SERCOM1/PAD[2] +SERCOM3/PAD[2] *TC3/WO[0]    TCC0/WO[2]
 * | 13         | ~13              |  PA19  | LED, SCK        | EIC/EXTINT[3]                        PTC/X[7]  SERCOM1/PAD[3] +SERCOM3/PAD[3] *TC3/WO[1]    TCC0/WO[3]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Analog Connector |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 14         | A0               |  PA02  | A0              | EIC/EXTINT[2] *ADC/AIN[0]  DAC/VOUT  PTC/Y[0]
 * | 15         | A1               |  PA03  | A1              | EIC/EXTINT[3] *ADC/AIN[1]            PTC/Y[1] 
 * | 16         | A2               |  PA06  | A2              | EIC/EXTINT[6] *ADC/AIN[6]  AC/AIN[2] PTC/Y[4]                  SERCOM0/PAD[2]  TCC1/WO[0]
 * | 17         | A3               |  PA04  | A3              | EIC/EXTINT[4] *ADC/AIN[4]  AC/AIN[0] PTC/Y[2]                  SERCOM0/PAD[0]  TCC0/WO[0]
 * | 18         | A4/SDA           |  PA08  | A4              | EIC/NMI       *ADC/AIN[16]   	     PTC/X[0]  SERCOM0/PAD[0] +SERCOM2/PAD[0]  TCC0/WO[0]   TCC1/WO[2]
 * | 19         | A5/SCL           |  PA09  | A5              | EIC/EXTINT[9] *ADC/AIN[17]           PTC/X[1]  SERCOM0/PAD[1] +SERCOM2/PAD[1]  TCC0/WO[1]   TCC1/WO[3]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Cell Module      |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------     
 * | 20			| TXD0             |  PA12  | TXDO            | EIC/EXTINT[12]  		             		   SERCOM2/PAD[0] *SERCOM4/PAD[0]  TCC2/WO[0]   TCC0/WO[6]
 * | 21			| RXD0             |  PA13  | RXDO            | EIC/EXTINT[13]  		             		   SERCOM2/PAD[1] *SERCOM4/PAD[1]  TCC2/WO[1]   TCC0/WO[7]
 * | 22			| DTR              |  PA23  | DTR             | EIC/EXTINT[7]                        PTC/X[11] SERCOM3/PAD[1]  SERCOM5/PAD[1]  TC4/WO[1]    TCC0/WO[5]
 * | 23			| DSR              |  PA27  | DSR             | EIC/EXTINT[15]
 * | 24			| DCD              |  PA28  | DCD             | EIC/EXTINT[8]
 * | 25			| EMERG_OFF		   |  PB04  | EMERG_OFF    	  |                                                                                                                       
 * | 26			| STATUS           |  PB05  | STATUS          | EIC/EXTINT[5]  ADC/AIN[13]           PTC/Y[11] 
 * | 27			| IGT	           |  PB06  | IGT             | EIC/EXTINT[6]  ADC/AIN[14]           PTC/Y[12] 
 * | 28			| PWR_IND          |  PB08  | PWR_IND         | EIC/EXTINT[8]  ADC/AIN[2] 			 PTC/Y[14]                 SERCOM4/PAD[0]  TC4/WO[0]
 * | 29			| WAKEUP           |  PB09  | WAKEUP          | EIC/EXTINT[9]  ADC/AIN[3] 			 PTC/Y[15]                 SERCOM4/PAD[1]  TC4/WO[1]
 * | 30			| LC_IND           |  PB10  | LC_IND          | EIC/EXTINT[10]                                                 SERCOM4/PAD[2]  TC5/WO[0]    TCC0/WO[4]
 * | 31			| RING             |  PB13  | RING            | EIC/EXTINT[13]                       PTC/X[13] SERCOM4/PAD[1]  				   TC4/WO[1]    TCC0/WO[7]
 * | 32			| RTS              |  PB14  | RTS             | EIC/EXTINT[14]                       PTC/X[14]*SERCOM4/PAD[2]  				   TC5/WO[0]
 * | 33			| CTS              |  PB15  | CTS             | EIC/EXTINT[15]                       PTC/X[15]*SERCOM4/PAD[3]  				   TC5/WO[1]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | Miscellaneous    |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------     
 * | 34			| !RS232_EN!	   |  PB07  | !RS232_EN!      | EIC/EXTINT[7]  ADC/AIN[15]           PTC/Y[13] 
 * | 35			| SDI12			   |  PB04	| SDI-12		  | EIC/EXTINT[4]  ADC/AIN[12]           PTC/Y[10] 
 * | 36			| CS_SD			   |  PB31	| CS_SD			  | EIC/EXTINT[15]                                                 SERCOM5/PAD[1]  TCC0/WO[1]   TCC1/WO[3]
 * | 37			| XBEE_RST		   |  PB00	| XBEE_RST		  | EIC/EXTINT[0]  ADC/AIN[8] 			 PTC/Y[6]                  SERCOM5/PAD[2]  TC7/WO[0]
 * | 38 		| RS485_DIR		   |  PB01  | RS485_DIR		  | EIC/EXTINT[1]  ADC/AIN[9] 			 PTC/Y[7]                  SERCOM5/PAD[3]  TC7/WO[1]
 * | 39			| RS485_TX		   |  PB02  | RS485_TX		  | EIC/EXTINT[2]  ADC/AIN[10] 			 PTC/Y[8]                 *SERCOM5/PAD[0]  TC6/WO[0]
 * | 40			| RS485_RX		   |  PB03  | RS485_RX		  | EIC/EXTINT[3]  ADC/AIN[11] 			 PTC/Y[9]                 *SERCOM5/PAD[1]  TC6/WO[1]
 * +------------+------------------+--------+-----------------+-------------------------------------------------------------------------------------------------------- 
 * |            | Wire             |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 41         | A4/SDA           |  PA08  | SDA             | EIC/NMI       +ADC/AIN[16]   	     PTC/X[0]  SERCOM0/PAD[0] *SERCOM2/PAD[0]  TCC0/WO[0]   TCC1/WO[2]
 * | 42         | A5/SCL           |  PA09  | SCL             | EIC/EXTINT[9] +ADC/AIN[17]           PTC/X[1]  SERCOM0/PAD[1] *SERCOM2/PAD[1]  TCC0/WO[1]   TCC1/WO[3]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | SPI  			   |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 43         | 11               |  PA17  | MOSI            | EIC/EXTINT[1]                        PTC/X[5]  SERCOM1/PAD[1] *SERCOM3/PAD[1] +TCC2/WO[1]   TCC0/WO[7]
 * | 44         | 12               |  PA18  | MISO            | EIC/EXTINT[2]                        PTC/X[6]  SERCOM1/PAD[2] *SERCOM3/PAD[2] +TC3/WO[0]    TCC0/WO[2]
 * | 45         | 13               |  PA19  | SCK, LED        | EIC/EXTINT[3]                        PTC/X[7]  SERCOM1/PAD[3] *SERCOM3/PAD[3] +TC3/WO[1]    TCC0/WO[3]
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * |            | USB              |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 46         |                  |  PA24  | USB_NEGATIVE    | *USB/DM
 * | 47         |                  |  PA25  | USB_POSITIVE    | *USB/DP
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------   
 * |            | DUMMY            |        |                 |
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 48         |                  |  PB11  | DUMMY           | 
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------   
 */
 
#include "variant.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // 0..13 - Digital pins
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1)
  { PORTA,  0, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 }, 			// D0 RX, SERCOM0/PAD[0]
  { PORTA,  1, PIO_SERCOM, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 },			// D1 TX, SERCOM0/PAD[1]

  // 2..12
  // Digital Low
  { PORTA, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14 },							// D2
  { PORTA,  5, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 }, 		// D3, TCC0/WO[1]
  { PORTB, 17, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 },   // D4, TC6/WO[0]
  { PORTA, 22, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, 	// D5, TC4/WO[0]
  { PORTA, 21, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM7_CH1, TC7_CH1, EXTERNAL_INT_5 }, 			// D6, TC7/WO[1]
  { PORTB, 23, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 },								// D7

  // Digital High
  { PORTB, 30, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_14 }, 	// D8,  TCC0/WO[0]
  { PORTA, 20, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM7_CH0, TC7_CH0, EXTERNAL_INT_4 }, 		// D9,  TC7/WO[0]
  { PORTA, 16, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH0, TCC2_CH0, EXTERNAL_INT_0 }, 	// D10, TCC2/WO[0]
  { PORTA, 17, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC2_CH1, EXTERNAL_INT_1 }, 	// D11, TCC2/WO[1]
  { PORTA, 18, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH0, TC3_CH0, EXTERNAL_INT_2 }, 		// D12, TC3/WO[0]

  // 13 (LED)
  { PORTA, 19, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH1, TC3_CH1, EXTERNAL_INT_3 }, 		// D13, TC3/WO[1]

  // 14..19 - Analog pins
  // --------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, 				// A0, ADC/AIN[0]
  { PORTA,  3, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, 				// A1, ADC/AIN[1]
  { PORTA,  6, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, 				// A2, ADC/AIN[6]
  { PORTA,  4, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 }, 				// A3, ADC/AIN[4]
  { PORTA,  8, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel16, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI }, 			// A4, ADC/AIN[16]
  { PORTA,  9, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel17, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 }, 				// A5, ADC/AIN[17]
  
  // 20..33 - Gemalto pins
  // ---------------------
  { PORTA, 12, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 }, 	// TXD0, SERCOM4/PAD[0] 
  { PORTA, 13, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, 	// RXD0, SERCOM4/PAD[1] 
  { PORTA, 23, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, 			// DTR
  { PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 }, 			// DSR
  { PORTA, 28, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 }, 			// DCD
  { PORTB,  4, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 		// EMERG_OFF
  { PORTB,  5, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 }, 			// STATUS
  { PORTB,  6, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, 			// IGT
  { PORTB,  8, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 }, 			// PWR_IND
  { PORTB,  9, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 }, 			// WAKEUP
  { PORTB, 10, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, 			// LC_IND
  { PORTB, 13, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, 			// RING
  { PORTB, 14, PIO_SERCOM,  PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 },		 	// RTS, SERCOM4/PAD[2] 
  { PORTB, 15, PIO_SERCOM,  PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13 }, 			// CTS, SERCOM4/PAD[3] 
  
  // 34..40 - Miscellaneous pins
  // ---------------------------
  { PORTB,  7, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, 			// !RS232_EN!
  { PORTB,  4, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 },			// SDI12
  { PORTB, 31, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },		// CS_SD
  { PORTB,  0, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 },			// XBEE_RST
  { PORTB,  1, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 },			// RS485_DIR
  { PORTB,  2, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, 		// RS485_TX, SERCOM5/PAD[0]
  { PORTB,  3, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, 		// RS485_RX, SERCOM5/PAD[1]
  
  // 41/42 I2C (SDA/SCL)
  // -------------------
  { PORTA,  8, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 		// SDA, SERCOM2/PAD[0]
  { PORTA,  9, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 		// SCL, SERCOM2/PAD[1]
    
  // 43..45 - SPI
  // ------------
  { PORTA, 17, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 		// MOSI, SERCOM1/PAD[1]
  { PORTA, 18, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 		// MISO, SERCOM1/PAD[2]
  { PORTA, 19, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 		// SCK, SERCOM1/PAD[3]
  
  // 46/47 - USB
  // --------------------
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 				// 46, USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 				// 47, USB/DP
  
  // 48 - DUMMY
  // ----------
  { PORTB, 11, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 			// 48, DUMMY

} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial1( &sercom0, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;
Uart Serial2( &sercom4, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX ) ;
Uart Serial3( &sercom5, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX ) ;

void SERCOM0_Handler()
{
  Serial1.IrqHandler();
}

void SERCOM4_Handler()
{
  Serial2.IrqHandler();
}

void SERCOM5_Handler()
{
  Serial3.IrqHandler();
}

