/**
*   \brief Header code for the Driver.
*   \author: Fabio Tawadrous
*   
*/
#ifndef _RG_LED_DRIVER_H_
    #define _RG_LED_DRIVER_H_
    #include "project.h"
    
    #define BYTE_TO_SEND 4                                  //  Two for photoresistor and two for potentiometer
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND +1        //  Start byte - sample bytes - tail byte
    #define THRESHOLD 15000                                 //  Value under which the LED must turn ON.

    
    //  These defines are used in the sample function, to define which is the AMUX channel, and which is the starting buffer index
    #define PHOTO_RESISTOR_SAMPLE 0  
    #define POTENTIOMETER_SAMPLE 1
    #define PHOTO_RESISTOR_BUFFER_INDEX 1
    #define POTENTIOMETER_BUFFER_INDEX 3
    
    //  Defines used to define if the led is on or off in a clearer way.
    #define LED_ON 1
    #define LED_OFF 0
    
    uint8_t DataBuffer[TRANSMIT_BUFFER_SIZE];       //  Array with the bytes to be sent
    volatile uint8 PacketReadyFlag;                 //  Flag used to enable the data sending

    
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
    *   \brief used to sample any sensor according to the input channel, and store the value in dataBuffer starting from the input Buffer index
    */
    int32 Generic_Sensor_Start_Sample(uint8_t AMUX_Channel, uint8_t buffer_starting_index);
    
#endif

/* [] END OF FILE */
