
#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>

UNSIGNED INT8 GIO, PHUT, GIAY, BDN,GIA_TRI_MOD,DEM_TG_EXIT=0;
UNSIGNED INT8 TR, CH, DV;

#DEFINE  UP      BT0    //DK LED DON
#DEFINE  DW      BT1
#DEFINE  CLR     BT2
#DEFINE  MOD     BT3

#INT_TIMER1
VOID INTERRUPT_TIMER1()
{
   BDN++; SET_TIMER1 (3036) ;
}

VOID GIAI_MA_GAN_CHO_LCD(UNSIGNED int8 time)
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

   LCD_DATA (TR) ;
   LCD_DATA (CH) ;
   LCD_DATA (DV) ;
}

void LCD_HIENTHI_DONGHO()
{
   LCD_GOTO_XY (0, 11) ;
   GIAI_MA_GAN_CHO_LCD (GIO) ;
   //!   LCD_GOTO_XY (0, 11) ;
   GIAI_MA_GAN_CHO_LCD (PHUT) ;
   //!   LCD_GOTO_XY (0, 11) ;
   GIAI_MA_GAN_CHO_LCD (GIAY) ;
}

VOID TAT_2LED_CHINH()
{
   IF (GIA_TRI_MOD == 1) 
   {
      LCD_GOTO_XY(0,11);
      LCD_DATA("   ");
   }
   
   IF (GIA_TRI_MOD == 2) 
   {
      LCD_GOTO_XY(0,14);
      LCD_DATA("   ");
   }
   
   IF (GIA_TRI_MOD ==3)
   {
      LCD_GOTO_XY(0,17);
      LCD_DATA("   ");    
   }
   
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_MOD()
{
   IF (PHIM_BT2 (200) )
   {
      GIA_TRI_MOD++;
      IF (GIA_TRI_MOD >= 4) GIA_TRI_MOD = 0;
      DEM_TG_EXIT = 0;
   }
}

//XXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_UP()
{
   IF (PHIM_BT0 (200) )
   {
      DEM_TG_EXIT = 0;

      SWITCH (GIA_TRI_MOD)
      {
         CASE 1: IF (GIO == 23) GIO = 0;
         ELSE GIO++;
         BREAK;
         CASE 2: IF (PHUT == 59) PHUT = 0;
         ELSE PHUT++;
         BREAK;
         CASE 3: IF (GIAY == 59) GIAY = 0;
         ELSE GIAY++;
         BREAK;
         DEFAULT: BREAK;
      }

   }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_DW()
{
   IF (PHIM_BT1 (200) )
   {
      DEM_TG_EXIT = 0;

      SWITCH (GIA_TRI_MOD)
      {
         CASE 1: IF (GIO == 0) GIO = 23;
         ELSE GIO--;
         BREAK;
         CASE 2: IF (PHUT == 0) PHUT = 59;
         ELSE PHUT--;
         BREAK;
         CASE 3: IF (GIAY == 0) GIAY = 59;
         ELSE GIAY--;
         BREAK;
         DEFAULT: BREAK;
      }

   }
}

//XXXXXXXXXXXXXXXXXXXXX
VOID MAIN()
{
   SET_UP_PORT_IC_CHOT () ;
   SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8) ;
   SET_TIMER1 (3036) ;
   ENABLE_INTERRUPTS (GLOBAL) ;
   ENABLE_INTERRUPTS (INT_TIMER1) ;
   SETUP_LCD ();
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DONG HO:");
   BDN = 0; GIAY = 0; PHUT = 0; GIO = 0; GIA_TRI_MOD = 0;
   WHILE (TRUE)
   {
   LCD_HIENTHI_DONGHO () ;
      
      IF (BDN < 10)
      {
         IF ((BDN < 5)&& (INPUT (BT0))&& (INPUT (BT1))) TAT_2LED_CHINH ();
         //!            HIEN_THI_8LED_7DOAN_QUET_ALL();
         PHIM_MOD (); PHIM_UP (); PHIM_DW ();
      }

      ELSE
      {
         BDN = BDN - 10;
         DEM_TG_EXIT++;
         IF (DEM_TG_EXIT == 20) GIA_TRI_MOD = 0;
         GIAY++;

         IF (GIAY == 60)
         {
            GIAY = 0;
            PHUT++;

            IF (PHUT == 60)
            {
               PHUT = 0;
               GIO++;
               IF (GIO == 24) GIO = 0;
            }
         }

         
      }
   }
}

