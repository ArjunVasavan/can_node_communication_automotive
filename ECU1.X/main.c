/*
 * File:   main.c
 * Author: DELL
 *
 * Created on 7 April, 2026, 12:53 AM
 */


#include "ADC.h"
#include "CAN.h"
#include "ECU1_Sensor.h"
#include "msg_id.h"
#include "CLCD.h"
//#include "uart.h"


void init_config()
{
    init_adc();
    init_clcd();
    init_matrix_keypad();
    init_can();
}

int main()
{
    init_config();
    
    //Call the functions
    while(1)
    {
        get_speed();
        get_gear_pos();    
    }
}
