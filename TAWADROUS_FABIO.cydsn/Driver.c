/**
*   \brief Source code for the Driver.
*   \author: Fabio Tawadrous
*   
*   In this file what were defined in the header file
*   is being implemented.
*/

#include "Driver.h"

extern int32 digital_pot_value;
extern int32 digital_photores_value;
//extern uint8_t LED_Status;

/**
*   \brief Start ADC, UART, Timer, PWM in the main.c file.
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
    On_Board_LED_Write(LED_ON);  //  Turn on the LED
    Timer_Start();
}

/**
*   \brief this function is called when 's' or 'S' is pressed. 
*/
void Stop_Remote_Session(void)
{
    On_Board_LED_Write(LED_OFF);  //  Turn off the on board LED
    Red_LED_PWM_WriteCompare(0);  //  Turn off the external LED
    Timer_Stop();
}

void Photo_Resistor_Start_Sample(void)
{
    AMux_FastSelect(PHOTO_RESISTOR_SAMPLE);  
    digital_photores_value = ADC_DelSig_Read32();
    if(digital_photores_value< 0)        digital_photores_value= 0;
    if(digital_photores_value> 65535)    digital_photores_value= 65535;
    DataBuffer[1] = digital_photores_value >> 8;
    DataBuffer[2] = digital_photores_value & 0xFF;
}

void Potentiometer_Start_Sample(void)
{
    AMux_FastSelect(POTENTIOMETER_SAMPLE);
    digital_pot_value = ADC_DelSig_Read32();
    if(digital_pot_value< 0)        digital_pot_value= 0;
    if(digital_pot_value> 65535)    digital_pot_value= 65535;
    DataBuffer[3] = digital_pot_value >> 8;
    DataBuffer[4] = digital_pot_value & 0xFF;
    Red_LED_PWM_WriteCompare(255*digital_pot_value/65535); //normalized for PWM 8 bit -> resource saved!
}

/* [] END OF FILE */
