/**
*   \file main.c
*   \brief Project aim: control the activation of a led through the external light intensity, and to control its intensity with a potentiometer
*   \author: Fabio Tawadrous
*/

#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
#include "Driver.h"

#define HEADER_BYTE 0xA0
#define TAIL_BYTE   0xC0

int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
    
	//  Start the components
    Components_Initialization();
    
    //  Start the interrupts
	isr_ADC_StartEx(Custom_ISR_ADC);
    isr_RX_StartEx(Custom_ISR_RX);
    
	//  Initialize send flag
	PacketReadyFlag	= 0;

    //  Define the first and last byte of the buffer
    DataBuffer[0] = HEADER_BYTE; 
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = TAIL_BYTE;  
      
    for (;;){
        if (PacketReadyFlag == 1)
        {
            PacketReadyFlag = 0;
            UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE);    // Send out the data
        }
    }
}