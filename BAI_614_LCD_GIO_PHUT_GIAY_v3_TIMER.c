#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>
UNSIGNED INT8 GIO, PHUT, GIAY, BDN,GIA_TRI_MOD,DEM_TG_EXIT=0;
UNSIGNED INT8 CH_GIO, DV_GIO, CH_PHUT, DV_PHUT, CH_GIAY, DV_GIAY;

#DEFINE  UP      BT0    //DK LED DON
#DEFINE  DW      BT1
#DEFINE  CLR     BT2
#DEFINE  MOD     BT3

#INT_TIMER1
VOID INTERRUPT_TIMER1()
{
   BDN++;SET_TIMER1(3036);
}
VOID GIAI_MA_GAN_CHO_LCD()
{
   DV_GIAY= GIAY%10+0x30;
   CH_GIAY= GIAY/10+0x30;
   DV_PHUT= PHUT%10+0x30;
   CH_PHUT= PHUT/10+0x30;
   DV_GIO= GIO%10+0x30;
   CH_GIO= GIO/10+0x30;
}
VOID TAT_2LED_CHINH()
{
   IF (GIA_TRI_MOD==1)     
   {
      DV_GIO=" "; CH_GIO=" ";
   }
   IF (GIA_TRI_MOD==2)     
   {
      DV_PHUT=" "; CH_PHUT=" ";
   }
   IF (GIA_TRI_MOD==3)     
   {
      DV_GIAY=" "; CH_GIAY=" ";
   }
}
VOID LCD_HIENTHI_DONGHO()
{
   LCD_GOTO_XY (0, 11) ;
   LCD_DATA(CH_GIO);
   LCD_DATA(DV_GIO);
   LCD_DATA(" ");
   LCD_DATA(CH_PHUT);
   LCD_DATA(DV_PHUT);
   LCD_DATA(" ");
   LCD_DATA(CH_GIAY);
   LCD_DATA(DV_GIAY);
   
   
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_MOD()
{
   IF(PHIM_BT2(200))
   {
      GIA_TRI_MOD++;
      IF(GIA_TRI_MOD>=4) GIA_TRI_MOD=0;
      DEM_TG_EXIT=0;
   }
}
//XXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_UP()
{
   IF(PHIM_BT0(200))
   {
      DEM_TG_EXIT=0;
      SWITCH (GIA_TRI_MOD)
         {
            CASE 1: IF (GIO==23) GIO=0;
                    ELSE GIO++;
                    BREAK;
            CASE 2: IF (PHUT==59) PHUT=0;
                    ELSE PHUT++;
                    BREAK; 
            CASE 3: IF (GIAY==59) GIAY=0;
                    ELSE GIAY++;
                    BREAK;
            DEFAULT: BREAK;
         }
         
     }
}
//XXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_DW()
{
   IF(PHIM_BT1(200))
   {
      DEM_TG_EXIT=0;
      SWITCH (GIA_TRI_MOD)
         {
            CASE 1: IF (GIO==0) GIO=23;
                    ELSE GIO--;
                    BREAK;
            CASE 2: IF (PHUT==0) PHUT=59;
                    ELSE PHUT--;
                    BREAK; 
            CASE 3: IF (GIAY==0) GIAY=59;
                    ELSE GIAY--;
                    BREAK;
            DEFAULT: BREAK;
         }
         
   }
}
//XXXXXXXXXXXXXXXXXXXXX
VOID MAIN()
{
   SET_UP_PORT_IC_CHOT();
   SETUP_TIMER_1(T1_INTERNAL | T1_DIV_BY_8);
   SET_TIMER1(3036);
   ENABLE_INTERRUPTS(GLOBAL);
   ENABLE_INTERRUPTS(INT_TIMER1);
   SET_UP_PORT_IC_CHOT ();
   SETUP_LCD ();
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DONG HO:");
   BDN=0; GIAY=0;PHUT=0; GIO=0; GIA_TRI_MOD=0;
   WHILE(TRUE)
   {
      GIAI_MA_GAN_CHO_LCD();
      IF (BDN<10)
         {
            IF ((BDN<5)&&(INPUT(BT0))&& (INPUT(BT2))) TAT_2LED_CHINH();
            LCD_HIENTHI_DONGHO();
            PHIM_MOD(); PHIM_UP(); PHIM_DW();
         }
      ELSE
         {
            BDN=BDN-10;
            DEM_TG_EXIT++;
            IF(DEM_TG_EXIT==20) GIA_TRI_MOD=0;
            GIAY++;
            IF(GIAY==60)
            {
               GIAY=0;
               PHUT++;
               IF (PHUT==60)
               {
                  PHUT=0;
                  GIO++;
                  IF (GIO==24) GIO=0;                  
               }
            }
         }
   }
}
