
#INCLUDE <TV_PICKIT2_SHIFT_1.C>

UNSIGNED INT8 T0,T0_TAM;

unsigned INT8 GIAY=0, PHUT=0, BDN=0;

#DEFINE  COUNT      BT0    //DK LED DON
#DEFINE  TIME      BT1
#DEFINE  CLR     BT2
#DEFINE  MOD     BT3

// Dem TIMER
#INT_TIMER1
VOID INTERRUPT_TIMER1()
{
   BDN++; SET_TIMER1 (3036) ;
}

VOID GIAI_MA_DEM_TIMER()
{
   XUAT_4LED_7DOAN_4SO(MA7DOAN[PHUT/10], MA7DOAN[PHUT%10], MA7DOAN[GIAY/10], MA7DOAN[GIAY%10]);
   IF (MA7DOAN[PHUT/10]==0XC0) // led 7 doan = 0
   {
      MA7DOAN[PHUT/10]=0XFF;
      IF (MA7DOAN[PHUT%10]==0XC0) MA7DOAN[PHUT%10]=0XFF; // 0xC0 chinh la so hex cua so 0 led 7 doan
      IF (MA7DOAN[GIAY/10]==0XC0) MA7DOAN[GIAY/10]=0XFF;
   }
   

   // LED_7DQ [2...7] = 0xFF
}

int Mode=0;
//!INT1 modeBlink4=0;
unsigned INT8 i=0;
//!UNSIGNED int8 dem=0;

//*****************************************************************************
int CDNN(INT1 pin)
{
   IF (!input (pin))
   {
      delay_ms (20);

      IF (!input (pin) )
      {
         WHILE (!input (pin) );
         RETURN 1;
      }
   }

   RETURN 0;
}

//*****************************************************************************
VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   
   //Counter
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0 (0);
   T0_TAM = T0 = 0;
   
   //TIMER
   SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8) ;
   SET_TIMER1 (3036) ;
   ENABLE_INTERRUPTS (GLOBAL) ;
   ENABLE_INTERRUPTS (INT_TIMER1) ;
   GIAY = 0; BDN = 0;
   
   XUAT_4LED_7DOAN_4SO (MASO0, MASO0, MASO0, MASO0);

   WHILE (TRUE)
   {
      T0 = GET_TIMER0 ();
      
      //Nhan nut COUNT
      IF (CDNN (COUNT))
      {
         Mode = 1;
         SET_TIMER0 (0);
         XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0);
      }

      
      // Nhan nut TIME
      IF (CDNN (TIME))
      {
         Mode = 2;
      }

      
      IF (Mode == 1)
      {
         IF (T0 != T0_TAM)
         {
            T0_TAM = T0;
            XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0);
            IF (T0 >= 101) SET_TIMER0 (1) ;

            IF (T0 % 10 == 0)
            {
               FOR (i = 0; i < 8; i++)
               {
                  XUAT_4LED_7DOAN_4SO (0xff, 0xff, 0xff, 0xff);
                  delay_ms (200);
                  XUAT_4LED_7DOAN_GIAIMA_XOA_SO0 (T0);
                  delay_ms (200);
                  i++;
               }

               IF (i == 4)
               {
                  
                  i = 0;
               }
            }
            
            GIAY=0;
         }
      }

      IF (Mode == 2)
      {
      IF (T0 != T0_TAM)
         {
            T0_TAM = T0;
            GIAY=0;
            PHUT=0;
            SET_TIMER1 (3036) ;
            BDN++;
         }
         
         GIAI_MA_DEM_TIMER();
         IF (BDN < 10) GIAI_MA_DEM_TIMER();

         ELSE
         {
            BDN = BDN - 10;
            GIAY++;
            IF (GIAY == 60)
            {
               GIAY = 0;
               PHUT++;
            }
            IF(PHUT==60) PHUT=0;
         }
      }

      //Nhan nut CLR
      IF (CDNN (CLR) )
      {
         SET_TIMER0 (0);
         for (INT i = 0; i < 3; i++)
         {
            XUAT_4LED_7DOAN_4SO (0xff, 0xff, 0xff, 0xff);
            delay_ms (500);
            XUAT_4LED_7DOAN_4SO (MASO0, MASO0, MASO0, MASO0);
            delay_ms (500);
         }
      }
   }
}

