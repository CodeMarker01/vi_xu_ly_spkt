#INCLUDE <TV_PICKIT2_SHIFT_1.C>
SIGNED INT8 GIO, PHUT, GIAY, BDN,GIA_TRI_MOD,DEM_TG_EXIT=0;

#DEFINE  UP      BT0    //DK LED DON
#DEFINE  DW      BT1
#DEFINE  CLR     BT2
#DEFINE  MOD     BT3

#INT_TIMER1
VOID INTERRUPT_TIMER1()
{
   BDN++;SET_TIMER1(3036);
}
VOID GIAI_MA_GAN_CHO_8LED_QUET()
{
   LED_7DQ[0]=MA7DOAN [GIAY%10];
   LED_7DQ[1]=MA7DOAN [GIAY/10];
   LED_7DQ[3]=MA7DOAN [PHUT%10];
   LED_7DQ[4]=MA7DOAN [PHUT/10];
   LED_7DQ[6]=MA7DOAN [GIO%10];
   LED_7DQ[7]=MA7DOAN [GIO/10];
}
VOID TAT_2LED_CHINH()
{
   IF (GIA_TRI_MOD==1)      {LED_7DQ[7]=0XFF; LED_7DQ[6]=0XFF;}
   ELSE IF (GIA_TRI_MOD==2) {LED_7DQ[4]=0XFF; LED_7DQ[3]=0XFF;}
   ELSE IF (GIA_TRI_MOD==3) {LED_7DQ[1]=0XFF; LED_7DQ[0]=0XFF;}
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
   ENABLE_INTERRUPTS(INT_TIMER1);;
   BDN=0; GIAY=0;PHUT=0; GIO=0; GIA_TRI_MOD=0;
   WHILE(TRUE)
   {
      GIAI_MA_GAN_CHO_8LED_QUET();
      IF (BDN<10)
         {
            IF ((BDN<5)&&(INPUT(BT0))&& (INPUT(BT2))) TAT_2LED_CHINH();
            HIEN_THI_8LED_7DOAN_QUET_ALL();
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
