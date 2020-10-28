/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    #include"cytypes.h"
    #include"stdio.h"
    #define BYTE_TO_SEND 2
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND +1
    #define THRESHOLD 20000 //poi rimetti a 5k
    #define PHOTO_RESISTOR_SAMPLE 0
    #define POTENTIOMETER_SAMPLE 1
    #define LED_ON 1
    #define LED_OFF 0
    CY_ISR_PROTO(Custom_ISR_ADC);
    CY_ISR_PROTO(Custom_ISR_RX);
    uint8_t DataBuffer[TRANSMIT_BUFFER_SIZE];
    volatile uint8 PacketReadyFlag;
#endif

/* [] END OF FILE */
