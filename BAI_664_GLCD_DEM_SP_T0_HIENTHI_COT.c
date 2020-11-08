
#INCLUDE  <TV_PICKIT2_SHIFT_1.C>
#INCLUDE  <TV_PICKIT2_SHIFT_GLCD128X64.C>
#INCLUDE<GRAPHICS.C>

UNSIGNED INT8  T0,T0_TAM;
UNSIGNED INT8 CH, TR, DV;
UNSIGNED INT8 CH_num, TR_num, DV_num;

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
   
   TR_num = T0 / 100 ;
   
   CH_num = (T0 / 10 %10) ;
   
   DV_num = T0 % 10 ;
   
   glcd_rect(9,9,(DV_num-0x30),18,1,1);
//!   glcd_circle(40,40,20,0,1);
//!glcd_rect(9,9,50,18,0,1);
}

VOID MAIN ()
{
   SET_UP_PORT_IC_CHOT () ;
//!   SETUP_GLCD (GLCD_TEXT_MODE) ;
   SETUP_GLCD(GLCD_GRAPHIC_MODE);
   SETUP_GLCD(GLCD_TEXT_MODE);
   GLCD_COMMAND(GLCD_GRAPHIC_MODE);
   GLCD_COMMAND(GLCD_TEXT_MODE);
   GLCD_MAU_NEN(0);
   
   
   GLCD_COMMAND (GLCD_ADDR_LINE1) ;
   GLCD_DATA ("DEM SAN PHAM:") ;
   
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0 (0) ;
   T0 = T0_TAM = 0;
//!   GLCD_HIENTHI_T0 (T0) ;
   HIENTHI_GLCD_T0_IMAGE();
   XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
   GDRAM_VDK_TO_GDRAM_GLCD_ALL();
//!   gdram_vdk;
   WHILE (TRUE)
   {
      T0 = GET_TIMER0 ();

      IF (T0 != T0_TAM)
      {
//!         GLCD_HIENTHI_T0 (T0) ;
         HIENTHI_GLCD_T0_IMAGE();
         XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0) ;
         T0_TAM = T0;
      }

      //!         XUAT_4LED_7DOAN_3SO (MA7DOAN[TO/100],MA7DOAN[TO/10%10],MA7DOAN[TO%10]);
      
      IF (T0 >= 101) SET_TIMER0 (1);
   }
}

