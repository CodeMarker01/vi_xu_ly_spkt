#INCLUDE <TV_PICKIT2_SHIFT_1.c>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.c>
CONST UNSIGNED CHAR HANG2[]={0X0A,0X15,0X11,0X11,0X0A,0X04,0,0};
SIGNED INT8 I;

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT();
   SETUP_LCD();
   LCD_GOTO_XY(0,0);
   LCD_DATA("HIEN THI TRAI TIM");
   LCD_COMMAND(0X40);
   FOR(I=0;I<8;I++)  {  LCD_DATA(HANG2[I]);}
   LCD_GOTO_XY(1,0); DELAY_US(20);
   LCD_DATA(0);
   
   WHILE(TRUE);
   
}

