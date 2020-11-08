#include <tv_pickit2_shift_1.c>
#include<tv_pickit2_shift_key4x4_138.c>
unsigned char LED7[4]={0x7f,0x7f,0x7f,0x7f};
signed int8 mp;

void DICH_LED7()
{

//! for(k=3; k>0; k--)
//! {
//!  LED7[k]=LED7[k-1];
//!}
//!LED7[0]=MA7DOAN[MP];
 LED7[3]=LED7[2];
 LED7[2]=LED7[1];
 LED7[1]=LED7[0];
 LED7[0]=MA7DOAN[MP];
}

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_4led_7doan_4so(0x7F, 0x7F, 0x7F, 0x7F);
   WHILE(true)
   {
      mp = key_4x4_DW();
      if(MP!=0xff)
      {
        DICH_LED7();
        //LED7[0]=MA7DOAN[MP];
        xuat_4led_7doan_4so(LED7[3], LED7[2], LED7[1], LED7[0]);
        DELAY_MS(500);
      }
   }
}

