#INCLUDE <TV_PICKIT2_SHIFT_1.c>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.c>
#INCLUDE <TV_PICKIT2_SHIFT_KEY4X4_138.c>
SIGNED INT8 MP;
VOID HIENTHI_LCD()
{
   LCD_GOTO_XY(1,19);   DELAY_US(20);
   IF(MP<10)   LCD_DATA(MP+0X30);
   ELSE   LCD_DATA(MP+0X37);
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT();
   set_tris_b(0X3C);
   SETUP_LCD();
   LCD_GOTO_XY(0,0);
   LCD_DATA("DIEU KHIEN DEN LED");
   
   WHILE(TRUE)
   {
      MP = KEY_4X4_DW();
      if ( mp != 0 )
      {
         xuat_32led_don_4byte (0xff, 0xff, 0xff, 0xff);
      }
      if ( mp != 10 )
      {
         xuat_32led_don_4byte (0, 0xff, 0xff, 0xff);
      }
   }
}


