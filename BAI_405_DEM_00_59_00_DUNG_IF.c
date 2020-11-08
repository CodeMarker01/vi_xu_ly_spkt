
//******************************************************************************************
#INCLUDE <TV_PICKIT2_SHIFT_1.C>

unSIGNED INT8 I=0;

UNSIGNED INT8 dem=0;

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   XUAT_4LED_7DOAN_4SO (0XB0, 0XA4, 0XF9, 0XC0);

   WHILE (TRUE)
   {
      IF (dem < 60)
      {
         XUAT_4LED_7DOAN_4SO (MA7DOAN[I / 10], MA7DOAN[I % 10],0xff, 0xff);
         DELAY_MS (500);
         dem++;
         I++;
      }

      else IF ((dem < 120) && (dem >= 60) )
      {
         XUAT_4LED_7DOAN_4SO (MA7DOAN[I / 10], MA7DOAN[I % 10],0xff, 0xff);
         DELAY_MS (500);
         dem++;
         I--;
      }

      else
      {
         i = 0;
         dem = 0;
      }
   }
}

