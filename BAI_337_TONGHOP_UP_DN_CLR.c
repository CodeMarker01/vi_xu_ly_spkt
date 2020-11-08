
#include <tv_pickit2_shift_1.c>                                               
#include <tv_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_32led_don.c>
#define UP BT0
#define DW BT1
#define CLR BT2

unsigned INT8 mp;                                                   
//!unsigned INT8 y=0;
unsigned INT8 ttct=1;

int CDNN(INT1 pin)
{
   IF (!input (pin) )
   {
      delay_ms (20);
      if (!input (pin) ) WHILE (!input (pin) );
      RETURN 1;
   }

   RETURN 0;
}

void main()
{
   SET_UP_PORT_IC_CHOT ();
   set_tris_b (0x3c);
   // ! xuat_32led_don_4byte (0, 0, 0, 0) ;

   WHILE (1)
   {
      xuat_4led_7doan_1so (ma7doan[ttct]);
      IF (ttct == 1) sang_tat_32led (10, 0);
      IF (ttct == 2) sang_tat_dan_pst_32led (10, 0);
      IF (ttct == 3) sang_tat_dan_tsp_32led (10, 0);
      IF (ttct == 4) sang_tat_dan_ngoai_vao_32led (10, 0);
      IF (ttct == 5) sang_tat_dan_trong_ra_32led (10, 0);
      IF (ttct == 6) sang_don_pst_32led (10, 0);
      IF (ttct == 7) sang_don_tsp_32led (10, 0);
      IF (ttct > 7) ttct = 7;
      IF (ttct < 1) ttct = 1;
      
      IF (CDNN (UP) ) ttct++;
      IF (CDNN (DW)) ttct--;

      IF (CDNN (CLR))
      {
         ttct = 1;
         reset_toan_bo_bien();
      }
   }
}

