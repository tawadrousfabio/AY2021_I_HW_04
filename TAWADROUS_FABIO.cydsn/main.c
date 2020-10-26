#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
	// Start the components
	ADC_DelSig_Start();
	UART_Start();
	//Timer_Start();
	isr_ADC_StartEx(Custom_ISR_ADC);
    isr_RX_StartEx(Custom_ISR_RX);
	// Initialize send flag
	PacketReadyFlag	= 0;
	// Start the ADC conversion
	ADC_DelSig_StartConvert();
    
    DataBuffer[0] = 0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = 0XC0;
    
    for (;;){
        if (PacketReadyFlag == 1)
        {
            // Send out the data
            UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE); //manda i singoli char dell'array di char. Però si aspetta una dimensione!
            //putstring invece mdnava finchè non trova /0. Qui invece devo definire il bytecount!!
            PacketReadyFlag = 0;
        }
    }
}