#include<tv_pickit2_shift_1.c>
#include<TV_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_lcd.c>

unsigned CHAR MP_LCD[80];

unsigned INT8 mp,mang;
signed INT8 k,i;

void giai_ma_lcd()
{
   FOR (k = 79; k > - 1; k--)
   { mp_lcd[k] = mp_lcd[k - 1]; }
   IF (mp < 10) mp_lcd[0] = mp + 0x30;
   ELSE mp_lcd[0] = mp + 0x37;
}

void hien_thi_lcd()
{                                                        ///19----0///
   lcd_GOTO_xy (0, 0) ;                                  ///39----20///
   delay_us (20);                                        ///59----40///
   FOR (i = 19; i >= 0; i--)                             ///79----60///
   {
      lcd_data (mp_lcd[i]);
   }

   lcd_GOTO_xy (1, 0) ;
   delay_us (20);
   FOR (i = 39; i >= 20; i--)
   {
      lcd_data (mp_lcd[i]);
   }

   lcd_GOTO_xy (2, 0) ;
   delay_us (20);
   FOR (i = 59; i >= 40; i--)
   {
      lcd_data (mp_lcd[i]);
   }

   lcd_GOTO_xy (3, 0) ;
   delay_us (20);
   FOR (i = 79; i >= 60; i--)
   {
      lcd_data (mp_lcd[i]);
   }

}

void main()
{
   set_up_port_ic_chot ();
   set_tris_b (0x3c);
   hien_thi_lcd ();
   setup_lcd ();
   lcd_GOTO_xy (0, 0) ;
   lcd_data ("hay nhan phim:");
   FOR (mang = 0; mang < 80; mang++)
   {
      mp_lcd[mang] = 0x20;
   }

   
   WHILE (true)
   {
      mp = key_4x4_dw ();
      
      IF (mp != 0xFF)
      {
         giai_ma_lcd ();
         hien_thi_lcd ();
      }
   }
}

