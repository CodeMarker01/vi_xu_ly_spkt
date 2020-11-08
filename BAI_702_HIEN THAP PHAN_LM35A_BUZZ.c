#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_glcd128x64.c>
#include <tv_pickit2_shift_lcd.c>
#define nd_tren 40

unsigned INT8 j, solan=100;
float lm35a;
int1 ttqn=0;
int16 KQ_HT;
int16 TP_CH,TP_DV,DV,CH;


signed INT8 i;

void lcd_hienthi_so_z_toado_xy(SIGNED int8 lcd_so, x1, y1)
{
   lcd_GOTO_xy(x1,y1);
   FOR (i=0;i<6;i++)
   {
      IF (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}


void so_sanh_dk_buzzer()
{
   IF ((lm35a>nd_tren)&&(ttqn==0))
   {
      ttqn = 1;
//!      buzzer_on();
      xuat_32led_don_4byte(0xFF,0xFF,0xFF,0xFF);
   }

   else IF ((lm35a<nd_tren)&&(ttqn==1))
   {
      ttqn = 0;
//!      buzzer_off();
      xuat_32led_don_4byte(0,0,0,0);
   }
}
void giaima_7doan()
{

TP_DV = MA7DOAN[KQ_HT%10]; 
TP_CH = MA7DOAN[KQ_HT/10%10];
DV = MA7DOAN[KQ_HT/100%10] & 0X7F;
CH = MA7DOAN[KQ_HT/1000];
}

void hienthi_ledquet()
{
  FOR (i=0;i<105;i++)
   {
      xuat_8led_7doan_quet_2(0,ma7doan [KQ_HT%10]);
      delay_ms(5);
      xuat_8led_7doan_quet_tat_led();
      xuat_8led_7doan_quet_2(1,ma7doan [KQ_HT/10%10]);
      delay_ms(5);
      xuat_8led_7doan_quet_tat_led();
      xuat_8led_7doan_quet_2(2,ma7doan [KQ_HT/100%10]& 0X7F);
      delay_ms(5);
      xuat_8led_7doan_quet_tat_led();
      xuat_8led_7doan_quet_2(3,ma7doan [KQ_HT/1000]);
      delay_ms(5);
      xuat_8led_7doan_quet_tat_led();
   }
}

VOID GIAI_MA_GAN_CHO_8LED_QUET()
{
   LED_7DQ[0]=MA7DOAN [KQ_HT%10];
   LED_7DQ[1]=MA7DOAN [KQ_HT/10%10];
   LED_7DQ[2] =MA7DOAN [KQ_HT/100%10] & 0x7F; 
   LED_7DQ[3] = MA7DOAN [KQ_HT/1000];
   // LED_7DQ [2...7] = 0xFF
}



void main()
{
   set_up_port_ic_chot ();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(an0|vss_vdd );
   set_adc_channel(0);
   ttqn = 0;
   setup_glcd(glcd_text_mode);
   setup_lcd();
   lcd_command(0x40);
   FOR (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   GIAI_MA_GAN_CHO_8LED_QUET();
   WHILE(true)
   {
      lm35a = 0;
      FOR (j=0; j<solan; j++)
      {
         lm35a = lm35a + read_adc ();
//!         delay_ms(1);
      } 
      lm35a = lm35a /2.046;
      lm35a = lm35a /solan;
      KQ_HT= (int16) (LM35A*100); 
      
      giaima_7doan();
      xuat_4led_7doan_4so(CH,DV,TP_CH,TP_DV);//4 LED 7 DOAN
      
      so_sanh_dk_buzzer ();
      glcd_command(glcd_addr_line1); //GLCD
      printf(GLCD_DATA, "ND = %3.2f", LM35A);//GLCD
      lcd_command(lcd_addr_line1);//LCD
      printf(LCD_DATA, "ND = %3.2f", LM35A);//LCD
      
      lcd_hienthi_so_z_toado_xy(KQ_HT/1000,2,3);
      lcd_hienthi_so_z_toado_xy(KQ_HT/100%10,2,6);
      lcd_hienthi_so_z_toado_xy(12,2,9);
      lcd_hienthi_so_z_toado_xy(KQ_HT/10%10,2,12);
      lcd_hienthi_so_z_toado_xy(KQ_HT%10,2,15);
      
      hienthi_ledquet();//LED QUET
      GIAI_MA_GAN_CHO_8LED_QUET();
//!      HIEN_THI_8LED_7DOAN_QUET ();
//!DELAY_QUET_8LED(2000);
      
   }
   }

