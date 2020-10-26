// Include header
#include"InterruptRoutines.h"
// Include required header files
#include"project.h"
// Variables declaration
int32 value_digit;
uint8 ch_receveid; //deve essere un preciso carattere quello che arriva.
uint8 SendBytesFlag=0;

CY_ISR(Custom_ISR_ADC){
    // Read Timer status register to bring interrupt line low
    Timer_ReadStatusRegister();
    if(SendBytesFlag==1){
        value_digit= ADC_DelSig_Read32();    
        if(value_digit< 0)        value_digit= 0;
        if(value_digit> 65535)    value_digit= 65535;
        DataBuffer[1] = value_digit >> 8;
        DataBuffer[2] = value_digit & 0xFF;
        
        PacketReadyFlag=1;
    }
}

CY_ISR(Custom_ISR_RX){
// Non-blocking call to get the latest data recieved
    ch_receveid= UART_GetChar();
    // Set flags based on UART command
    switch(ch_receveid){
        case'A':
        case'a':
            SendBytesFlag= 1;
            Pin_LED_Write(1);
            Timer_Start();
            break;
        case'B':
        case'b':
            SendBytesFlag= 0;
            Pin_LED_Write(0);
            Timer_Stop();
            break;
        default:
        break;    
    }
}
