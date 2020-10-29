// Include header
#include"InterruptRoutines.h"
// Include required header files
#include "project.h"
#include "Driver.h"

// Variables declaration

extern uint8_t LED_Status;

uint8 session_char; //deve essere un preciso carattere quello che arriva.
uint8 Remote_Start = 0;

CY_ISR(Custom_ISR_ADC){
    // Read Timer status register to bring interrupt line low
    Timer_ReadStatusRegister();
    if(Remote_Start == 1){
        
        Photo_Resistor_Start_Sample();
        PacketReadyFlag=1;
        
        //Se il LED è acceso allora con il potenziometro agisco sull'intensità di luce
        if(LED_Status == 1){
            
            Potentiometer_Start_Sample();
        } else Red_LED_PWM_WriteCompare(0); 
    } 
}

CY_ISR(Custom_ISR_RX){
// Non-blocking call to get the latest data recieved
    session_char = UART_GetChar();
    // Set flags based on UART command
    switch(session_char){
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
