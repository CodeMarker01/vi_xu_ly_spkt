#include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_DS13B07_I2C.c>


void HT_DS1307 ( )
{     
    LCD_COMMAND (0x8C);   
      LCD_DATA(GIO_DS13/16  +0X30);    LCD_DATA(GIO_DS13%16  +0X30);
      LCD_DATA(' ');
      LCD_DATA(PHUT_DS13/16 +0X30);    LCD_DATA(PHUT_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(GIAY_DS13/16 +0X30);    LCD_DATA(GIAY_DS13%16 +0X30);
      LCD_COMMAND (0xC6);
      LCD_DATA("THU ");
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
   lcd_command (lcd_addr_line1) ;
   lcd_data ("clock:") ;
   doc_thoi_gian_tu_realtime () ;

   IF (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai () ;
      NAP_THOI_GIAN_HTAI_VAO_DS13B07 () ;
   }

//!   thiet_lap_thoi_gian_hien_tai () ;
//!   nap_thoi_gian_htai_vao_ds1307 () ;
   doc_thoi_gian_tu_realtime();
   giaytam = giay_ds13;

   WHILE (true)
   {
      doc_thoi_gian_tu_realtime () ;

      IF (giaytam != giay_ds13)
      {
         giaytam = giay_ds13;
         HT_DS1307();
      }

      delay_ms (500) ;
   }
}

