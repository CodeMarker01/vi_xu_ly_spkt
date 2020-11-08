//DUNG TIMER
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#include<TV_pickit2_shift_key4x4_138.c>

signed INT8 tg,bdn,mp;

#INT_timer1

void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036);
}

//
void hienthi_tg()
{
   lcd_GOTO_xy (1, 17) ;
   delay_us (20);
   lcd_data (tg + 0x30) ;
}

//
void main()
{
   set_up_port_ic_chot ();
   set_tris_b (0x3c);
   setup_lcd ();
   set_timer1 (3036);
   enable_interrupts (global);
   enable_interrupts (INT_timer1);
   setup_timer_1 (t1_disabled);
   
   tg = 0;
   bdn = 0;
   lcd_GOTO_xy (0, 0) ;
   lcd_data ("DIEU KHIEN BUZZER");
   lcd_GOTO_xy (1, 0) ;
   lcd_data ("BUZZER:");
   lcd_GOTO_xy (1, 11) ;
   lcd_data (", TG:");


   WHILE (true)
   {
      mp = key_4x4_dw ();

      IF (mp != 0XFF)
      {
         IF (mp < 10)
         {
            tg = mp;
            hienthi_tg ();
         }

         IF (mp == 10)
         {
            setup_timer_1 (t1_internal|t1_div_by_8);
            // !   buzzer_on ();
            xuat_32led_don_4byte (0xff, 0xff, 0xff, 0xff) ;
            lcd_GOTO_xy (1, 8) ;
            lcd_data ("ON ");
         }

      }

         IF (bdn >= (10 * tg))
         {
            setup_timer_1 (t1_disabled);
            bdn = 0;
            // !   buzzer_off ();
            xuat_32led_don_4byte (0, 0, 0, 0);
            lcd_GOTO_xy (1, 8) ;
            lcd_data ("OFF");
         }
   }
}

