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
uint8_t external_LED_value;
int32 digital_photores_value;
int32 digital_potentiometer_value;

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
        // Recall to a generic function, which can sample both the sensors, according to the input
        digital_photores_value = Generic_Sensor_Start_Sample(PHOTO_RESISTOR_SAMPLE, 1);
        digital_potentiometer_value = Generic_Sensor_Start_Sample(POTENTIOMETER_SAMPLE, 3);
        
        PacketReadyFlag=1;

        //Now we can check if the photoresistor sampled value is under the fixed threshold
        if(digital_photores_value < THRESHOLD)
        {
            Red_LED_PWM_WriteCompare(255*digital_potentiometer_value/65535); //  Normalized for 8 bit PWM -> resource saved (avoided 16bit PWM)
        } else{
            Red_LED_PWM_WriteCompare(0); //  If we are over the threshold, the LED must be turned OFF.
        }
    } 
}



