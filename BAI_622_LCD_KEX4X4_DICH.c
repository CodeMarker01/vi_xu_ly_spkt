#include<tv_pickit2_shift_1.c>
#include<TV_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_lcd.c>

unsigned CHAR MP_LCD[20]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
unsigned INT8 mp;
signed INT8 k,i;

void giai_ma_lcd()
{
   FOR (k = 19; k >=0; k--)
   { mp_lcd[k] = mp_lcd[k - 1]; }
   IF (mp < 10) mp_lcd[0] = mp + 0x30;
   ELSE mp_lcd[0] = mp + 0x37;
}

void hien_thi_lcd()
{
   lcd_GOTO_xy(1,0);
   FOR(i=19;i>=0;i--)
   {
      lcd_data(mp_lcd[i]);
   }
}

void main()
{
   set_up_port_ic_chot () ;
   set_tris_b (0x3c) ;
   hien_thi_lcd();
   setup_lcd();
   lcd_GOTO_xy(0,0);
   lcd_data("hay nhan phim:");
   WHILE (true)
   {
      mp = key_4x4_dw ();
      
      IF (mp != 0xFF)
      {
         giai_ma_lcd();
         hien_thi_lcd();
         
      }
   }
}

