
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>

signed INT8 i,dem;

void lcd_hienthi_so_z_toado_xy(SIGNED int8 lcd_so, x1, y1)
{
   lcd_GOTO_xy(x1,y1);
   FOR (i=0;i<6;i++)
   {
      IF (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   lcd_GOTO_xy(0,0);
   lcd_data("**dem tu 00 den 99**");
   lcd_command(0x40);
   FOR (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   lcd_hienthi_so_z_toado_xy(0,2,0);

   WHILE(true)
   {
      FOR (dem=80;dem<1000;dem++)
      {
         lcd_hienthi_so_z_toado_xy(dem/100%10,2,0);
         lcd_hienthi_so_z_toado_xy(dem/10%10,2,3);
         lcd_hienthi_so_z_toado_xy(dem%10,2,6);
         delay_ms(300);
      }
   }
}

