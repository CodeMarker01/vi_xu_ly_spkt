// CHUA XOA SO 0 VO NGHIA

#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#include<TV_pickit2_shift_key4x4_138.c>

UNSIGNED INT16 GTC,T0=0,MP,DV=1,CH=0;


VOID GIAIMA()
{
   
   LED_7DQ[0] = MA7DOAN[T0 % 10];
   LED_7DQ[1] = MA7DOAN[T0 / 10];
   LED_7DQ[3] = MA7DOAN[GTC % 10];
   LED_7DQ[4] = MA7DOAN[GTC / 10];
}

VOID HIENTHI()
{
   LCD_GOTO_XY (0, 17) ;
   DELAY_US (20) ;
   LCD_DATA (GTC / 10 + 0X30) ;
   LCD_DATA (GTC % 10 + 0X30) ;
   LCD_GOTO_XY (1, 17) ;
   DELAY_US (20) ;
   LCD_DATA (T0 / 10  + 0X30) ;
   LCD_DATA (T0 % 10 + 0X30) ;
   GIAIMA (); HIEN_THI_8LED_7DOAN_QUET () ;
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT () ;
   SETUP_LCD () ;
   LCD_GOTO_XY (1, 0) ;
   LCD_DATA ("T0 SAN PHAM: ") ;
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("GIA TRI CAI: ");
   setup_timer_0 (T0_EXT_L_TO_H|T0_DIV_1) ;
   SET_TIMER0 (0) ;
   T0 = 0;

   WHILE (TRUE)
   {
      MP = KEY_4X4_DW ();

      IF (MP != 0XFF)
      {
         IF (MP <= 9)
         {
            CH = DV;
            DV = MP;
         }

         ELSE IF (MP == 12) // NHAN PHIM 'C'
         {
            DV = 1; CH = 0;
            GTC = 1;
           SET_TIMER0 (0) ;
          
         }
      }

      GTC = CH * 10 + DV;// T0 10 LAN SE DUOC 1s
      HIENTHI () ;
      GIAIMA () ;
      HIEN_THI_8LED_7DOAN_QUET () ;
      XUAT_4LED_7DOAN_4SO (MA7DOAN[GTC / 10], MA7DOAN[GTC % 10]&0X7F, MA7DOAN[T0 / 10], MA7DOAN[T0 % 10]) ;
      T0 = GET_TIMER0 () ;
      IF (T0 == GTC + 1) SET_TIMER0 (0);
   }
}

