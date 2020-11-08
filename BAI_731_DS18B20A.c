#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
unsigned int8 chuc,dv,tp_chuc,tp_dv;
void main()
{
   set_up_port_ic_chot();
   khoi_tao_ds18b20 () ;
   ds18a_tam = 0;
   xuat_4led_7doan_giaima_xoa_so0 (0) ;

   WHILE (true)
   {
      IF (touch_present ()) {doc_giatri_ds18b20 (); }
      
      IF (ds18al != ds18a_tam)
      {
         ds18a_tam = ds18al;
         chuc=    ma7doan[nguyen/10];
         dv=      ma7doan[nguyen%10]&0x7F;
         tp_chuc= ma7doan[tp/10];
         tp_dv=   ma7doan[tp%10];
         
         xuat_4led_7doan_4so(chuc,dv,tp_chuc,tp_dv);
        
      }
   }
}

