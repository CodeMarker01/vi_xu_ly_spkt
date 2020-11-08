
#include <tv_pickit2_shift_1.c>                                               
#include <tv_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_32led_don.c>
#define UP BT0
#define DW BT1
#define CLR BT2

unsigned INT8 mp;                                                   
//!unsigned INT8 y=0;
UNSIGNED INT8 T0,T0_TAM;
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

UNSIGNED INT8 T0;
UNSIGNED INT8 DONVI, CHUC, TRAM;
VOID GIAI_MA_HIEN_THI (UNSIGNED INT16 TAM)
{
   DONVI=MA7DOAN[TAM%10];
   CHUC=MA7DOAN[TAM/10%10];
   TRAM=MA7DOAN[TAM/100];
   IF (TRAM==0XC0) // led 7 doan = 0
   {
      TRAM=0XFF;
      IF (CHUC==0XC0) CHUC=0XFF;
   }
    XUAT_4LED_7DOAN_4SO(CHUC, DONVI, 0xff, ttct);
}

void main()
{
   SET_UP_PORT_IC_CHOT ();
   set_tris_b (0x3c);
   // ! xuat_32led_don_4byte (0, 0, 0, 0) ;
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1|T0_8_BIT);
   SET_TIMER0(0);
   T0 = 0;
   GIAI_MA_HIEN_THI(T0);

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
      
      XUAT_4LED_7DOAN_4SO(CHUC, DONVI, 0xff, ttct);
   }
}

