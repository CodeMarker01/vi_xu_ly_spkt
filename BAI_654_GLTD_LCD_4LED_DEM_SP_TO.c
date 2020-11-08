

#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>
#INCLUDE  <TV_PICKIT2_SHIFT_GLCD128X64.C>

UNSIGNED INT16 T0,T0_TAM;
UNSIGNED INT8 CH_GLCD, TR_GLCD, DV_GLCD ;
UNSIGNED INT8 CH_LCD, TR_LCD, DV_LCD ;

VOID HIENTHI_LCD()
{
   LCD_GOTO_XY (0, 17) ;
   DELAY_US (20) ;
   
   TR_LCD = T0 / 100 + 0x30 ;
   
   CH_LCD = (T0 / 10 %10) + 0x30 ;
   
   DV_LCD = T0 % 10 + 0x30 ;
   
   if(TR_LCD==0x30)
   {
      TR_LCD = " ";
      if (CH_LCD==0x30)
      {
         CH_LCD=" ";
      }
   }
   LCD_DATA(TR_LCD);
   LCD_DATA(CH_LCD);
   LCD_DATA(DV_LCD);
}

VOID HIENTHI_GLCD_T0()
{
   GLCD_COMMAND (GLCD_ADDR_LINE2) ;
   DELAY_US (20) ;
   
   TR_GLCD = T0 / 100 + 0x30 ;
   
   CH_GLCD  = (T0 / 10 %10) + 0x30 ;
   
   DV_GLCD  = T0 % 10 + 0x30 ;
   
   if(TR_GLCD ==0x30)
   {
      TR_GLCD  = " ";
      if (CH_GLCD ==0x30)
      {
         CH_GLCD =" ";
      }
   }
   GLCD_DATA(TR_GLCD );
   GLCD_DATA(CH_GLCD );
   GLCD_DATA(DV_GLCD );
   GDRAM_VDK_TO_GDRAM_GLCD_ALL();
}


VOID MAIN()
{
   SET_UP_PORT_IC_CHOT () ;
   SETUP_LCD () ;
   SETUP_GLCD (GLCD_TEXT_MODE) ;
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DEM SAN PHAM:") ;
   GLCD_COMMAND (GLCD_ADDR_LINE1) ;
   GLCD_DATA ("DEM SAN PHAM:") ;
   GDRAM_VDK_TO_GDRAM_GLCD_ALL();
   
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT) ;
   SET_TIMER0 (0) ;
   T0 = T0_TAM = 0;
   HIENTHI_LCD () ;
   HIENTHI_GLCD_T0();
   XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
   
   WHILE (TRUE)
   {
      
      
      T0 = GET_TIMER0 () ;

      IF (T0 != T0_TAM)
      {
         T0_TAM = T0;
         HIENTHI_LCD () ;
         HIENTHI_GLCD_T0();
         XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
      }

      
      IF (T0 >= 101) SET_TIMER0 (1);
   }
}


