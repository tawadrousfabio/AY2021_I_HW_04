/**
*   \file main.c
*   \brief Project aim: to control the activation of a led through a photoresistor, and to control its intensity with a potentiometer
*   \author: Fabio Tawadrous
*/

#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
#include "Driver.h"

int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
	// Start the components
	
    Components_Initialization();
    
    //  Start the interrupts
	isr_ADC_StartEx(Custom_ISR_ADC);
    isr_RX_StartEx(Custom_ISR_RX);
    
	// Initialize send flag
	PacketReadyFlag	= 0;
    LED_Status = 0;
    DataBuffer[0] = 0xA0; //  First byte
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = 0XC0;  // Tail byte
      
    for (;;){
        if (PacketReadyFlag == 1)
        {
            PacketReadyFlag = 0;
            UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE); // Send out the data
        }
    }
}