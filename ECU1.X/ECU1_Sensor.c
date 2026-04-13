#include "ECU1_Sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "Matrix_Keypad.h"
#include "clcd.h"
#include <stdint.h>

char gear[9][3]={"ON","GN","G1","G2","G3","G4","G5","Rr","Cl"};
int ind = 0;
#define _XTAL_FREQ 8000000

uint16_t msg_id;
uint8_t rx1_data[4];
char len1;

uint16_t gear_id;
uint8_t rx2_data[4];
char len2;

uint16_t get_speed()
{
    char str[3];
   unsigned short speed= read_adc(CHANNEL4)/10.33;
   str[0]=(speed/10)+48;
   str[1]=(speed%10)+48;
   str[2]='\0';

   can_transmit(SPEED_MSG_ID ,(const uint8_t*)str,2);
   __delay_ms(20);
   can_receive(&msg_id,rx1_data,(uint8_t*)&len1);
   rx1_data[len1] = '\0';


   if(msg_id == SPEED_MSG_ID) {
       clcd_print((const uint8_t*)"SPEED", LINE1(0));
       clcd_print(rx1_data, LINE2(0));
   }

   return speed;
}

unsigned char get_gear_pos()
{

    // Implement the gear function

    /* NOTE: STATE_CHANGE
     * state change doesnt impact anything we can send void also
     */
    int key=read_switches(STATE_CHANGE);
    if(key== 1) {
        if(ind<7) {
            ind++;
        }
    } else if(key == 2) {
        if(ind>0) {
            ind--;
        }
    } else if(key== 3) {
        ind=8;
    }

    /* NOTE: For ECU3 CAN Connection
     * comment from 
     * __delay_ms(20)
     * to 
     *
     */

    can_transmit(GEAR_MSG_ID,(const uint8_t*)gear[ind],2);
    __delay_ms(20);
    can_receive(&gear_id,rx2_data,(uint8_t*)&len2);
    rx2_data[len2] = '\0';
    if(gear_id == GEAR_MSG_ID)
    {
        clcd_print((const unsigned char*)"GEAR", LINE1(9));
        clcd_putch(rx2_data[0], LINE2(9));
        clcd_putch(rx2_data[1], LINE2(10));
    }

    // till here

    return gear[ind][0];

}
