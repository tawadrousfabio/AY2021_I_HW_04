#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"

int32 value_digit;
int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
	// Start the components
	ADC_DelSig_Start();
	UART_Start();
    AMux_Start();
	Timer_Start();
	isr_ADC_StartEx(Custom_ISR_ADC);
    isr_RX_StartEx(Custom_ISR_RX);
	// Initialize send flag
	PacketReadyFlag	= 0;
    
    AMux_FastSelect(PHOTO_RESISTOR_SAMPLE);
	// Start the ADC conversion
	ADC_DelSig_StartConvert();
    
    DataBuffer[0] = 0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = 0XC0;
    
    char message[20];
    
    for (;;){
        if (PacketReadyFlag == 1)
        {
            // Send out the data
            //UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE); //manda i singoli char dell'array di char. Però si aspetta una dimensione!
            //putstring invece mdnava finchè non trova /0. Qui invece devo definire il bytecount
            sprintf(message, "Received: %ld\r\n", value_digit);
            UART_PutString(message);
            PacketReadyFlag = 0;
            
            if(value_digit < THRESHOLD){
                On_Board_LED_Write(1);
                Red_LED_Write(1);
            } else{
                On_Board_LED_Write(0);
                Red_LED_Write(0);
            }
        }
    
    }
}