
#INCLUDE  <TV_PICKIT2_SHIFT_1.C>
#INCLUDE  <TV_PICKIT2_SHIFT_GLCD128X64.C>

UNSIGNED INT8  T0,T0_TAM;
UNSIGNED INT8 CH, TR, DV;
UNSIGNED INT8 CH_number, TR_number, DV_number;

//!VOID GLCD_HIENTHI_T0(UNSIGNED T0)
//!{
//!   
//!   GLCD_COMMAND (GLCD_ADDR_LINE2) ;
//!   GLCD_DATA (T0 / 100 % 10 + 0X30);
//!   GLCD_DATA (T0 / 10 % 10 + 0X30);
//!   GLCD_DATA (T0 / 10 + 0X30);
//!}

VOID HIENTHI_GLCD_T0()
{
   GLCD_COMMAND (GLCD_ADDR_LINE2) ;
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
   GLCD_DATA(TR);
   GLCD_DATA(CH);
   GLCD_DATA(DV);
}

VOID HIENTHI_GLCD_T0_IMAGE()
{
   GLCD_COMMAND (GLCD_ADDR_LINE2) ;
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
   GLCD_DATA(TR);
   GLCD_DATA(CH);
   GLCD_DATA(DV);
   
   
}

VOID MAIN ()
{
   SET_UP_PORT_IC_CHOT () ;
   SETUP_GLCD(GLCD_GRAPHIC_MODE);
   GLCD_MAU_NEN(0);
   
   
   GLCD_COMMAND (GLCD_ADDR_LINE1) ;
   GLCD_DATA ("DEM SAN PHAM:") ;
   
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0 (0) ;
   T0 = T0_TAM = 0;
//!   GLCD_HIENTHI_T0 (T0) ;
   HIENTHI_GLCD_T0();
   XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
   
   WHILE (TRUE)
   {
      T0 = GET_TIMER0 ();

      IF (T0 != T0_TAM)
      {
//!         GLCD_HIENTHI_T0 (T0) ;
         HIENTHI_GLCD_T0();
         XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
         T0_TAM = T0;
      }

      //!         XUAT_4LED_7DOAN_3SO (MA7DOAN[TO/100],MA7DOAN[TO/10%10],MA7DOAN[TO%10]);
      
      IF (T0 >= 101) SET_TIMER0 (1);
   }
}

