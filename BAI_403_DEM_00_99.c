#INCLUDE <TV_PICKIT2_SHIFT_1.C>
SIGNED INT8 I;

VOID MAIN()

{     SET_UP_PORT_IC_CHOT();
      XUAT_4LED_7DOAN_4SO(0XB0, 0XA4, 0XF9, 0XC0);
      WHILE(TRUE)
      {
         FOR (I=0;I<99;I++)
            {
//!               XUAT_4LED_7DOAN_1SO(MA7DOAN[I]);
               XUAT_4LED_7DOAN_4SO(0XB0, 0XA4, MA7DOAN[I/10], MA7DOAN[I%10]);
               DELAY_MS(100);
            }
      }
}
