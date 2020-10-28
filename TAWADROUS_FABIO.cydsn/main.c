#include "project.h"
#include "stdio.h"
#include "InterruptRoutines.h"

int32 digital_pot_value;
int32 digital_photores_value;
uint8_t LED_Status;

int main( void ) 
{
	CyGlobalIntEnable; // Enable global interrupts.
	// Start the components
	ADC_DelSig_Start();
	UART_Start();
    AMux_Start();
	Timer_Start();
    Red_LED_PWM_Start();
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
            //sprintf(message, "Received: %ld\r\n", digital_pot_value);
            //UART_PutString(message);
            PacketReadyFlag = 0;
            
            if(digital_photores_value < THRESHOLD){
                Red_LED_Write(LED_ON);
                LED_Status = 1;
                sprintf(message, "Potentiometer: %ld\r\n", digital_pot_value);
                UART_PutString(message);
            } else{
                Red_LED_Write(LED_OFF);
                LED_Status = 0;
                sprintf(message, "Photoresistor: %ld\r\n", digital_photores_value);
                UART_PutString(message);
            }
        }
    }
}