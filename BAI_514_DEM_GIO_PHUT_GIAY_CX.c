
#INCLUDE <TV_PICKIT2_SHIFT_1.C>

UNSIGNED INT8 GIAY,BDN, PHUT, GIO;

#INT_TIMER1

VOID INTERRUPT_TIMER1()
{
   BDN++; SET_TIMER1 (3036) ;
}

VOID GIAI_MA_GAN_CHO_8LED_QUET()
{
   LED_7DQ[0] = MA7DOAN [GIAY % 10];
   LED_7DQ[1] = MA7DOAN [GIAY / 10];
   LED_7DQ[2] = MA7DOAN [PHUT % 10]& 0x7F;
   LED_7DQ[3] = MA7DOAN [PHUT / 10];
   LED_7DQ[4] = MA7DOAN [GIO % 10]& 0x7F;
   LED_7DQ[5] = MA7DOAN [GIO / 10];

   // LED_7DQ [2...7] = 0xFF
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8);
   SET_TIMER1 (3036);
   ENABLE_INTERRUPTS (GLOBAL);
   ENABLE_INTERRUPTS (INT_TIMER1);
   GIAY = 0; BDN = 0;
   PHUT = 58; GIO = 23;
   WHILE (TRUE)
   {
      GIAI_MA_GAN_CHO_8LED_QUET ();
      IF (BDN < 10) HIEN_THI_8LED_7DOAN_QUET () ;

      ELSE
      {
         BDN = BDN - 10;
         GIAY++;

         IF (GIAY == 60)
         {
            GIAY = 0;
            
            phut++;

            IF (phut == 60)
            {
               phut = 0;
               gio++;

               IF (gio == 24)
               {gio = 0; }
            }
         }

         
      }
   }
}

