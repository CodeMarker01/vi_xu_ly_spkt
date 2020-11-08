
#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>

unsigned INT8 GIAY;
unsigned int8 DV, CH, TR;

VOID LCD_HIENTHI_DONGHO()
{
   LCD_GOTO_XY (0, 15) ;
   DELAY_US (20);
   TR = GIAY / 100 + 0x30 ;
   
   CH = (GIAY / 10 %10) + 0x30 ;
   
   DV = GIAY % 10 + 0x30 ;
   
   if(TR==0x30)
   {
      TR = " ";
      if (CH==0x30)
      {
         CH=" ";
      }
   }
   LCD_DATA(TR);
   LCD_DATA(CH);
   LCD_DATA(DV);
   
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   SETUP_LCD ();
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DONG HO:");
   GIAY = 100;

   WHILE (TRUE)
   {
      LCD_HIENTHI_DONGHO ();
      DELAY_MS (300);
      GIAY++;
      IF (GIAY == 150) GIAY = 0;
   }
}

