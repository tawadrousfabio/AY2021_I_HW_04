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
*   In this ISR we check the last char received. If b or B the session will be started.
*   if s or S is pressed, the session will be ended.
*   If another key is pressed, nothing happens.
*/

CY_ISR(Custom_ISR_RX){
    session_char = UART_GetChar();
    
    // Set flags based on UART command
    switch(session_char)
    {
        case'B':
        case'b':
            Remote_Start= 1;  //flag which allows the sampling to start in the other interrupt.
            Start_Remote_Session(); //function which starts the timer and turn ON the on board led.
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

/**
*
* In this ISR we check if the flag is 1 (which means that b or B was pressed). 
* Only if the flag is 1 we can start to sample both the sensors. 
* I decided to sample both the sensors (and plot both, always), but the LED intensity
* is modulated ONLY AND ONLY IF the ambient light intensity is below the threshold.
**/

CY_ISR(Custom_ISR_ADC){
    Timer_ReadStatusRegister(); // Read Timer status register to bring interrupt line low
    if(Remote_Start == 1)
    {  
        // Recall 2 functions which sample respectively the 2 sensors.
        Photo_Resistor_Start_Sample(); 
        Potentiometer_Start_Sample(); 
        
        PacketReadyFlag=1;
        
        //check if the photoresistor value < threshold => flag = 1
        if(digital_photores_value < THRESHOLD)
        {
            Red_LED_PWM_WriteCompare(255*digital_pot_value/65535); //normalized for 8 bit PWM -> resource saved!
        } else{
            //  if the LED is not ON, we not sample the potentiometer, and the graph will show only the photoresistor values
            Red_LED_PWM_WriteCompare(0);
        }
    } 
}



