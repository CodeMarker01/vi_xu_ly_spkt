
#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_32LED_DON.C>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>
#INCLUDE <TV_PICKIT2_SHIFT_KEY4X4_138.C>
#INCLUDE <TV_PICKIT2_SHIFT_GLCD128X64.C>
#INCLUDE <GRAPHICS.C>

UNSIGNED INT8 T0, T0_TAM;
UNSIGNED INT8 I, CHUC_LCD, DONVI_LCD, CHUC_GLCD, DONVI_GLCD, MP;
UNSIGNED INT1 TT_HT;

// HIEN THI CHU U
CONST UNSIGNED CHAR LCD_CHU_U[1][6] =
{
   
   0,32,2,5,3,4, 
};

// NGAT
SIGNED INT8 GIAY, BDN;
#INT_TIMER1
VOID INTERRUPT_TIMER1()
{
   BDN++;
   SET_TIMER1 (3036);
}

// HAM HIEN THI CHU X
VOID LCD_HIENTHI_CHU_Z_TOADO_XY(SIGNED INT8 LCD_SO, X1, Y1)
{
   LCD_GOTO_XY (X1, Y1) ;
   FOR (I = 0; I < 6; I++)
   {
      IF (I == 3) LCD_GOTO_XY (X1 + 1, Y1);
      LCD_DATA (LCD_CHU_U[LCD_SO][I]);
   }
}

// HAM HIEN THI SO LON
VOID LCD_HIENTHI_SO_Z_TOADO_XY(SIGNED INT8 LCD_SO, X1, Y1)
{
   LCD_GOTO_XY (X1, Y1) ;
   FOR (I = 0; I < 6; I++)
   {
      IF (I == 3) LCD_GOTO_XY (X1 + 1, Y1);
      LCD_DATA (LCD_SO_X[LCD_SO][I]);
   }
}

// HIEN THI RA LCD
VOID HIEN_THI_LCD (UNSIGNED T0)
{
   CHUC_LCD = T0 / 10;
   DONVI_LCD = T0 % 10;
   IF (CHUC_LCD == 0) CHUC_LCD = 10;
   LCD_HIENTHI_SO_Z_TOADO_XY (CHUC_LCD, 2, 16);
   LCD_HIENTHI_SO_Z_TOADO_XY (DONVI_LCD, 2, 0);
   LCD_HIENTHI_CHU_Z_TOADO_XY (0, 0, 9);
}

// HIEN THI RA GLCD
VOID HIEN_THI_GLCD(UNSIGNED GIAY)
{
   SETUP_GLCD (GLCD_TEXT_MODE);
   CHUC_GLCD = GIAY / 10 + 0X30;
   DONVI_GLCD = GIAY % 10 + 0X30;
   IF (CHUC_GLCD == 0X30) CHUC_GLCD = 0X20;
   GLCD_COMMAND (0X89);
   GLCD_DATA ("Gi");
   GLCD_COMMAND (0X8C);
   GLCD_DATA ("=");
   
   GLCD_COMMAND (0X8E);
   GLCD_DATA (CHUC_GLCD);
   GLCD_DATA (DONVI_GLCD);
}


VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   SET_TRIS_B (0X3C);
   
   //KHOI TAO COUNTER
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0 (8);
   
   // KHOI TAO LCD
   SETUP_LCD ();
   LCD_COMMAND (0X40);
   FOR (I = 0; I < 64; I++)
   {
      LCD_DATA (LCD_MA_8DOAN[I]);
   }
   
   // DEM COUNTER
   T0_TAM = T0 = 0;
   
   //DEM GIAY DUNG NGAT
   SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8);
   SET_TIMER1 (3036);
   ENABLE_INTERRUPTS (GLOBAL);
   ENABLE_INTERRUPTS (INT_TIMER1);
   GIAY = 15;
   BDN = 0;
   
   // KHOI TAO GLCD
   SETUP_GLCD (GLCD_CLEAR_DISPLAY);
   SETUP_GLCD (GLCD_GRAPHIC_MODE);
   GLCD_MAU_NEN (0);
   
   WHILE (TRUE)
   {
      T0 = GET_TIMER0 ();
      IF (T0 != T0_TAM)
      {
         T0_TAM = T0;
//!         IF (T0 > 22) SET_TIMER0 (12) ;
         IF (T0 > 14) SET_TIMER0 (8) ;
//!         HIEN_THI_AB ();
            HIEN_THI_LCD (T0);
      }
      
      IF (BDN < 10) HIEN_THI_GLCD (GIAY); 
      ELSE
      {
         BDN = BDN - 10;
         GIAY--;
         IF (GIAY < 5) GIAY = 15;
      }
      
      SETUP_GLCD (GLCD_GRAPHIC_MODE);
      GLCD_MAU_NEN (0);
      GLCD_CIRCLE (30, 30, 20, 0, 1) ;
      GLCD_RECT (75, 11, 115, 51, 0, 1) ;
      GDRAM_VDK_TO_GDRAM_GLCD_ALL ();
   }
}
