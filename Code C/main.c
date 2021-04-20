#include <main.h>
#include <stdlib.h>
#include <string.h>





#INT_TIMER1
void  TIMER1_isr(void) 
{

}

#INT_EXT
void  EXT_isr(void) 
{

}

#INT_EXT1
void  EXT1_isr(void) 
{

}

#INT_RDA
void  RDA_isr(void) 
{

}

void main()
{
   int timer_counter = 0;
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);
   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      //104 ms overflow


   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_low_volt_detect(FALSE);
   

   
   boolean too_many_people = 0;
   boolean toggle = 0;
   int people_inside_tens = 0;


   while(TRUE)
   {
   

      
      

      
      

      

      

      
      if (toggle) {
      output_d(people_inside_units);
         output_e(2);
      }
      else {
         output_d(people_inside_tens);
         output_e(1);
      }

      toggle = !toggle;



      //TODO: User Code
   }

}
