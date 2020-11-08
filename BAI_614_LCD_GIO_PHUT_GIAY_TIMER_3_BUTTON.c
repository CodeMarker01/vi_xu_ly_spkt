
#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>

#DEFINE  UP      BT0    //DK LED DON
#DEFINE  DW      BT1
#DEFINE  ADJ     BT2
#DEFINE  MOD     BT3

SIGNED INT PHUT,GIAY,GIO, BDN;
SIGNED INT8 GIO, PHUT, GIAY, BDN;
UNSIGNED CHAR GIA_TRI_MOD;

#INT_TIMER1

VOID INTERRUPT_TIMER1()
{
   BDN++; SET_TIMER1 (3036) ;
}

VOID LCD_HIENTHI_DONGHO()
{
   LCD_GOTO_XY (0, 11) ;
   
   LCD_DATA (GIO / 10 + 0X30) ;
   LCD_DATA (GIO % 10 + 0X30) ;
   LCD_DATA (' ') ;
   LCD_DATA (PHUT / 10 + 0X30) ;
   LCD_DATA (PHUT % 10 + 0X30) ;
   LCD_DATA (' ') ;
   LCD_DATA (GIAY / 10 + 0X30) ;
   LCD_DATA (GIAY % 10 + 0X30) ;
   
   LCD_GOTO_XY(1,0);
   LCD_DATA("BT0: UP");
   LCD_GOTO_XY(1,10);
   LCD_DATA("BT1: DW");
   LCD_GOTO_XY(2,0);
   LCD_DATA("BT2: ADJ");
   
   IF (GIA_TRI_MOD == 1)
   {
      LCD_GOTO_XY (0, 11) ;
      LCD_DATA(0xff);
   }

   ELSE IF (GIA_TRI_MOD == 2)
   {
      LCD_GOTO_XY (0, 16) ;
      LCD_DATA(0xff);
   }

   ELSE IF (GIA_TRI_MOD == 3)
   {
      LCD_GOTO_XY (0, 22) ;
      LCD_DATA(0xff);
   }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_MOD()
{
   IF ( ! INPUT (MOD) )
   {
      GIA_TRI_MOD++;
      IF (GIA_TRI_MOD >= 4) GIA_TRI_MOD = 0;
      GIAI_MA_GAN_CHO_8LED_QUET () ;
      DO{HIEN_THI_8LED_7DOAN_QUET (); }
      WHILE ( ! INPUT (MOD)) ;
   }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_UP()
{
   IF ( ! INPUT (UP) )
   {
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

      GIAI_MA_GAN_CHO_8LED_QUET () ;
      DO{ HIEN_THI_8LED_7DOAN_QUET (); }
      WHILE ( ! INPUT (UP)) ;
   }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID PHIM_DW()
{
   IF ( ! INPUT (DW) )
   {
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

      GIAI_MA_GAN_CHO_8LED_QUET () ;
      DO{ HIEN_THI_8LED_7DOAN_QUET (); }
      WHILE ( ! INPUT (DW)) ;
   }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT () ;
   
   // Dem Timer
   SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8) ;
   SET_TIMER1 (3036) ;
   ENABLE_INTERRUPTS (GLOBAL) ;
   ENABLE_INTERRUPTS (INT_TIMER1) ;
   BDN = 0; GIAY = 0; PHUT = 0; GIO = 0; GIA_TRI_MOD = 0;
   
   // Khoi tao LCD
   SETUP_LCD () ;
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DONG HO:") ;
   GIAY = 0;
   PHUT = 0;

   WHILE (TRUE)
   {
      LCD_HIENTHI_DONGHO () ;
      
      
      IF (BDN < 10) LCD_HIENTHI_DONGHO ();

      ELSE
      {
         BDN = BDN - 10;
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

