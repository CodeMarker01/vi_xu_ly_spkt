#INCLUDE <TV_PICKIT2_SHIFT_1.C>
UNSIGNED INT16 TG_DELAY;

VOID MAIN ()
{
   SET_UP_PORT_IC_CHOT();
   TG_DELAY=1;
   WHILE (TRUE)
      {
//!         XUAT_8LED_7DOAN_QUET_1(0XFE, 0XC0);    //0
//!         DELAY_MS(TG_DELAY);
//!         
//!         XUAT_8LED_7DOAN_QUET_1(0XFD, 0XF9);    //1
//!         DELAY_MS(TG_DELAY);
//!         
//!         XUAT_8LED_7DOAN_QUET_1(0XFB, 0XA4);    //2
//!         DELAY_MS(TG_DELAY);
//!         
//!         XUAT_8LED_7DOAN_QUET_1(0XF7, 0XB0);    //3
//!         DELAY_MS(TG_DELAY);
//!         
//!         XUAT_8LED_7DOAN_QUET_1(0XEF, 0X99);    //4
//!         DELAY_MS(TG_DELAY);
//!         
//!         XUAT_8LED_7DOAN_QUET_1(0XDF, 0X92);    //5
//!         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_1(0XBF, 0XF9);    //6
         DELAY_MS(TG_DELAY);
         
         XUAT_8LED_7DOAN_QUET_1(0X7F, 0XC0);    //7
         DELAY_MS(TG_DELAY);
         
         
      }
}
