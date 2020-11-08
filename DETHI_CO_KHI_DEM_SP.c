
#INCLUDE <TV_PICKIT2_SHIFT_1.c>

UNSIGNED INT8 T0;
UNSIGNED INT8 DONVI, CHUC, TRAM;
int1 Mode=0;
unsigned int8 i=0;
int1 modeBlink4 = 0;

#DEFINE  COUNT      BT0    //DK LED DON
#DEFINE  TIME      BT1
#DEFINE  CLR     BT2
#DEFINE  MOD     BT3

VOID GIAI_MA_HIEN_THI (UNSIGNED INT16 TAM)
{
   DONVI = MA7DOAN[TAM % 10];
   CHUC = MA7DOAN[TAM / 10 % 10];
   TRAM = MA7DOAN[TAM / 100];

   IF (TRAM == 0XC0) // led 7 doan = 0
   {
      TRAM = 0XFF;
      IF (CHUC == 0XC0) CHUC = 0XFF; // 0xC0 chinh la so hex cua so 0 led 7 doan
   }

   XUAT_4LED_7DOAN_3SO (TRAM, CHUC, DONVI) ;
}

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
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0 (0);
   
   XUAT_4LED_7DOAN_4SO (MASO0, MASO0, MASO0, MASO0);

   WHILE (TRUE)
   {
      //Nhan nut CLR
      IF (CDNN (CLR) )
      {
         for (INT i = 0; i < 3; i++)
         {
            XUAT_4LED_7DOAN_4SO (0xff, 0xff, 0xff, 0xff);
            delay_ms (500);
            XUAT_4LED_7DOAN_4SO (MASO0, MASO0, MASO0, MASO0);
            delay_ms (500);
         }
      }

      //Nhan nut COUNT
      IF (CDNN (COUNT))
      {
         Mode = ~Mode;
         SET_TIMER0 (0);
      }

      
      IF (Mode == 1)
      {
         T0 = GET_TIMER0 ();
         GIAI_MA_HIEN_THI (T0);
         IF (T0 >= 1000) SET_TIMER0 (1) ;

         IF (T0 % 10 == 0 && T0 != 0 )
         {
            if(i<4 && ModeBlink4 == 0)
            {
               XUAT_4LED_7DOAN_4SO (0xff, 0xff, 0xff, 0xff);
               delay_ms (500);
               GIAI_MA_HIEN_THI (T0);
               delay_ms (500);
               i++;
               
            }
            if (i==4)
            {
              modeBlink4 = 1;
               i=0;
            }
         }
      }
   }
}


