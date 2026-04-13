/*
 * File:   ECU1_Sensor.c
 * Author: DELL
 *
 * Created on 7 April, 2026, 12:50 AM
 */


#include "ECU1_Sensor.h"
#include "ADC.h"
#include "CAN.h"
#include "msg_id.h"
#include "CLCD.h"
//#include "uart.h"

int speed;
char str[3];
char gear[9][3] = {"ON","GN","G1","G2","G3","G4","G5","GR","C_"};
int index = 0;
unsigned char key;
uint16_t msg_id;
uint8_t data[4];
uint8_t len;


uint16_t get_speed()
{
    // Implement the speed function
    speed = read_adc(CHANNEL4)/10.33;
    str[0] = (speed/10) + 48;
    str[1] = (speed%10) + 48;
    str[2] = '\0';
   
    can_transmit(SPEED_MSG_ID,str,2);
    __delay_ms(80);
    can_receive(&msg_id,data,&len);
    data[len] = '\0';
    clcd_print("SPEED",LINE1(0));
    clcd_print(data,LINE2(1));
    
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    
    key = read_switches(STATE_CHANGE);
    
    if(key == 1 && index < 7)
    {
        index++;
    }
    else if(key == 2 && index > 0)
    {
        index--;
    }
    else if(key == 3)
    {
        index = 8;
    }
    
    clcd_print("GEAR",LINE1(9));
    clcd_print(gear[index], LINE2(10));
        
}
