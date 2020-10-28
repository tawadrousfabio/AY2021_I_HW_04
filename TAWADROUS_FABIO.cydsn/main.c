#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"
#include "Driver.h"

int32 digital_pot_value;
int32 digital_photores_value;
uint8_t LED_Status;

int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
	// Start the components
	
    Components_Initialization();
    
	isr_ADC_StartEx(Custom_ISR_ADC);
    isr_RX_StartEx(Custom_ISR_RX);
    
	// Initialize send flag
	PacketReadyFlag	= 0;
    
    DataBuffer[0] = 0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = 0XC0;
    
    char message[20];
    
    for (;;){
        if (PacketReadyFlag == 1)
        {
            PacketReadyFlag = 0;
            
            if(digital_photores_value < THRESHOLD){
                Red_LED_Write(LED_ON);
                LED_Status = 1;
                sprintf(message, "Potentiometer: %ld\r\n", digital_pot_value);
                UART_PutString(message);
                // Send out the data
                //UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE); 
            } else{
                Red_LED_Write(LED_OFF);
                LED_Status = 0;
                sprintf(message, "Photoresistor: %ld\r\n", digital_photores_value);
                UART_PutString(message);
                // Send out the data
                //UART_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE); //manda i singoli char dell'array di char. 
            }
        }
    }
}