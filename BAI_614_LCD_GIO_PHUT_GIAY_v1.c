
#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>

unsigned INT8 GIAY, phut, gio;

unsigned INT8 DV, CH, TR;

void xoa_0_vo_nghia(time)
{
   TR = time / 100 + 0x30;
   
   CH = (time / 10 % 10) + 0x30;
   
   DV = time % 10 + 0x30;
   
   IF (TR == 0x30)
   {
      TR = " ";

      IF (CH == 0x30)
      {
         CH = " ";
      }
   }

   LCD_DATA (TR);
   LCD_DATA (CH);
   LCD_DATA (DV);
}

VOID LCD_HIENTHI_DONGHO()
{
   LCD_GOTO_XY (0, 11) ;
   DELAY_US (20);
   xoa_0_vo_nghia(gio);
   xoa_0_vo_nghia (phut) ;
//!   LCD_DATA (' ');
   xoa_0_vo_nghia (giay) ;
   
   //!   LCD_DATA (PHUT / 10 + 0X30) ;
   //!   LCD_DATA (PHUT % 10 + 0X30) ;
   //!   LCD_DATA (' ') ;
   //!   LCD_DATA (GIAY / 10 + 0X30) ;
   //!   LCD_DATA (GIAY % 10 + 0X30) ;
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   SETUP_LCD ();
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DONG HO:");
   GIAY = 0;
   phut=58;
   gio=13;

   WHILE (TRUE)
   {
      LCD_HIENTHI_DONGHO ();
      DELAY_MS (200);
      GIAY++;
      // ! IF (GIAY == 150) GIAY = 0;

      IF (giay == 60)
      {
         giay = 0;
         phut++;

         IF (phut == 60)
         {
            phut = 0;
            gio++;

            IF (gio == 24)
            {
               gio = 0;
            }
         }
      }
   }
}

