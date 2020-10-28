/**
*   \brief Source code for RGB Led Driver.
*   \author: Fabio Tawadrous
*   
*   In this file what were defined in the header file
*   is being implemented.
*/

#include "Driver.h"

extern int32 digital_pot_value;
extern int32 digital_photores_value;
extern uint8_t LED_Status;

void Components_Initialization(void)
{
    ADC_DelSig_Start();
	UART_Start();
    AMux_Start();
	Timer_Start();
    Red_LED_PWM_Start();
    AMux_FastSelect(PHOTO_RESISTOR_SAMPLE);
	// Start the ADC conversion
	ADC_DelSig_StartConvert();
}

void Start_Remote_Session(void)
{
    On_Board_LED_Write(LED_ON);
    Timer_Start();
}

void Stop_Remote_Session(void)
{
    On_Board_LED_Write(LED_OFF);
    Red_LED_PWM_WriteCompare(0);
    Timer_Stop();
}

void Photo_Resistor_Start_Sample(void)
{
//1. campiono continuamente la luce 
    AMux_FastSelect(PHOTO_RESISTOR_SAMPLE);
    digital_photores_value = ADC_DelSig_Read32();
    if(digital_photores_value< 0)        digital_photores_value= 0;
    if(digital_photores_value> 65535)    digital_photores_value= 65535;
    DataBuffer[1] = digital_photores_value >> 8;
    DataBuffer[2] = digital_photores_value & 0xFF;
}

void Potentiometer_Start_Sample(void)
{
//visto che il LED è ON => posso controllare l'intensità
    AMux_FastSelect(POTENTIOMETER_SAMPLE);
    digital_pot_value = ADC_DelSig_Read32();
    if(digital_pot_value< 0)        digital_pot_value= 0;
    if(digital_pot_value> 65535)    digital_pot_value= 65535;
    DataBuffer[1] = digital_pot_value >> 8;
    DataBuffer[2] = digital_pot_value & 0xFF;
    Red_LED_PWM_WriteCompare(digital_pot_value);
}


/**
*   \brief This function is specific for the PWM red channel, and modifies the compare value & type, and the period.
*/
void RGLed_WriteCmp()//(Cmp p)
{
    //RGLed_WriteGreenCmp(p.green_cmp, p.green_cmp_type, p.green_period); //set the green channel
}


/* [] END OF FILE */
