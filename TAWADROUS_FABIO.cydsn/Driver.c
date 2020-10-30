/**
*   \brief Source code for the Driver.
*   \author: Fabio Tawadrous
*   
*   In this file what were defined in the driver header file
*   is being implemented.
*/

#include "Driver.h"


/**
*   \brief Start ADC, UART, AMUX, Timer, PWM in the main.c file.
*/
void Components_Initialization(void)
{
    ADC_DelSig_Start();
	UART_Start();
    AMux_Start();
	Timer_Start();
    Red_LED_PWM_Start();
    AMux_FastSelect(PHOTO_RESISTOR_SAMPLE);  //  Of course the first AMUX channel to be sampled is the one related to photoresistor
	ADC_DelSig_StartConvert(); 	// Start the ADC conversion
}

/**
*   \brief this function is called when 'b' or 'B' is pressed. 
*/
void Start_Remote_Session(void)
{
    On_Board_LED_Write(LED_ON);  //  Turn on the on board LED
    Timer_Start();
}

/**
*   \brief this function is called when 's' or 'S' is pressed, and stops the session. 
*/
void Stop_Remote_Session(void)
{
    On_Board_LED_Write(LED_OFF);  //  Turn off the on board LED
    Red_LED_PWM_WriteCompare(0);  //  Turn off the external LED
    Timer_Stop();
}



/**
*   \brief: dynamic function which samples a specific sensor according to the given input
*
*   Before of this I had 2 functions, one for the photoresistor and one for the the potentiometer.
*   I decided to create a dynamic version of the sample functions because if in future we add more sensors to 
*   be sampled, all connected to the same AMux, it would be easy to sample whatever of them, by just recalling
*   this function giving as input the specific channel to be sampled and the starting array index where I would like to 
*   store the bytes that will be sent (e.g. for the photoresistor I'm using the first 2 bytes after the A0 => index = 1 (it will store in 
*   the indexes 1 and 2).
*   The function returns a digital_value, which is the sampled value, which could be stored in a variable (when the function is called), and
*   used for specific purposes.
**/

int32 Generic_Sensor_Start_Sample(uint8_t AMUX_Channel, uint8_t buffer_starting_index)
{
    int32 digital_value; //local variable. It's needed only within the function itself, having the function a return value.
    
    AMux_FastSelect(AMUX_Channel); 
    digital_value = ADC_DelSig_Read32();  //even if this is a blocking function, for this specific application we can use it in the interrupt without problems
    if(digital_value< 0)        digital_value= 0;   
    if(digital_value> 65535)    digital_value= 65535;   
    DataBuffer[buffer_starting_index] = digital_value >> 8;
    DataBuffer[buffer_starting_index+1] = digital_value & 0xFF;
   
    return digital_value;
}

/* [] END OF FILE */
