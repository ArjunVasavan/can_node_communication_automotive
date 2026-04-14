#include "ECU2_Sensor.h"
#include "ADC.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"
#include "clcd.h"
void init_ssd()
{
    TRISD = 0x00;          // Segment lines
    TRISA = TRISA & 0xF0;  // Digit select lines
    PORTA = PORTA & 0xF0;
}

void init_led() {

    TRISB0 = 0;
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
    
    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
    PORTBbits.RB3 = 0;
    
}

void init_config()
{
    init_adc();
    init_digital_keypad();
    init_led();
    init_can();
}

int main()
{
    init_config();
    
    //call the functions
    while(1)
    {
        get_rpm();
        process_indicator();
    }
}
