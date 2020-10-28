/**
*   \brief Header code for RG(B) Led Driver.
*   \author: Fabio Tawadrous

*   I decided to define a struct type, in order to be 
*   able to use then an array of 7 structs (one for each pattern),
*   which allow to avoid the switch-case during the implementation.
*   
*/
#ifndef _RG_LED_DRIVER_H_
    #define _RG_LED_DRIVER_H_
    #include "project.h"
    
    #define BYTE_TO_SEND 2
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND +1
    #define THRESHOLD 20000 //poi rimetti a 5k
    #define PHOTO_RESISTOR_SAMPLE 0
    #define POTENTIOMETER_SAMPLE 1
    #define LED_ON 1
    #define LED_OFF 0
    
    uint8_t DataBuffer[TRANSMIT_BUFFER_SIZE];
    volatile uint8 PacketReadyFlag;

    
    /**
    *   \brief 
    */
    void Start_Remote_Session(void);
    
    /**
    *   \brief 
    */
    void Stop_Remote_Session(void);
    
    /**
    *   \brief 
    */
    void Photo_Resistor_Start_Sample(void);
    
    /**
    *   \brief 
    */
    void Potentiometer_Start_Sample(void);
    
    /**
    *   \brief 
    */
    void RedLed_WriteCmp();
    

#endif

/* [] END OF FILE */
