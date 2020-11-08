

#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>

UNSIGNED INT16 T0,T0_TAM;
UNSIGNED INT8 CH, TR, DV;

VOID HIENTHI_LCD()
{
   LCD_GOTO_XY (0, 17) ;
   DELAY_US (20) ;
   
   TR = T0 / 100 + 0x30 ;
   
   CH = (T0 / 10 %10) + 0x30 ;
   
   DV = T0 % 10 + 0x30 ;
   
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
   SET_UP_PORT_IC_CHOT () ;
   SETUP_LCD () ;
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DEM SAN PHAM:") ;
   
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1) ;
   SET_TIMER0 (0) ;
   T0 = T0_TAM = 0;
   HIENTHI_LCD () ;
   XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
   
   WHILE (TRUE)
   {
      
      
      T0 = GET_TIMER0 () ;

      IF (T0 != T0_TAM)
      {
         T0_TAM = T0;
         HIENTHI_LCD () ;
         XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
      }

      
      IF (T0 >= 101) SET_TIMER0 (1);
   }
}


