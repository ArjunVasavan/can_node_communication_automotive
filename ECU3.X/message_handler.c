#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

uint16_t msg_id;
uint8_t data[5];
uint8_t len;

volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    
    //Implement the speed function
    data[len] = '\0';
     clcd_print(data, LINE1(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    data[len] = '\0';
     clcd_print(data, LINE1(6));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    data[len] = '\0'
    //Implement the rpm function
     clcd_print(data, LINE2(0));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    data[len] = '\0';
     clcd_print(data, LINE2(6));
}

void process_canbus_data() 
{   
    //process the CAN bus data
    can_receive(&msg_id,data,&len);
    data[len] = '\0';
    
    if(msg_id == SPEED_MSG_ID)
    {
        handle_speed_data(data,len); 
    }
    else if(msg_id == GEAR_MSG_ID)
    {
        handle_gear_data(data,len);  
    }
   
    else if(msg_id==RPM_MSG_ID)
    {
       handle_rpm_data(data,len);
    }
    else if(msg_id==INDICATOR_MSG_ID)
    {
       handle_indicator_data(data,len);
    }
    
}
