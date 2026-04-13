/*
 * File:   ECU2_Sensor.c
 * Author: DELL
 *
 * Created on 7 April, 2026, 1:55 AM
 */


#include "ECU2_Sensor.h"
#include "ADC.h"
//#include "can.h"
#include "msg_id.h"
#include "Digital_Keypad.h"
//#include "uart.h"

int rpm;
char digit[10] = {0xE7,0x21,0xCB,0x6B,0x2D,0X6E,0xEE,0x23,0xEF,0x6F};
char ssd[4];  
char flag = 0;
char status;
int delay = 0;


void display(char *data)
{
    for( int i = 0 ; i < 4 ; i++ )
    {
        PORTD = data[i];   // Send segment data
        PORTA = (unsigned char)((PORTA & 0XF0) | (1 << i)); // Select digit
        for( int delay_1 = 500; delay_1--; ); // Multiplexing delay
    }
}

uint16_t get_rpm()
{
    //Implement the rpm function
    rpm = ((unsigned long)read_adc(CHANNEL4) * 6000) / 1023;
    
    // Convert count to 4-digit display
    ssd[0] = digit[(rpm / 1000)%10];
    ssd[1] = digit[(rpm / 100)%10];
    ssd[2] = digit[(rpm / 10)%10];
    ssd[3] = digit[rpm % 10];

    display(ssd);  // Refresh display    
}

/*uint16_t get_engine_temp()
{
    //Implement the engine temperature function
}*/

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    unsigned char key=read_digital_keypad(STATE_CHANGE);
    if(key==0x0e)
    {
        status=1;
        flag=0;
        delay=0;
    }
    else if(key==0x0b)
    {
       status=2; 
       delay=0;
       flag=0;
    }
    else if(key==0x0d)
    {
        status=0;
        delay=0;
        flag=0;
        
    }
    if(status==0)
    {
      
       LEFT_IND_OFF();
         
       RIGHT_IND_OFF();
        
    }
    else if(status==1)
    {
        RIGHT_IND_OFF();
        if(delay++>=300)
        {
            if(flag==0)
            {
                LEFT_IND_ON();
                flag=1;
            }
            else
            {
                LEFT_IND_OFF();
                flag=0;
            }
            delay=0;
        }
    }
    else if(status==2)
    {
        LEFT_IND_OFF();
        if(delay++>=300)
        {
            if(flag==0)
            {
                RIGHT_IND_ON();
                flag=1;
            }
            else
            {
                RIGHT_IND_OFF();
                flag=0;
            }
            delay=0;
        }
    }        
    return status;    
}
