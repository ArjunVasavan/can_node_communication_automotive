#include "ADC.h"
#include "CAN.h"
#include "ECU1_Sensor.h"
#include "CLCD.h"
void init_config() {
    init_adc();
    init_matrix_keypad();
    init_can();
}
int main() {
    init_config();
    while(1) {
        get_speed();
        get_gear_pos();    
    }
}
