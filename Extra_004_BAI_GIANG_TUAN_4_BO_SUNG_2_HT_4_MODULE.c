#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_glcd128x64.c>
unsigned int8 i;
signed int8 t0=0, SP=0;
unsigned int8 S, P, DV, CH, DV_lcd, CH_lcd, DV_lon, CH_lon;
unsigned int1 mode, TT_HT, TT_DEM;

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1);
   for (i=0;i<6;i++)
   {
      if (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void giaima_led_7doan()
{
   S=0x92;
   P=0x8C;
   DV=ma7doan[SP%10];
   CH=ma7doan[SP/10%10];
   if (CH==0xC0)
   {
      CH=0xFF;
   }
}

void giaima_lcd_glcd()
{
   DV_lcd=SP%10+(0x30);
   CH_lcd=SP/10+(0x30);
   if (CH_lcd==0x30)
   {
      CH_lcd=0x20;
   }
}

void giaima_solon_lcd()
{
   DV_lon=SP%10;
   CH_lon=SP/10;
   if (CH_lon==0) CH_lon=12;
}

void start_stop()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         mode=~mode;
         while(!input(BT0));
      }
   }
}

void inv_ht()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         TT_HT=~TT_HT;
         while(!input(BT1));
      }
   }
}

void inv_tt()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         TT_DEM=~TT_DEM;
         while(!input(BT2));
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   setup_lcd();
   setup_glcd(glcd_text_mode);
   setup_timer_0(t0_ext_l_to_h|t0_div_1|t0_8_bit);
   set_timer0(0);
   mode=0; TT_HT=0; TT_DEM=0;
   lcd_command(0x40);
   for(i=0;i<64;i++)
   {
      lcd_data(lcd_ma_8doan[i]);
   }
   while(TRUE)
   {
      giaima_led_7doan();
      giaima_lcd_glcd();
      giaima_solon_lcd();
      if (mode==0)
      {
         setup_timer_0(t0_off);
      }
      else
      {
         setup_timer_0(t0_ext_l_to_h|t0_div_1|t0_8_bit); 
         if (TT_DEM==0)
         {
            t0=get_timer0();
            if (t0==1)
            {
               set_timer0(0);
               SP++;
            }
            if (SP>99) SP=0;
         }
         else
         {
            t0=get_timer0();
            if (t0==1)
            {
               set_timer0(0);
               SP--;
            }
            if (SP<=0) SP=99;
         }
         
      }
      if (TT_HT==0)
      {
         xuat_4led_7doan_4so(S,P,CH,DV);
         lcd_goto_xy(0,0);
         lcd_data("S");
         lcd_data("P");
         lcd_data(CH_lcd);
         lcd_data(DV_lcd);
         lcd_hienthi_so_z_toado_xy(10,2,0);
         lcd_hienthi_so_z_toado_xy(11,2,3);
         lcd_hienthi_so_z_toado_xy(CH_lon,2,6);
         lcd_hienthi_so_z_toado_xy(DV_lon,2,9);
         glcd_command(glcd_addr_line1);
         glcd_data("S");
         glcd_data("P");
         glcd_data(CH_lcd);
         glcd_data(DV_lcd);
         led_7dq[0]=DV;
         led_7dq[1]=CH;
         led_7dq[2]=0x8C;
         led_7dq[3]=0x92;
         hien_thi_8led_7doan_quet();
      }
      else
      {
         xuat_4led_7doan_4so(CH,DV,S,P);
         lcd_goto_xy(0,0);
         lcd_data(CH_lcd);
         lcd_data(DV_lcd);
         lcd_data('S');
         lcd_data('P');
         lcd_hienthi_so_z_toado_xy(CH_lon,2,0);
         lcd_hienthi_so_z_toado_xy(DV_lon,2,3);
         lcd_hienthi_so_z_toado_xy(10,2,6);
         lcd_hienthi_so_z_toado_xy(11,2,9);
         glcd_command(glcd_addr_line1);
         glcd_data(CH_lcd);
         glcd_data(DV_lcd);
         glcd_data("S");
         glcd_data("P");    
         led_7dq[0]=0x8C;
         led_7dq[1]=0x92;
         led_7dq[2]=DV;
         led_7dq[3]=CH;
         hien_thi_8led_7doan_quet();
      }
      start_stop();
      inv_ht();
      inv_tt();
   }
}
