#include <tv_pickit2_shift_1.c>
#define nd_tren  32
#define nd_duoi  30
unsigned int8     j, solan=100; 
UNSIGNED int16   lm35a;
int1 ttqn=0;
void so_sanh_dk_buzzer()
{
   IF ((lm35a>nd_tren)&&(ttqn==0))
   {
      ttqn = 1; 
//!      buzzer_on();
      xuat_32led_don_4byte(0xFF,0xFF,0xFF,0xFF);
      triac_2_off();
   }

   else IF ((lm35a<nd_tren)&&(ttqn==1))
   {
      ttqn = 0; 
//!      buzzer_off();
      xuat_32led_don_4byte(0,0,0,0);
   }

   else IF ((lm35a<nd_duoi)&&(ttqn==0)) 
   triac_2_on();
}

void main()
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0|vss_vdd );
   set_adc_channel(0);
   ttqn = 0; 
   WHILE(true)
   {
      lm35a = 0;
      FOR (j=0; j<solan; j++)
      {
         lm35a = lm35a + read_adc(); 
         delay_ms(1);
      }

      lm35a = lm35a /2.046; 
      lm35a = lm35a /solan;
      xuat_4led_7doan_giaima_xoa_so0(lm35a); 
      so_sanh_dk_buzzer();
   }
}


