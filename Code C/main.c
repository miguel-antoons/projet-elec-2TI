#include "C:\Users\antoo\Documents\Ephec\electronique_digitale\projet-elec-2TI\Code C\main.h"
#include <string.h>
#include <stdlib.h>

char rda_input[1];
signed int8 people_inside_units = 0;

boolean flag_timer = 0;
boolean flag_in_or_out = 0;
boolean flag_rda = 0;

#int_TIMER1
void  TIMER1_isr(void) 
{
   flag_timer = 1;
}

#int_EXT
void  EXT_isr(void) 
{
   flag_in_or_out = 1;
   people_inside_units++;
}

#int_EXT1
void  EXT1_isr(void) 
{
   flag_in_or_out = 1;
   people_inside_units--;
}

#int_RDA
void  RDA_isr(void) 
{
   rda_input[0] = getc();
   flag_rda = 1;
}



void main()
{
   boolean too_many_people = 0;
   boolean toggle = 0;
   int8 people_inside_tens = 0;
   int8 timer_counter = 0;
   int8 people_inside_total = 0;
   
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
//Setup_Oscillator parameter not selected from Intr Oscillotar Config tab

   set_timer1(0);
   
   output_high(PIN_E0);

   while (TRUE) {
      // check if there was any data received from rs232
      if (flag_rda) {
         // reset the flag's value
         flag_rda = 0;
         too_many_people = atoi(rda_input);
      }
      
      // check if the green/red led's state has to change depending on the 
      // value received from the rs232 and timer1
      if (too_many_people) {
         if (flag_timer) {
            set_timer1(0);
            flag_timer = 0;
            
            // counter will increment on each timer finish
            timer_counter++;
            
            // if the counter is equal to 9 the red led's output il toggle
            // this is done in order to let the red led blink
            if (timer_counter > 6) {
               timer_counter = 0;
               output_low(PIN_B7);
               output_toggle(PIN_B6);
            }
         }
      }
      // else it is the green led that will be shining
      else {
         output_low(PIN_B6);
         output_high(PIN_B7);
      }
      
      // if external input 1 is high, increase peope inside and send value 
      // to rs232
      if (flag_in_or_out) {
         flag_in_or_out = 0;
         
          // calculate how many units and tens there are
         if (people_inside_units > 9) {
            people_inside_tens++;
            people_inside_units = 0;
         }
         // prevent negative numbers from showing up
         else if (people_inside_units < 0 && people_inside_tens == 0) {
            people_inside_units = 0;
         }
         // lower tens by 1 if units go negative 1
         else if (people_inside_units < 0) {
            people_inside_units = 9;
            people_inside_tens--;
         }
         
         if (people_inside_tens > 9) {
            people_inside_tens = 0;
         }
         
         // calculate the sum of people inside from tens and units
         people_inside_total = (people_inside_tens * 10) + people_inside_units;
         
         // send total to rs232
         printf("%d ", people_inside_total);  
      }
      
      // set output e to 0 to avoid having the wrong number shown on the wrong
      // screen
      output_e(0);
      
      // check which screen and which value to show
      if (toggle) {
         output_d(people_inside_units);
         output_e(1);
      }
      else {
         output_d(people_inside_tens);
         output_e(2);
      }
      
      // invert the value in order to show the other value on next iteration
      toggle = !toggle;
   }

}
