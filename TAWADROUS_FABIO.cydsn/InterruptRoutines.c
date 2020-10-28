// Include header
#include"InterruptRoutines.h"
// Include required header files
#include"project.h"


// Variables declaration

extern int32 digital_pot_value;
extern int32 digital_photores_value;
extern uint8_t LED_Status;

uint8 ch_receveid; //deve essere un preciso carattere quello che arriva.
uint8 Remote_Start = 0;

CY_ISR(Custom_ISR_ADC){
    // Read Timer status register to bring interrupt line low
    Timer_ReadStatusRegister();
    if(Remote_Start == 1){
        //1. campiono continuamente la luce 
        AMux_FastSelect(PHOTO_RESISTOR_SAMPLE);
        digital_photores_value = ADC_DelSig_Read32();
        if(digital_photores_value< 0)        digital_photores_value= 0;
        if(digital_photores_value> 65535)    digital_photores_value= 65535;
        DataBuffer[1] = digital_photores_value >> 8;
        DataBuffer[2] = digital_photores_value & 0xFF;
        
        PacketReadyFlag=1;
        
        //Se il LED è acceso allora con il potenziometro agisco sull'intensità di luce
        if(LED_Status == 1){
            //visto che il LED è ON => posso controllare l'intensità
            AMux_FastSelect(POTENTIOMETER_SAMPLE);
            digital_pot_value = ADC_DelSig_Read32();
            if(digital_pot_value< 0)        digital_pot_value= 0;
            if(digital_pot_value> 65535)    digital_pot_value= 65535;
            DataBuffer[1] = digital_pot_value >> 8;
            DataBuffer[2] = digital_pot_value & 0xFF;
            Red_LED_PWM_WriteCompare(digital_pot_value);
        
        }
        
        
    }
}

CY_ISR(Custom_ISR_RX){
// Non-blocking call to get the latest data recieved
    ch_receveid= UART_GetChar();
    // Set flags based on UART command
    switch(ch_receveid){
        case'B':
        case'b':
            Remote_Start= 1;
            //On_Board_LED_Write(1);
            Timer_Start();
            break;
        case'S':
        case's':
            Remote_Start = 0;
            On_Board_LED_Write(0);
            Timer_Stop();
            break;
        default:
        break;    
    }
}
