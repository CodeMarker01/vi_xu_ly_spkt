
#INCLUDE <TV_PICKIT2_SHIFT_1.c>
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>
#INCLUDE  <TV_PICKIT2_SHIFT_GLCD128X64.C>
#include <tv_pickit2_shift_key4x4_138.c>
#DEFINE  START      BT0    //DK LED DON
#DEFINE  PAUSE      BT1
#DEFINE  DAOCHIEU     BT2
#DEFINE  DAO     BT3
//!#DEFINE  CDO     BT3

UNSIGNED INT16 T0,T0_TAM;

UNSIGNED INT8 DV_SEG, CH_SEG, TR_SEG;
UNSIGNED INT8 DV_LCD, CH_LCD, TR_LCD;
UNSIGNED INT8 DV_GLCD, CH_GLCD, TR_GLCD;
UNSIGNED INT8 DV_LCDBig, CH_LCDBig, TR_LCDBig;
unsigned INT i, mode=0;
unsigned INT8 mp;
int1 TT_DC;
int1 Dao_HienThi=1;
unsigned int8 sp;

// Hien thi 4 LED7
VOID GIAI_MA_HIEN_THI ()
{
   DV_SEG = MA7DOAN[T0 % 10];
   CH_SEG = MA7DOAN[T0 / 10 % 10];
   IF (CH_SEG == 0XC0) CH_SEG = 0XFF; // 0xC0 chinh la so hex cua so 0 led 7 doan
   
   IF (Dao_HienThi == 0)
      XUAT_4LED_7DOAN_4SO (CH_SEG, DV_SEG&0x7f, 0x92, 0x8c);
   ELSE
      XUAT_4LED_7DOAN_4SO (0x92, 0x8c&0x7f, CH_SEG, DV_SEG);
}

// Hien thi Led quet
VOID GIAI_MA_GAN_CHO_8LED_QUET()
{
   LED_7DQ[5] = MA7DOAN [T0 / 10 % 10];
   LED_7DQ[4] = MA7DOAN [T0 % 10]&0x7f;
   LED_7DQ[3] = 0x92;
   LED_7DQ[2] = 0x8c;
   IF (T0 == 0) LED_7DQ[5] = 0xff;

   // LED_7DQ [2...7] = 0xFF
}

// Hien thi LCD so nho
VOID HIENTHI_LCD()
{
   
   DELAY_US (20);
   
   CH_LCD = (T0 / 10 % 10) + 0x30;
   DV_LCD = T0 % 10 + 0x30;
   
   IF (CH_LCD == 0x30)
   {
      CH_LCD = " ";
   }

   IF (Dao_HienThi == 0)
   {
      LCD_GOTO_XY (0, 15) ;
      LCD_DATA (CH_LCD);
      LCD_DATA (DV_LCD);
      LCD_DATA (" SP");
   }

   ELSE
   {
      LCD_GOTO_XY (0, 15) ;
      LCD_DATA (" SP");
      LCD_DATA (CH_LCD);
      LCD_DATA (DV_LCD);
   }
}

//Hien thi LCD so lon
VOID LCD_HIENTHI_SO_Z_TOADO_XY (SIGNED INT8 LCD_SO, SIGNED INT8 X1, SIGNED INT8 Y1)
{
   LCD_GOTO_XY (X1, Y1) ;
   FOR (I = 0; I < 6; I++)
   {
      IF (I == 3) LCD_GOTO_XY (X1 + 1, Y1);
      LCD_DATA (LCD_SO_X[LCD_SO][I]);
   }
}

VOID HIENTHI_LCD_KichThuocLon()
{
   CH_LCDBig = T0 / 10 % 10;
   DV_LCDBig = T0 % 10;
   
   IF (CH_LCDBig == 0) CH_LCDBig = 10;
   LCD_COMMAND (0x40);
   DELAY_US (20);
   FOR (I = 0; I < 64; I++)
   { LCD_DATA (LCD_MA_8DOAN[I]); }
   IF (Dao_HienThi == 0)
   {
      lcd_hienthi_so_z_toado_xy (CH_LCDBig, 2, 3) ;
      lcd_hienthi_so_z_toado_xy (DV_LCDBig, 2, 6) ;
      lcd_hienthi_so_z_toado_xy (10, 2, 9) ;
      lcd_hienthi_so_z_toado_xy (5, 2, 12) ;
      lcd_hienthi_so_z_toado_xy (11, 2, 15) ;
   }

   ELSE
   {
      lcd_hienthi_so_z_toado_xy (5, 2, 12) ;
      lcd_hienthi_so_z_toado_xy (11, 2, 15) ;
      lcd_hienthi_so_z_toado_xy (10, 2, 9) ;
      lcd_hienthi_so_z_toado_xy (CH_LCDBig, 2, 3) ;
      lcd_hienthi_so_z_toado_xy (DV_LCDBig, 2, 6) ;
   }
}

// Hien thi GLCD
VOID HIENTHI_GLCD_T0()
{
   GLCD_COMMAND (GLCD_ADDR_LINE2);
   DELAY_US (20);
   
   CH_GLCD = (T0 / 10 % 10) + 0x30;
   DV_GLCD = T0 % 10 + 0x30;
   
   
   
   IF (CH_GLCD == 0x30)
   {
      CH_GLCD = " ";
   }

   
   IF (Dao_HienThi == 0)
   {
      GLCD_DATA (CH_GLCD);
      GLCD_DATA (DV_GLCD);
      GLCD_DATA (" SP");
   }

   ELSE
   {
      GLCD_DATA (" SP");
      GLCD_DATA (CH_GLCD);
      GLCD_DATA (DV_GLCD);
   }

   GDRAM_VDK_TO_GDRAM_GLCD_ALL();
}

// Chong doi nut nhan
int1 CDNN(INT1 pin)
{
   IF (!input (pin))
   {
      delay_ms (20);

      IF ( ! input (pin) )
      {
         WHILE ( ! input (pin)) 
         {HIEN_THI_8LED_7DOAN_QUET ();}
         RETURN 1;
      }
   }
   RETURN 0;
}

VOID KT_DAO()
{
   IF(!INPUT(BT3))
   {
      DELAY_MS(20);
      IF(!INPUT(BT3))
      {
         DAO_HIENTHI = ~DAO_HIENTHI;
         GIAI_MA_HIEN_THI ();
         
         WHILE(!INPUT(BT3)) { HIEN_THI_8LED_7DOAN_QUET(); }
      }
   }
}

// COUNTER DEM LEN DEM XUONG
void dem_xuong()
{
//!   t0 = get_timer0 ();

   IF (t0 == 1)
   {
      set_timer0 (0);
      sp--;
      IF (sp == 0) sp = 99;
   }
}

void dem_len()
{
//!   t0 = get_timer0 ();

   IF (t0 == 1)
   {
      set_timer0 (0);
      sp++;
      IF (sp == 100) sp = 1;
   }
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   
   //Khai bao ma tran phim
   set_tris_b (0x3c);
   
   //Khai bao LCD
   SETUP_LCD ();
   LCD_GOTO_XY (0, 0) ;
   LCD_DATA ("DEM SAN PHAM:");
   
   //Khai bao GLCD
   SETUP_GLCD (GLCD_GRAPHIC_MODE);
   SETUP_GLCD (GLCD_TEXT_MODE);
//!   GLCD_COMMAND (GLCD_GRAPHIC_MODE);
//!   GLCD_COMMAND (GLCD_TEXT_MODE); //672
   LCD_GOTO_XY (0, 0) ;
   GLCD_COMMAND (GLCD_ADDR_LINE1);
   GLCD_DATA ("DEM SAN PHAM:");
   GDRAM_VDK_TO_GDRAM_GLCD_ALL();

   //Dem counter
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0 (0);
   T0 = T0_TAM = 0;
   
   //Hien thi len 4 module
   HIENTHI_LCD ();
   GIAI_MA_HIEN_THI ();
   HIENTHI_LCD_KichThuocLon ();
   GIAI_MA_GAN_CHO_8LED_QUET ();
   HIENTHI_GLCD_T0 ();
   
   WHILE (TRUE)
   {
   
      IF (CDNN (START))
      {
         mode++;
         IF (mode >= 2) mode = 0;
      }
      
      IF (CDNN (DAO))
      {
         Dao_HienThi = ~ Dao_HienThi;
         GIAI_MA_HIEN_THI ();
      }
      
      IF (CDNN(DAOCHIEU))
      {
         TT_DC = ~TT_DC;
      }
      
      

//!      KT_DAO();
      
      
      GLCD_COMMAND (GLCD_ADDR_LINE3);
      GLCD_DATA ("Mode = ");
      GLCD_DATA (mode + 0x30);
      LCD_GOTO_XY (1, 0) ;
      LCD_DATA ("Dao HT = ");
      LCD_DATA (Dao_HienThi + 0x30);
      GDRAM_VDK_TO_GDRAM_GLCD_ALL();
      
//!      mp = key_4x4_dw ();
//!      IF (mp != 0xff)
//!      {
//!         IF (mp == 0)
//!         {
//!            mode++;
//!            IF (mode >= 2) mode = 0;
//!         }
//!      }
//!
      
      HIEN_THI_8LED_7DOAN_QUET ();
      
      IF (mode == 1)
      {
         SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
//!         T0 = GET_TIMER0 ();
         IF (T0 != T0_TAM)
      {
         T0_TAM = T0;
         HIENTHI_LCD ();
         GIAI_MA_HIEN_THI ();
         HIENTHI_LCD_KichThuocLon ();
         GIAI_MA_GAN_CHO_8LED_QUET ();
         HIENTHI_GLCD_T0 ();
         IF (TT_DC == 1)
         {
               t0 = get_timer0 ();
               dem_len ();
         }

            ELSE 
            {
               t0 = get_timer0 ();
               dem_xuong ();
               
            }
      }
      }
      ELSE
      {
         SETUP_TIMER_0 (T0_OFF);
      }
//!
      

//!      HIENTHI_LCD ();
//!         GIAI_MA_HIEN_THI ();
//!         HIENTHI_LCD_KichThuocLon ();
//!         GIAI_MA_GAN_CHO_8LED_QUET ();
//!         HIENTHI_GLCD_T0 ();
//!      IF (T0 >= 101) SET_TIMER0 (1) ;
      
   }
}

