/**
*   \brief Source code for the implementation of what happens during the two interrupts
*   \author: Fabio Tawadrous
*/

#include"InterruptRoutines.h"
#include "project.h"
#include "Driver.h"

// Variables declaration

uint8 session_char; 
uint8 Remote_Start = 0;

/**
*   \brief in this ISR we check the last char received. If b or B -> start the session, if s or S -> end it.
*/

CY_ISR(Custom_ISR_RX){
    session_char = UART_GetChar();
    
    // Set flags based on UART command
    switch(session_char)
    {
        case'B':
        case'b':
            Remote_Start= 1;
            Start_Remote_Session(); 
            break;
        case'S':
        case's':
            Remote_Start = 0;
            Stop_Remote_Session();
            break;
        default:
        break;    
    }
}


CY_ISR(Custom_ISR_ADC){
    Timer_ReadStatusRegister(); // Read Timer status register to bring interrupt line low
    if(Remote_Start == 1)
    {  
        Photo_Resistor_Start_Sample(); //if the session started, start also to sample the photoresistor
        PacketReadyFlag=1;
        //check if the photoresistor value < threshold => flag = 1
        if(digital_photores_value < THRESHOLD)
        {
            LED_Status = 1; 
            Potentiometer_Start_Sample(); //if LED is ON, sample also the potentiometer
        } else{
            //  if the LED is not ON, we not sample the potentiometer, and the graph will show only the photoresistor values
            DataBuffer[3] = 0;
            DataBuffer[4] = 0;
            LED_Status = 0; 
        }
    } 
}



