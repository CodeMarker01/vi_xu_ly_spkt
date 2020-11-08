
#INCLUDE <TV_PICKIT2_SHIFT_1.C>

SIGNED INT8 I;

UNSIGNED INT8 giay = 0;
unsigned INT8 phut = 0;

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   XUAT_4LED_7DOAN_4SO (0XB0, 0XA4, 0XF9, 0XC0);

   WHILE (TRUE)
   {
      XUAT_4LED_7DOAN_4SO (MA7DOAN[phut/10],MA7DOAN[phut%10] , MA7DOAN[giay / 10], MA7DOAN[giay % 10]);
      DELAY_MS (500);
      giay++;

      IF (giay == 60)
      {
         phut++;
         giay = 0;
      }
   }
}

