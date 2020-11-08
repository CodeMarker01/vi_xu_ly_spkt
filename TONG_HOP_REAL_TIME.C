#include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_DS13B07_I2C.c>
#include <tv_pickit2_shift_glcd128x64.c>
#include <graphics.c>


signed INT8 i;
unsigned INT8 dv_giay,ch_giay,ch_phut,dv_phut,dv_gio,ch_gio;
void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [GIAY_DS13%16];
   led_7dq[1] = ma7doan [GIAY_DS13/16];
   led_7dq[2] = 0XBF;
   led_7dq[3] = ma7doan [PHUT_DS13%16 ];
   led_7dq[4] = ma7doan [PHUT_DS13/16 ];
   led_7dq[5] = 0XBF;
   led_7dq[6] = ma7doan [GIO_DS13%16];
   led_7dq[7] = ma7doan [GIO_DS13/16 ];
}

void lcd_hienthi_so_z_toado_xy(SIGNED int8 lcd_so, x1, y1)
{
   lcd_GOTO_xy(x1,y1);
   FOR (i=0;i<6;i++)
   {
      IF (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void giaima_hienthi_to()
{
ch_giay=GIAY_DS13/16; 
dv_giay=GIAY_DS13%16; 

ch_phut=PHUT_DS13/16 ;
dv_phut=PHUT_DS13%16 ;

ch_gio=GIO_DS13/16  ;
dv_gio=GIO_DS13%16 ;

}
void HT_DS1307_to( )
{     
      lcd_command(0x82);
      lcd_data("GIO");
      lcd_command(0x88);
      lcd_data("PHUT");
      lcd_command(0x8F);
      lcd_data("GIAY");
      lcd_hienthi_so_z_toado_xy(ch_gio,2,0);lcd_hienthi_so_z_toado_xy(dv_gio,2,3);
      
     // lcd_hienthi_so_z_toado_xy(19,2,6);
      
      lcd_hienthi_so_z_toado_xy(ch_phut,2,7);lcd_hienthi_so_z_toado_xy(dv_phut,2,10);
      
     //  lcd_hienthi_so_z_toado_xy(19,2,12);
       
      lcd_hienthi_so_z_toado_xy(ch_giay,2,14);lcd_hienthi_so_z_toado_xy(dv_giay,2,17);
   
}


void HT_DS1307 ( )
{     
      LCD_COMMAND (0x8C);   
      LCD_DATA(GIO_DS13/16  +0X30);    LCD_DATA(GIO_DS13%16  +0X30);
      LCD_DATA(' ');
      LCD_DATA(PHUT_DS13/16 +0X30);    LCD_DATA(PHUT_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(GIAY_DS13/16 +0X30);    LCD_DATA(GIAY_DS13%16 +0X30);
      LCD_COMMAND (0xC6);
      LCD_DATA("THU");
      LCD_DATA(THU_DS13 +0X30); 
      LCD_COMMAND (0xCC);  
      LCD_DATA(NGAY_DS13/16 +0X30);    LCD_DATA(NGAY_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(THANG_DS13/16 +0X30);   LCD_DATA(THANG_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(NAM_DS13/16 +0X30);     LCD_DATA(NAM_DS13%16 +0X30); 
}

void main()
{
   set_up_port_ic_chot();
   setup_lcd () ;
   doc_thoi_gian_tu_realtime () ;
   lcd_command(0x40);
   FOR (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   
   IF (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai () ;
      NAP_THOI_GIAN_HTAI_VAO_DS13B07 () ;
   }

   doc_thoi_gian_tu_realtime();
   giaytam = giay_ds13;


   setup_glcd(glcd_text_mode);
   setup_glcd(glcd_graphic_mode);
   glcd_mau_nen(0);
   glcd_circle(21, 32, 20, 0, 1);
   glcd_circle(64, 32, 20, 0, 1);
   glcd_circle(106, 32, 20, 0, 1);
   gdram_vdk_to_gdram_glcd_all();

   WHILE (true)
   {
      doc_thoi_gian_tu_realtime () ;

      IF (giaytam != giay_ds13)
      {
         giaytam = giay_ds13;
//!         HT_DS1307();
          giai_ma_gan_cho_8led_quet();
        
      }
       for(int i=0;i<200;i++)
       {
       hien_thi_8led_7doan_quet();
       }
       
       giaima_hienthi_to();
       HT_DS1307_to( );
    
   glcd_command(glcd_text_mode);
   glcd_command (glcd_addr_line3+1);
   glcd_data (GIO_DS13/16  +0X30);
   glcd_data (GIO_DS13%16  +0X30);
   
   glcd_command(glcd_text_mode);
   glcd_command (glcd_addr_line3 + 3);
   glcd_data (PHUT_DS13/16 +0X30);
   glcd_data (PHUT_DS13%16 +0X30);
    
   glcd_command(glcd_text_mode);
   glcd_command (glcd_addr_line3 + 6);
   glcd_data (GIAY_DS13/16 +0X30);
   glcd_data (GIAY_DS13%16 +0X30);
    
    
    
    
    
   }
}

