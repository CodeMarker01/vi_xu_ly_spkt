#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds1307_i2c.c>
#include <tv_pickit2_shift_glcd128x64.c>
#INCLUDE <GRAPHICS.C>
#include <tv_pickit2_shift_ds18b20.c>
unsigned int16 NDNGUYEN_TAM,NDTP_TAM;
unsigned CHAR giatri_mod;
signed INT8 I;
unsigned INT16 BDN;

#INT_TIMER1
VOID INTERRUPT_TIMER1()
{
   BDN++;
   SET_TIMER1 (3036) ;
} 
void lcd_hienthi_so_z_toado_xy(SIGNED int8 lcd_so, x1, y1)
{
   lcd_GOTO_xy (x1, y1) ;
   FOR (i = 0; i < 6; i++)
   {
      IF (i == 3) lcd_goto_xy (x1 + 1, y1);
      lcd_data (lcd_so_x[lcd_so][i]);
   }
}

VOID HIENTHI_GLCD ()
{
    GLCD_COMMAND (GLCD_TEXT_MODE);
   GLCD_COMMAND (GLCD_ADDR_LINE2);
   GLCD_DATA("  ");
   GLCD_DATA ((NDNGUYEN_TAM/10) + 0X30) ;
   GLCD_DATA ((NDNGUYEN_TAM% 10) + 0X30) ;
   GLCD_COMMAND (GLCD_ADDR_LINE3);
   GLCD_DATA("            .");
   GLCD_DATA ((NDTP_TAM/10) + 0X30) ;
   GLCD_DATA ((NDTP_TAM% 10) + 0X30) ;

}
//!VOID HT_GLCD_LCD()
//!{ IF (GIAY_DS13 > 10)
//!   { 
//!      GLCD_COMMAND(GLCD_CLEAR_DISPLAY );
//!      SETUP_GLCD (GLCD_GRAPHIC_MODE);
//!      GLCD_MAU_NEN (0); 
//!      glcd_line(128, 0,0, 64, 1);
//!      GDRAM_VDK_TO_GDRAM_GLCD_ALL ();
//!      lcd_hienthi_so_z_toado_xy (NDNGUYEN_TAM / 10, 0, 7) ;
//!      lcd_hienthi_so_z_toado_xy (NDNGUYEN_TAM % 10, 0, 10) ;
//!      LCD_GOTO_XY(3,6);
//!      LCD_DATA(".");
//!      lcd_hienthi_so_z_toado_xy (NDTP_TAM / 10, 2, 7) ;
//!      lcd_hienthi_so_z_toado_xy (NDTP_TAM % 10, 2, 10) ;
//!   }
//!   ELSE 
//!   {
//!   
//!      GLCD_COMMAND(GLCD_CLEAR_DISPLAY );
//!   SETUP_GLCD (GLCD_GRAPHIC_MODE);
//!   GLCD_MAU_NEN (0);
//!   GLCD_CIRCLE (23, 22, 15, 0, 1) ;
//!   GLCD_CIRCLE (110, 40, 15, 0, 1) ;
//!    glcd_line(128, 0,0, 64, 1);
//!   GDRAM_VDK_TO_GDRAM_GLCD_ALL ();
//!   HIENTHI_GLCD();
//!    SETUP_LCD();
//!   }
//!}

VOID HT_4LED_7DOAN()
{ IF (THU_DS13 == 0X1) XUAT_4LED_7DOAN_4SO(MA7DOAN[GIAY_DS13/16],MA7DOAN[GIAY_DS13%16]&0X7F,0XC6,0XAB);
  ELSE XUAT_4LED_7DOAN_4SO(MA7DOAN[GIAY_DS13/16],MA7DOAN[GIAY_DS13%16]&0X7F,0XFF,MA7DOAN[THU_DS13]);
}
VOID NHAP_NHAY_CON_TRO()
{
   SWITCH (GIATRI_MOD)
   {
      CASE 2: XUAT_4LED_7DOAN_4SO(MA7DOAN[GIAY_DS13/16],MA7DOAN[GIAY_DS13%16]&0X7F,0XFF,0XFF);
      BREAK;
      CASE 1: IF (THU_DS13 == 0X1) XUAT_4LED_7DOAN_4SO(0XFF,0XFF,0XC6,0XAB);
               ELSE XUAT_4LED_7DOAN_4SO(0XFF,0XFF,0XFF,MA7DOAN[THU_DS13]);
      BREAK;
      DEFAULT:BREAK;
   }
}

void hien_thi_gia_tri_mod ( )
{
 IF (GIATRI_MOD ==1) XUAT_32LED_DON_1DW(0X000000FF);
 ELSE IF (GIATRI_MOD ==2) XUAT_32LED_DON_1DW(0X0000000F);
 ELSE TAT_32LED_DON();
}
void phim_mod()
{
   IF (!input (mod))
   {
      delay_ms (20);
      {
         IF (!input (mod))
         {
            IF (giatri_mod < 2) giatri_mod++;
            ELSE giatri_mod = 0;
            hien_thi_gia_tri_mod ();
            WHILE ( ! input (mod)) ;
         }
      }
   }
}
UNSIGNED INT8 HIEU_CHINH_SO_BCD_TANG(UNSIGNED INT8 X)
{
   UNSIGNED INT8 Y;
   Y = X;
   X = X & 0X0F;
   IF (X==0X0A)  Y = Y + 6;
   RETURN (Y);
}

UNSIGNED INT8 HIEU_CHINH_SO_BCD_GIAM(UNSIGNED INT8 X)
{
   UNSIGNED INT8 Y;
   Y = X;
   X = X & 0X0F;
   IF (X==0X0F)  Y = Y - 6;
   RETURN (Y);
}
VOID LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH()
{
   NAP_THOI_GIAN_HTAI_VAO_DS13B07();
         HIENTHI_GLCD();
      HT_4LED_7DOAN();
}
void phim_up()
{
   IF (!input (up))
   {
      delay_ms (20);

      IF (!input (up))
      {
         SWITCH (giatri_mod)
         {
            case 1: IF (giay_ds13 == 0x59) giay_ds13 = 0;

            ELSE
            {
               giay_ds13++;
               giay_ds13 = hieu_chinh_so_bcd_tang (giay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            BREAK;
            case 2: IF (THU_ds13 == 0x7) THU_ds13 = 0X1;

            ELSE
            {
               THU_ds13++;
               THU_ds13 = hieu_chinh_so_bcd_tang (THU_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            BREAK;
            DEFAULT: break;
         }

         WHILE ( ! input (up)) ;
      }
   }
}
void phim_dw()
{
   IF (!input (dw))
   {
      delay_ms (20);

      IF (!input (dw))
      {
         SWITCH (giatri_mod)
         {
            case 1: IF (giay_ds13 == 0) giay_ds13 = 0x59;

            ELSE
            {
               giay_ds13--;
               giay_ds13 = hieu_chinh_so_bcd_giam (giay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            BREAK;
            case 2: IF (THU_ds13 == 0X1) THU_ds13 = 0x7;

            ELSE
            {
               THU_ds13--;
               THU_ds13 = hieu_chinh_so_bcd_giam (THU_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            BREAK;
            DEFAULT: break;
         }

         WHILE ( ! input (dw)) ;
      }
   }
}
VOID MAIN()
{
   SET_UP_PORT_IC_CHOT ();
   SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8);
   SET_TIMER1 (3036);
   ENABLE_INTERRUPTS (GLOBAL);
   ENABLE_INTERRUPTS (INT_TIMER1);
   BDN = 0;
   
   SETUP_GLCD (GLCD_CLEAR_DISPLAY);
   SETUP_GLCD (GLCD_GRAPHIC_MODE);
   GLCD_MAU_NEN (0);
   GLCD_CIRCLE (23, 22, 15, 0, 1) ;
   GLCD_CIRCLE (110, 40, 15, 0, 1) ;
    glcd_line(128, 0,0, 64, 1);
   GDRAM_VDK_TO_GDRAM_GLCD_ALL ();
   doc_thoi_gian_tu_realtime ();
   IF (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai ();
      nap_thoi_gian_htai_vao_ds13b07 ();
   }
   khoi_tao_ds18b20();  
   WHILE (true)
   {
      doc_thoi_gian_tu_realtime ();
     DOC_GIATRI_DS18B20();
      IF (NDTP != NDTP_TAM)
      {
        NDNGUYEN_TAM=NDNGUYEN;
        NDTP_TAM=NDTP;
      }
//!      HT_GLCD_LCD();
      HT_4LED_7DOAN();
      IF (BDN<10) 
      {
         IF (BDN<5) nhap_nhay_con_tro ();
         ELSE 
         {
         HIENTHI_GLCD();
         HT_4LED_7DOAN();
         }
   }
   ELSE BDN=BDN-10;
      phim_mod ();
      PHIM_UP();
      PHIM_DW();
   }
 }
