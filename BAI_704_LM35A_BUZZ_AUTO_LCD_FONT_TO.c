
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#define nd_tren  32
#define nd_duoi  30

unsigned INT8     j, solan=100; 
UNSIGNED INT16   lm35a;
int1 ttqn=0;
signed INT8 i;
int16 CH,DV;

void so_sanh_dk_buzzer()
{
   IF ((lm35a > nd_tren)&& (ttqn == 0))
   {
      ttqn = 1;
      //!      buzzer_on();
      xuat_32led_don_4byte (0xFF, 0xFF, 0xFF, 0xFF) ;
      triac_2_off () ;
   }

   else IF ((lm35a < nd_tren)&& (ttqn == 1))
   {
      ttqn = 0;
      //!      buzzer_off();
      xuat_32led_don_4byte (0, 0, 0, 0) ;
   }

   else IF ((lm35a < nd_duoi)&& (ttqn == 0))
   triac_2_on () ;
}

//Hien thi LCD so lon
VOID LCD_HIENTHI_SO_Z_TOADO_XY (SIGNED INT8 LCD_SO, SIGNED INT8 X1, SIGNED INT8 Y1)
{
   LCD_GOTO_XY (X1, Y1) ;
   FOR (I = 0; I < 6; I++)
   {
      IF (I == 3) LCD_GOTO_XY (X1 + 1, Y1);
      LCD_DATA (LCD_SO_X[LCD_SO][I]);
   }
}

VOID HIENTHI_LCD_KichThuocLon()
{
   CH = lm35a / 10 % 10;
   DV = lm35a % 10;
   
   IF (CH == 0) CH = 10;
   LCD_COMMAND (0x40);
   DELAY_US (20);
   FOR (I = 0; I < 64; I++)
   { LCD_DATA (LCD_MA_8DOAN[I]); }
   
   
   lcd_hienthi_so_z_toado_xy (CH, 2, 3) ;
   lcd_hienthi_so_z_toado_xy (DV, 2, 6) ;
   
}

void main()
{
   set_up_port_ic_chot ();
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0|vss_vdd) ;
   set_adc_channel (0) ;
   setup_lcd () ;
   ttqn = 0;

   WHILE (true)
   {
      lm35a = 0;
      FOR (j = 0; j<solan; j++)
      {
         lm35a = lm35a + read_adc ();
         delay_ms (1) ;
      }

      lm35a = lm35a / 2.046;
      lm35a = lm35a / solan;
      xuat_4led_7doan_giaima_xoa_so0 (lm35a);
      HIENTHI_LCD_KichThuocLon () ;
      so_sanh_dk_buzzer () ;
   }
}

