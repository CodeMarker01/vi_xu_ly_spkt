
// BAI 412
#include <tv_pickit2_shift_1.c>
#include<TV_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_lcd.c>// LCD
#include <tv_pickit2_shift_glcd128x64.c>// GLCD
#include <graphics.c>

unsigned INT8 t0,t0_tam,chuc,donvi,sp;

int1 TT_DC,TT_HT,doi_hinh;
int1 tt;
signed INT8 mp;
signed INT8 chuclcd,donvilcd; // LCD nho
signed INT8 i; // LCD to
signed INT8 chuc_glcd; //GLCD
//!void doi_hinhh()
//!{
//!   IF(doi_hinh == 0)
//!   {
//!      //HÌNH TRÒN
//!      setup_glcd (glcd_graphic_mode);
//!      glcd_mau_nen (0);
//!      glcd_circle (67, 30, 30, 0, 1);
//!      gdram_vdk_to_gdram_glcd_all () ;
//!   }
//!
//!   ELSE
//!   {
//!      //HÌNH VUÔNG
//!      setup_glcd (glcd_graphic_mode);
//!      glcd_mau_nen (0);
//!      glcd_RECT (0, 0, 127, 60, 0, 1) ;
//!      gdram_vdk_to_gdram_glcd_all ();
//!   }
//!
//!   GLCD_COMMAND(GLCD_TEXT_MODE);
//!}

unsigned INT key_4x4_dw_QUET()
{
   mpt1 = key_nhan ();

   IF (mpt1 != 0xff)
   {
      delay_ms (20) ;
      mpt1 = key_nhan ();
      DO{mpt2 = key_nhan (); HIEN_THI_8LED_7DOAN_QUET (); }
      WHILE (mpt2 == mpt1);
      delay_ms (20) ;
   }

   RETURN (mpt1) ;
}

void glcd_hienthi_t0_thuan() //GLCD
{
   glcd_command (glcd_addr_line2 + 3);
   glcd_data (sp / 10 % 10 + 0x30);
   glcd_data (sp % 10 + 0x30);
   glcd_data (".SP");
}

void glcd_hienthi_t0_nguoc()//GLCD
{
   glcd_command (glcd_addr_line2 + 3);
   glcd_data ("SP.");
   glcd_data (sp / 10 % 10 + 0x30);
   glcd_data (sp % 10 + 0x30);
}

void lcd_hienthi_so_z_toado_xy(SIGNED int8 lcd_so, x1, y1) // LCD TO
{
   lcd_GOTO_xy (x1, y1) ;
   FOR (i = 0; i < 6; i++)
   {
      IF (i == 3) lcd_goto_xy (x1 + 1, y1);
      lcd_data (lcd_so_x[lcd_so][i]);
   }
}

VOID LCD_TO_THUAN()
{
   chuc_glcd = SP / 10;

   IF (chuc_glcd == 0)
      chuc_glcd = 10;

   lcd_hienthi_so_z_toado_xy (chuc_glcd, 2, 0) ;
   lcd_hienthi_so_z_toado_xy (SP % 10, 2, 3) ;
   lcd_hienthi_so_z_toado_xy (12, 2, 6) ; // HIEN THI DAU CHAM
   lcd_hienthi_so_z_toado_xy (5, 2, 12) ;
   lcd_hienthi_so_z_toado_xy (11, 2, 15) ;
}

VOID LCD_TO_nguoc()
{
   chuc_glcd = SP / 10;

   IF (chuc_glcd == 0)
      chuc_glcd = 10;

   lcd_hienthi_so_z_toado_xy (5, 2, 0) ;
   lcd_hienthi_so_z_toado_xy (11, 2, 3) ;
   lcd_hienthi_so_z_toado_xy (12, 2, 6) ; // HIEN THI DAU CHAM
   lcd_hienthi_so_z_toado_xy (chuc_glcd, 2, 12) ;
   lcd_hienthi_so_z_toado_xy (SP % 10, 2, 15) ;
}

void giai_ma_gan_cho_8led_quet_nguoc() // LED QUET
{

   led_7dq[3] = ma7doan [5];
   led_7dq[2] = 0x8C&0X7F;
   
   led_7dq[0] = ma7doan [sp % 10];
   led_7dq[1] = ma7doan [sp / 10];
   
   
}

void giai_ma_gan_cho_8led_quet_thuan() // LED QUET
{
   led_7dq[1] = ma7doan [5];
   led_7dq[0] = 0x8C;
   
   led_7dq[2] = ma7doan [sp % 10]&0X7F;
   led_7dq[3] = ma7doan [sp / 10];
}

void hienthi_thuan()
{
   xuat_4led_7doan_4so (chuc, donvi&0X7F, 0X92, 0X8C) ;
   chuc = ma7doan[sp / 10];
   donvi = ma7doan[sp % 10];
   IF (chuc == 0xC0) chuc = 0xFF;
}

void hienthi_nguoc()
{
   xuat_4led_7doan_4so (0X92, 0X8C&0X7F, chuc, donvi) ;
   chuc = ma7doan[sp / 10];
   donvi = ma7doan[sp % 10];
   IF (chuc == 0xC0) chuc = 0xFF;
}

void hienthi_thuan_LCD_nho()
{
   lcd_GOTO_xy (0, 14) ;
   delay_us (20);
   chuclcd = sp / 10 % 10 + 0x30;
   donvilcd = sp % 10 + 0x30;

   IF (chuclcd == 0x30)
      chuclcd = 0x20;

   lcd_data (chuclcd);
   lcd_data (donvilcd);
   lcd_data (".SP");
}

void hienthi_nguoc_LCD_nho()
{
   lcd_GOTO_xy (0, 14) ;
   delay_us (20);
   chuclcd = sp / 10 % 10 + 0x30;
   donvilcd = sp % 10 + 0x30;

   IF (chuclcd == 0x30)
      chuclcd = 0x20;

   
   lcd_data ("SP.");
   lcd_data (chuclcd);
   lcd_data (donvilcd);
}

void dem_xuong()
{
   t0 = get_timer0 ();

   IF (t0 == 1)
   {
      set_timer0 (0);
      sp--;
      IF (sp == 0) sp = 99;
   }
}

void dem_len()
{
   t0 = get_timer0 ();

   IF (t0 == 1)
   {
      set_timer0 (0);
      sp++;
      IF (sp == 100) sp = 1;
   }
}

void main()
{
   set_tris_b (0x3c);
   set_up_port_ic_chot ();
   t0 = 0; TT_DC = 1; TT_HT = 1;
   hienthi_thuan ();
   setup_timer_0 (t0_off);
   set_timer0 (0);
   t0_tam = t0 = 0;
   tt = 0;
   setup_lcd ();
   lcd_command (0x40); // LCD TO
   
   FOR (i = 0; i < 64; i++) { lcd_data (lcd_ma_8doan[i]); }// LCD TO
   
   lcd_GOTO_xy (0, 0) ;
   lcd_data ("DEM SAN PHAM: ");
   
   SETUP_GLCD (GLCD_TEXT_MODE); //GLCD
   setup_glcd (glcd_graphic_mode) ;
   glcd_mau_nen (0) ;
   glcd_circle (67, 30, 30, 0, 1);
   gdram_vdk_to_gdram_glcd_all () ;
   
   
   
   DOI_HINH = 0;
   
   WHILE (true)
   {
      GLCD_COMMAND (GLCD_TEXT_MODE); //GLCD
      t0 = get_timer0 ();
      hien_thi_8led_7doan_quet (); //quet
      mp = key_4x4_dw_QUET ();
//!      doi_hinhh (); //GLCD
      IF (mp != 0xFF)
      {
         IF (mp == 0)
         {
            tt = ~tt;
         }

         IF (mp == 4)
         {
            TT_DC = ~TT_DC;
         }

         IF (mp == 8)
         {
            TT_HT = ~TT_HT;
         }

//!         IF (mp == 1)
//!         {
//!            doi_hinh = ~doi_hinh;
//!         }
      }

      IF (tt == 1)
      {
         setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);

         IF (t0 != t0_tam)
         {
            t0_tam = t0;

            IF (TT_DC == 1)
               dem_len ();

            ELSE dem_xuong ();
         }
      }

      ELSE setup_timer_0 (t0_off);
      
      IF (TT_HT == 1)
      {
         hienthi_thuan ();
         hienthi_thuan_LCD_nho ();
         giai_ma_gan_cho_8led_quet_thuan (); //quet
         LCD_TO_THUAN (); //LCD TO
         glcd_hienthi_t0_thuan ();
      }

      
      ELSE
      {
         hienthi_nguoc ();
         hienthi_nguoc_LCD_nho ();
         LCD_TO_nguoc () ;
         giai_ma_gan_cho_8led_quet_nguoc (); //quet
         glcd_hienthi_t0_nguoc ();
      }
   }
}

