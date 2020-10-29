/**
*   \brief Header code for the Driver.
*   \author: Fabio Tawadrous
*   
*/
#ifndef _RG_LED_DRIVER_H_
    #define _RG_LED_DRIVER_H_
    #include "project.h"
    
    #define BYTE_TO_SEND 4 //  2 for potentiometer and 2 for photoresistor
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND +1 //  Start byte - sample bytes - tail byte
    #define THRESHOLD 15000 //  value under which the LED turns ON.
    //poi rimetti a 5k
    
    //These defines are used to make clearer the code and the functions input.
    #define PHOTO_RESISTOR_SAMPLE 0
    #define POTENTIOMETER_SAMPLE 1
    #define LED_ON 1
    #define LED_OFF 0
    
    uint8_t DataBuffer[TRANSMIT_BUFFER_SIZE]; 
    volatile uint8 PacketReadyFlag;
    volatile uint8 LED_Status;
    
    int32 digital_photores_value;
    int32 digital_pot_value;
    /**
    *   \brief starts the components. It will be used in the main.c file
    */
    void Components_Initialization(void);
    
    /**
    *   \brief this function is called when 'b' or 'B' is pressed. It turns ON the on board led, and starts the timer
    */
    void Start_Remote_Session(void);
    
    /**
    *   \brief this function is called when 's' or 'S' is pressed. It turns OFF the on board led, and stops the timer
    */
    void Stop_Remote_Session(void);
    
    /**
    *   \brief this function is used to sample the photo resistor
    */
    void Photo_Resistor_Start_Sample(void);
    
    /**
    *   \brief this function is used to sample the potentiometer
    */
    void Potentiometer_Start_Sample(void);
    
    
#endif

/* [] END OF FILE */
