#include <tv_pickit2_shift_1.c>
//!#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>
#include <TV_PICKIT2_SHIFT_DS13B07_I2C.c>
#include <tv_pickit2_shift_ds18b20.c>
#include <tv_pickit2_shift_glcd128x64.c>
#include <graphics.c>

UNSIGNED INT1 TT_HINH;

//LCD CHU TO
signed INT8 i;// LCD TO
unsigned INT8 dv_giay,ch_giay,ch_phut,dv_phut,dv_gio,ch_gio;//DS1307
unsigned int8 thu;
int16 TP_NG,TP_CH,TP_DV,DV,CH;//DS18b20
UNSIGNED INT8 MP;

// HIEN THI CHU C
CONST UNSIGNED CHAR LCD_CHU_C[1][6] =
{
   
   7, 1, 1, 7, 3, 3, 
};

// HIEN THI CHU n
CONST UNSIGNED CHAR LCD_CHU_n[1][6] =
{
   
   32,32,32,7,1,7, 
};

// HAM HIEN THI CHU C
VOID LCD_HIENTHI_CHU_C_TOADO_XY(SIGNED INT8 LCD_SO, X1, Y1)
{
   LCD_GOTO_XY (X1, Y1) ;
   FOR (I = 0; I < 6; I++)
   {
      IF (I == 3) LCD_GOTO_XY (X1 + 1, Y1);
      LCD_DATA (LCD_CHU_C[LCD_SO][I]);
   }
}

// HAM HIEN THI CHU n
VOID LCD_HIENTHI_CHU_n_TOADO_XY(SIGNED INT8 LCD_SO, X1, Y1)
{
   LCD_GOTO_XY (X1, Y1) ;
   FOR (I = 0; I < 6; I++)
   {
      IF (I == 3) LCD_GOTO_XY (X1 + 1, Y1);
      LCD_DATA (LCD_CHU_n[LCD_SO][I]);
   }
}

void lcd_hienthi_so_z_toado_xy(SIGNED int8 lcd_so, x1, y1)//LCD TO
{
   lcd_GOTO_xy(x1,y1);
   FOR (i=0;i<6;i++)
   {
      IF (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void giaima_hienthi_to()//LCD TO
{
ch_giay=GIAY_DS13/16; 
dv_giay=GIAY_DS13%16; 

ch_phut=PHUT_DS13/16 ;
dv_phut=PHUT_DS13%16 ;

ch_gio=GIO_DS13/16  ;
dv_gio=GIO_DS13%16 ;

thu = THU_DS13%16;

}
void HT_DS1307_to( )//LCD TO
{     
      lcd_hienthi_so_z_toado_xy(dv_giay,0,0);
      lcd_hienthi_so_z_toado_xy(ch_giay,2,0);
      
      if (thu!=1)
      {
         lcd_hienthi_so_z_toado_xy(thu,2,17);
      }
      else
      {
         LCD_HIENTHI_CHU_C_TOADO_XY(0,2,14);
         LCD_HIENTHI_CHU_n_TOADO_XY(0,2,17 );
      }
   
}

// END LCD CHU TO

//DS18B20
void giaima_lcd_ds18b20()
{
   TP_DV = tp%10 +0x30;
   TP_CH = tp/10%10+0x30;
   TP_NG = tp/100 +0x30;
   DV = nguyen%10+0x30;
   CH = nguyen/10%10+0x30;
}

void hienthi_glcd()
{

   glcd_command(glcd_text_mode);// NGUYEN DS18B20
   glcd_command (glcd_addr_line2+3);
   glcd_data (CH );
   glcd_data (DV );
    
   glcd_command(glcd_text_mode);//TP DS18B20
   glcd_command (glcd_addr_line4 + 3);
   glcd_data (TP_NG );
   glcd_data (TP_CH );
   glcd_data (TP_DV );
   
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
   setup_lcd () ;// LCD
   
   doc_thoi_gian_tu_realtime () ;// DS1307
   
   //ds18
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
   
   lcd_command(0x40);// LCD TO
   FOR (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }//LCD TO
   
   IF (ma_ds13 != ma_ds)//DS1307
   {
      thiet_lap_thoi_gian_hien_tai () ;
      NAP_THOI_GIAN_HTAI_VAO_DS13B07 () ;
   }

   doc_thoi_gian_tu_realtime();//DS1307
   giaytam = giay_ds13;//DS1307

   setup_glcd(glcd_text_mode);
   setup_glcd(glcd_graphic_mode);
   glcd_mau_nen(0);
   glcd_circle(63, 19, 15, 0, 1);
   glcd_rect (42, 42, 84, 63, 0, 1);
   gdram_vdk_to_gdram_glcd_all();

   WHILE (true)
   {
      doc_thoi_gian_tu_realtime () ; // DS1307

      IF (giaytam != giay_ds13)//DS1307
      {
         giaytam = giay_ds13;
         
      }
      
       IF (touch_present () ){doc_giatri_ds18b20 (); }
      IF (ds18al != ds18a_tam)
      {
         ds18a_tam = ds18al;
      }
      
       giaima_hienthi_to();// LCD TO
       HT_DS1307_to( );// LCD TO
       giaima_lcd_ds18b20();
       hienthi_glcd();
    
   }
}


