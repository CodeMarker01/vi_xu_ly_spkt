//LCD TO DS1307
#include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_DS13B07_I2C.c> //#include <tv_pickit2_shift_lcd.c> da co thu vien 

unsigned INT16 k;
unsigned CHAR giatri_mod;
unsigned INT8 dv_giay,ch_giay,ch_phut,dv_phut,dv_gio,ch_gio;
unsigned INT8 dv_ngay,ch_ngay,ch_thang,dv_thang,dv_nam,ch_nam;
char thu;
signed INT8 i;
char thu1,thu2;
int1 tt;


void nhap_nhay_nho()
{
   SWITCH (giatri_mod)
   {
      CASE 1: ch_gio = '_'; dv_gio = '_'; 
      BREAK;
      CASE 2: ch_phut='_';dv_phut='_'; 
      BREAK;
      CASE 3: ch_giay='_';dv_giay='_'; 
      BREAK;
      CASE 4: ch_ngay='_';dv_ngay='_';
      BREAK;
      CASE 5: ch_thang='_';dv_thang='_'; 
      BREAK;
      CASE 6: ch_nam='_';dv_nam='_'; 
      BREAK;
      CASE 7:  thu1='_';thu2='_';
      BREAK;
      
      DEFAULT: break;
   }
}
void giaima_hienthi_nho()
{
ch_giay=GIAY_DS13/16 +0X30;
dv_giay=GIAY_DS13%16 +0X30;

ch_phut=PHUT_DS13/16 +0X30;
dv_phut=PHUT_DS13%16 +0X30;

ch_gio=GIO_DS13/16  +0X30;
dv_gio=GIO_DS13%16  +0X30;

ch_ngay=NGAY_DS13/16 +0X30;
dv_ngay=NGAY_DS13%16 +0X30;

ch_thang=THANG_DS13/16 +0X30;
dv_thang=THANG_DS13%16 +0X30;

ch_nam=NAM_DS13/16 +0X30;
dv_nam=NAM_DS13%16 +0X30;

if (THU_DS13!=1) 
   {
      thu1=THU_DS13 +0X30;
      thu2=0x20;
   }
      ELSE 
      
      {
      thu1='C';
      thu2='N';
      }
      
}

void HT_DS1307_nho ( )
{     
      
      LCD_COMMAND (0x8C);   
      LCD_DATA(ch_gio);    LCD_DATA(dv_gio);
      LCD_DATA(':');
      LCD_DATA(ch_phut);    LCD_DATA(dv_phut);
      LCD_DATA(':');
      LCD_DATA(ch_giay);    LCD_DATA(dv_giay);
      LCD_COMMAND (0xC5);
      LCD_DATA("THU ");
      LCD_DATA(thu1);
      LCD_DATA(thu2);
      LCD_COMMAND (0xCC);  
      LCD_DATA(ch_ngay);    LCD_DATA(dv_ngay);
      LCD_DATA('/');
      LCD_DATA(ch_thang);   LCD_DATA(dv_thang);
      LCD_DATA('/');
      LCD_DATA(ch_nam);     LCD_DATA(dv_nam);  
}

// PHÍM NHAN CHUYEN HIEN THI
void phim_nhan()
{

   IF (!input (BT2))
   {
      delay_ms (20) ;
      {
         IF (!input (BT2))
         {
           tt=!tt;
           lcd_command(lcd_clear_display);
            WHILE ( ! input (BT2)) ;
         }
      }
   }
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

ch_ngay=NGAY_DS13/16+0x30 ;
dv_ngay=NGAY_DS13%16+0x30 ;

ch_thang=THANG_DS13/16+0x30;
dv_thang=THANG_DS13%16+0x30 ;

ch_nam=NAM_DS13/16+0x30 ;
dv_nam=NAM_DS13%16+0x30 ;

if (THU_DS13!=1) 
   {
      thu=THU_DS13 +0X30;
      LCD_DATA(0X20);
   }
      ELSE thu="CN";
      

      
      
}
void HT_DS1307_to( )
{     
      LCD_COMMAND (0x8C);   
      lcd_hienthi_so_z_toado_xy(ch_gio,0,0);lcd_hienthi_so_z_toado_xy(dv_gio,0,3);
     // LCD_DATA(':');
      lcd_hienthi_so_z_toado_xy(ch_phut,0,7);lcd_hienthi_so_z_toado_xy(dv_phut,0,10);
      //LCD_DATA(':');
      lcd_hienthi_so_z_toado_xy(ch_giay,0,14);lcd_hienthi_so_z_toado_xy(dv_giay,0,17);
      LCD_COMMAND (0xD7);
      LCD_DATA("THU ");
      LCD_DATA(thu);
      LCD_COMMAND (0xE0);  
      LCD_DATA(ch_ngay);    LCD_DATA(dv_ngay);
      LCD_DATA('/');
      LCD_DATA(ch_thang);   LCD_DATA(dv_thang);
      LCD_DATA('/');
      LCD_DATA(ch_nam);     LCD_DATA(dv_nam);
}


void nhap_nhay_to()
{
   SWITCH (giatri_mod)
   {
      CASE 1: ch_gio = 16; dv_gio = 16; 
      BREAK;
      CASE 2: ch_phut= 16;dv_phut=16; 
      BREAK;
      CASE 3: ch_giay=16;dv_giay=16; 
      BREAK;
      CASE 4: ch_ngay='_';dv_ngay='_';
      BREAK;
      CASE 5: ch_thang='_';dv_thang='_'; 
      BREAK;
      CASE 6: ch_nam='_';dv_nam='_'; 
      BREAK;
      CASE 7: thu="___";
      BREAK;
      DEFAULT: break;
   }
}

void hien_thi_gia_tri_mod ( )
{
   lcd_command(0xD4);
   lcd_data (giatri_mod + 0x30) ;
}

void phim_mod()
{
   IF (!input (mod))
   {
      delay_ms (20) ;
      {
         IF (!input (mod))
         {
            IF (giatri_mod < 7) giatri_mod++;
            ELSE giatri_mod = 0;
            hien_thi_gia_tri_mod ();
            WHILE ( ! input (mod)) ;
         }
      }
   }
}

unsigned int8 hieu_chinh_so_bcd_tang(UNSIGNED int8 x )
{
   UNSIGNED int8 y;
   y = x;
   x = x&0x0f;
   IF (x == 0x0a) y = y + 6;
   RETURN (y) ;
}

unsigned int8 hieu_chinh_so_bcd_giam(UNSIGNED int8 x )
{
   UNSIGNED int8 y;
   y = x;
   x = x&0x0f;
   IF (x == 0x0f) y = y - 6;
   RETURN (y) ;
}

void luu_giai_ma_hien_thi_sau_khi_chinh()
{
   nap_thoi_gian_htai_vao_ds13B07();
   hien_thi_thoi_gian_ds13B07 ();
}

void phim_up()
{
   IF (!input (up))
   {
      delay_ms (20) ;

      IF (!input (up))
      {
         SWITCH (giatri_mod)
         {
            case 3: IF (giay_ds13 == 0x59) giay_ds13 = 0;

            ELSE
            {
               giay_ds13++;
               giay_ds13=hieu_chinh_so_bcd_tang(giay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 2: IF (phut_ds13 == 0x59) phut_ds13 = 0;

            ELSE
            {
               phut_ds13++;
               phut_ds13=hieu_chinh_so_bcd_tang(phut_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 1: IF (gio_ds13 == 0x23) gio_ds13 = 0;

            ELSE
            {
               gio_ds13++;
               gio_ds13 = hieu_chinh_so_bcd_tang (gio_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 4: IF (ngay_ds13 == 0x31) ngay_ds13 = 1;

            ELSE
            {
               ngay_ds13++;
               ngay_ds13 = hieu_chinh_so_bcd_tang (ngay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 5: IF (thang_ds13 == 0x12) thang_ds13 = 1;

            ELSE
            {
               thang_ds13++;
               thang_ds13=hieu_chinh_so_bcd_tang(thang_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 6: IF (nam_ds13 == 0x99) nam_ds13 = 0;
            ELSE
            {
               nam_ds13++;
               nam_ds13 = hieu_chinh_so_bcd_tang (nam_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            
            case 7: 
           
               thu_ds13++;
               if (thu_ds13 == 8) thu_ds13=1; 
               luu_giai_ma_hien_thi_sau_khi_chinh () ;
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
      delay_ms (50) ;

      IF (!input (dw))
      {
         SWITCH (giatri_mod)
         {
            case 3: IF (giay_ds13 == 0) giay_ds13 = 0x59;

            ELSE
            {
               giay_ds13--;
               giay_ds13 = hieu_chinh_so_bcd_giam (giay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 2: IF (phut_ds13 == 0) phut_ds13 = 0x59;

            ELSE
            {
               phut_ds13--;
               phut_ds13=hieu_chinh_so_bcd_giam(phut_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 1: IF (gio_ds13 == 0) gio_ds13 = 0x23;

            ELSE
            {
               gio_ds13--;
               gio_ds13 = hieu_chinh_so_bcd_giam (gio_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 4: IF (ngay_ds13 == 0) ngay_ds13 = 0x31;

            ELSE
            {
               ngay_ds13--;
               ngay_ds13 = hieu_chinh_so_bcd_giam (ngay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 5: IF (thang_ds13 == 1) thang_ds13 = 0x12;

            ELSE
            {
               thang_ds13--;
               thang_ds13 = hieu_chinh_so_bcd_giam (thang_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            case 6: IF (nam_ds13 == 0) nam_ds13 = 0x99;

            ELSE
            {
               nam_ds13--;
               nam_ds13 = hieu_chinh_so_bcd_giam (nam_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            
            case 7: 
            thu_ds13--;
            if (thu_ds13 == 0) thu_ds13=7;
            luu_giai_ma_hien_thi_sau_khi_chinh () ;
            BREAK;
            DEFAULT: break;
         }

         WHILE ( ! input (dw)) ;
      }
   }
}

void delay_mssv(UNSIGNED int8 t)
   {
   for (INT8 i = 0; i < t; i++)
   {
      delay_ms (1) ;
      IF ((input (up) == 0)|| (input (dw) == 0)||(input (mod)  == 0))
      BREAK;
   }
   }

void main()
{
   set_up_port_ic_chot();
   setup_lcd () ;
   doc_thoi_gian_tu_realtime () ;

   IF (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai () ;
      nap_thoi_gian_htai_vao_ds13B07 () ;
   }

   giatri_mod = 0;
   hien_thi_gia_tri_mod ();
   doc_thoi_gian_tu_realtime () ;
   giaytam = giay_ds13;
  
   lcd_command(0x40);
   FOR (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   tt=1;
    giaima_hienthi_to();
         HT_DS1307_to ( );
   WHILE (true)
   {
      doc_thoi_gian_tu_realtime () ;
      phim_nhan();
      IF (giaytam != giay_ds13)
      {
         giaytam = giay_ds13;
         hien_thi_gia_tri_mod ();
         
         if (tt==0)
         {
         giaima_hienthi_nho();
         HT_DS1307_nho ( );
         }
         else 
         {
         giaima_hienthi_to();
         HT_DS1307_to ( );
         }
      }

      FOR (k = 0; k < 10000; k++)
      {
         phim_mod (); phim_up (); phim_dw ();
      }
      
      IF (giatri_mod != 0) 
      {
         if(tt==0)
          {
          nhap_nhay_nho();
          delay_mssv (500) ;
          HT_DS1307_nho( );
          }
          else
        {
          nhap_nhay_to();
          delay_mssv (500) ;
          HT_DS1307_to( );
          }
      } 
   }
}

