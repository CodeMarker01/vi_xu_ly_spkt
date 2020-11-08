/*
* 1. Hien thi 2 LM35 len led quet, led 4, LCD, GLCD -> auto buzzer
*
*
*
*
*/
// Khai bao thu vien
#include <tv_pickit2_shift_1.c> 

// LM35 Section
// khai bao bien LM35
UNSIGNED INT8     j, solan=100; 
unsigned INT16   lm35a, lm35b;

void doc_nd_lm35a()
{
   set_adc_channel (0); lm35a = 0;
   FOR (j = 0; j<solan; j++)
   {
      lm35a = lm35a + read_adc ();
      delay_us (100) ;
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}

void doc_nd_lm35b()
{
   set_adc_channel (1) ;
   lm35b = 0;
   FOR (j = 0; j<solan; j++)
   {
      lm35b = lm35b + read_adc ();
      delay_us (100) ;
   }

   lm35b = lm35b / 2.046;
   lm35b = lm35b / solan;
}
// END LM35 Section
//**********************************************************************************

//HIEN THI
// Hien thi Led quet
VOID GIAI_MA_GAN_CHO_8LED_QUET() // 
{
   LED_7DQ[7] = ma7doan[8]; // %10 -> donvi
   LED_7DQ[6] = ma7doan[lm35b/10%10];///10 -> chuc
   LED_7DQ[5] = ma7doan[lm35b%10];
   LED_7DQ[2] = 0x88;
   LED_7DQ[1] = ma7doan[lm35a/10%10];
   LED_7DQ[0] = ma7doan[lm35a%10];
//!   IF (T0 == 0) LED_7DQ[5] = 0xff;

   // LED_7DQ [2...7] = 0xFF
}

void main()
{
   set_up_port_ic_chot () ;
   
   // setup ADC LM35
   setup_adc (adc_clock_div_32) ;
   setup_adc_ports (an0_to_an1|vss_vdd) ; // dung 2 port 0,1; con port 2: an0_to_an2
   GIAI_MA_GAN_CHO_8LED_QUET ();
   
   WHILE (true)
   {
      doc_nd_lm35a ();
      doc_nd_lm35b () ;
      // xuat ra 4 led 7 doan
      xuat_4led_7doan_4so (ma7doan[lm35b/10%10],ma7doan[lm35b%10],ma7doan[lm35a/10%10], ma7doan[lm35a%10]);
      // led quet
      GIAI_MA_GAN_CHO_8LED_QUET ();
      HIEN_THI_8LED_7DOAN_QUET ();
      
   }
}


