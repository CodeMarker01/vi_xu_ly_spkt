#INCLUDE <TV_PICKIT2_SHIFT_1.C>
UNSIGNED INT16 TG_DELAY;

VOID MAIN ()
{
   SET_UP_PORT_IC_CHOT();
   TG_DELAY=1;
   WHILE (TRUE)
      {

         
         XUAT_8LED_7DOAN_QUET_2(7, 0XF9);    //1
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(6, 0XF8);    //7
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(5, 0XF9);    //1
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(4, 0X99);    //4
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(3, 0XF9);    //1
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(2, 0XA4);    //2
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(1, 0XA4);    //2
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_2(0, 0XC0);    //0
         DELAY_MS(TG_DELAY);
         
         
      }
}
