/**
*   \file main.c
*   \brief Project aim: control the activation of a led through the external light intensity, and control the led intensity with a potentiometer
*   \author: Fabio Tawadrous
*/

#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
#include "Driver.h"


//  Defines for the starting and ending byte of the buffer
#define HEADER_BYTE 0xA0
#define TAIL_BYTE   0xC0

int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
    
	//  Recall to a function which starts the components
    Components_Initialization();
    
    //  Start the interrupts
	isr_ADC_StartEx(Custom_ISR_ADC);
    isr_RX_StartEx(Custom_ISR_RX);
    
	//  Initialize send flag
	PacketReadyFlag	= 0;

    //  Associate the first and last byte of the buffer
    DataBuffer[0] = HEADER_BYTE; 
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = TAIL_BYTE;  
      
    for (;;){
        if (PacketReadyFlag == 1)  //  If data are ready to be sent
        {
            UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE);    // Send out the data
            PacketReadyFlag = 0;
        }
    }
}