
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>

UNSIGNED INT8 LED[4]={0,0,0,5};
UNSIGNED INT8 SP;
UNSIGNED INT16 NGUYEN,LE;

VOID HIEN_THI_8LED_7DOAN_QUET_ALL1()
{     
      FOR(TT8LED=0;TT8LED<8;TT8LED++)         
         {           
            XUAT_8LED_7DOAN_QUET_2(TT8LED, LED_7DQ[TT8LED]);
            DELAY_US(900);
            XUAT_8LED_7DOAN_QUET_TAT_LED();           
         }
}

#INT_timer3

void NGAT_TIMER3 ()
{
   hien_thi_8led_7doan_quet_all1 ();
   set_timer3 (-6000);
}

VOID HIENTHI7DOAN()
{
   

   led_7dq[7] = MA7DOAN [NGUYEN / 10];
   led_7dq[6] = MA7DOAN [NGUYEN % 10]&0X7F;
   led_7dq[5] = MA7DOAN [LE / 100];
   led_7dq[4] = MA7DOAN [LE / 10 % 10];
   led_7dq[3] = MA7DOAN [LE % 10];
   led_7dq[2] = 0x9c;
   led_7dq[1] = 0xc6;
   led_7dq[0] = 0xBf;
}

VOID HIENTHI4LED()
{
   
   LED[0] = SP % 10;
   LED[1] = SP / 10;
   XUAT_4LED_7DOAN_4SO (0x92,0x8c, MA7DOAN[LED[1]], MA7DOAN[LED[0]]);
}

VOID  KHOI_TAO_DS18B20_11_BIT()
{
   
   TOUCH_PRESENT ();
   TOUCH_WRITE_BYTE (SKIP_ROM);
   TOUCH_WRITE_BYTE (WRITE_SCRATCHPAD);
   TOUCH_WRITE_BYTE (0x0); // ghi 2 byte rong
   TOUCH_WRITE_BYTE (0x0); //
   TOUCH_WRITE_BYTE (0x5F); //Cau hinh DO phan giai 11 bit
   TOUCH_PRESENT ();
   TOUCH_WRITE_BYTE (SKIP_ROM);
   TOUCH_WRITE_BYTE (COPY_SCRATCHPAD);
}

// !VOID  KHOI_TAO_DS18B20_10_BIT()
// !{
// !   
// !   TOUCH_PRESENT ();
// !   TOUCH_WRITE_BYTE (SKIP_ROM);
// !   TOUCH_WRITE_BYTE (WRITE_SCRATCHPAD);
// !   TOUCH_WRITE_BYTE (0x0); // ghi 2 byte rong
// !   TOUCH_WRITE_BYTE (0x0); //
// !   TOUCH_WRITE_BYTE (0X3F); //Cau hinh DO phan giai 11 bit
// !   TOUCH_PRESENT ();
// !   TOUCH_WRITE_BYTE (SKIP_ROM);
// !   TOUCH_WRITE_BYTE (COPY_SCRATCHPAD);
// !}
// !VOID  KHOI_TAO_DS18B20_9_BIT()
// !{
// !   
// !   TOUCH_PRESENT ();
// !   TOUCH_WRITE_BYTE (SKIP_ROM);
// !   TOUCH_WRITE_BYTE (WRITE_SCRATCHPAD);
// !   TOUCH_WRITE_BYTE (0x0); // ghi 2 byte rong
// !   TOUCH_WRITE_BYTE (0x0); //
// !   TOUCH_WRITE_BYTE (0X1F); //Cau hinh DO phan giai 11 bit
// !   TOUCH_PRESENT ();
// !   TOUCH_WRITE_BYTE (SKIP_ROM);
// !   TOUCH_WRITE_BYTE (COPY_SCRATCHPAD);
// !}
// !VOID SL11BIT ()
// !{
// !   KHOI_TAO_DS18B20_11_BIT ();
// !   IF (touch_present () ) //kt coi co ko
// !      {
// !         
// !         doc_giatri_ds18b20 ();
// !         NGUYEN = ds18a>>4; // sua thanh nguyen
// !         LE = (BIT_TEST (ds18a, 3) * 500 + BIT_TEST (ds18a, 2) * 250 + BIT_TEST (ds18a, 1) * 125);
// !         ds18a = ds18a&0x0ff;
// !         HIENTHI7DOAN ();
// !         HIENTHI4LED();
// !}
// !VOID SL10BIT ()
// !{
// !   KHOI_TAO_DS18B20_10_BIT ();
// !   IF (touch_present () ) //kt coi co ko
// !      {
// !         
// !         doc_giatri_ds18b20 ();
// !         NGUYEN = ds18a>>4; // sua thanh nguyen
// !         LE = (BIT_TEST (ds18a, 2) * 50 + BIT_TEST (ds18a, 1) * 25 );
// !         ds18a = ds18a&0x0ff;
// !         
// !         led_7dq[7] = MA7DOAN [NGUYEN / 10];
// !   led_7dq[6] = MA7DOAN [NGUYEN % 10]&0X7F;
// !   led_7dq[5] = MA7DOAN [LE / 10];
// !   led_7dq[4] = MA7DOAN [LE % 10];
// !   led_7dq[3] = 0XFF;
// !   led_7dq[2] = 0x9c;
// !   led_7dq[1] = 0xc6;
// !   led_7dq[0] = 0xff;
// !}
// !VOID SL9BIT ()
// !{
// !   KHOI_TAO_DS18B20_9_BIT ();
// !   IF (touch_present () ) //kt coi co ko
// !      {
// !         
// !         doc_giatri_ds18b20 ();
// !         NGUYEN = ds18a>>4; // sua thanh nguyen
// !         LE = (BIT_TEST (ds18a, 1) * 5);
// !         ds18a = ds18a&0x0ff;
// !         
// !         led_7dq[7] = MA7DOAN [NGUYEN / 10];
// !   led_7dq[6] = MA7DOAN [NGUYEN % 10]&0X7F;
// !   led_7dq[5] = MA7DOAN [LE / 10];
// !   led_7dq[4] = 0XFF;
// !   led_7dq[3] = 0XFF;
// !   led_7dq[2] = 0x9c;
// !   led_7dq[1] = 0xc6;
// !   led_7dq[0] = 0xff;
// !}

// !
void main()
{
   KHOI_TAO_DS18B20_11_BIT ();
   DS18A_TAM = 0;
   SP = 5;
   HIENTHI4LED();
   set_up_port_ic_chot ();
   SET_TRIS_B (0X3c);
   setup_timer_3 (T3_internal|T3_div_by_8);
   set_timer3 (-6000);
   enable_interrupts (global);
   enable_interrupts (INT_timer3);   
   SETUP_TIMER_0 (T0_OFF);

   SET_TIMER0 (5);
   HIENTHI7DOAN();
   WHILE (true)
   {  
//!
          
      IF (touch_present () ) //kt coi co ko
      {
         
         doc_giatri_ds18b20 ();
         NGUYEN = ds18a>>4; // sua thanh nguyen
         LE = (BIT_TEST (ds18a, 3) * 500 + BIT_TEST (ds18a, 2) * 250 + BIT_TEST (ds18a, 1) * 125);
         ds18a = ds18a&0x0ff;
         hien_thi_8led_7doan_quet_all1 ();
         HIENTHI7DOAN ();
         HIENTHI4LED();
         
      }
         SETUP_TIMER_0 (T0_EXT_L_TO_H |T0_DIV_1|T0_8_BIT);
         SP = GET_TIMER0 ();
         HIENTHI4LED();
         HIENTHI7DOAN ();
     IF ((SP!=0)&(SP==16))
           
     {   
          SP=6;
          SET_TIMER0 (6);
          SETUP_TIMER_0 (T0_EXT_L_TO_H |T0_DIV_1|T0_8_BIT);
          SP = GET_TIMER0 ();
          HIENTHI4LED();
     }

//!       
//!     SWITCH (TTCT)
//!         {
//!            CASE 11: SL11BIT ();
//!            BREAK;
//!            CASE 10: SL10BIT ();
//!            BREAK;
//!            CASE 9: SL9BIT ();
//!            BREAK;           
//!         }
   }
    hien_thi_8led_7doan_quet_all1 ();
         HIENTHI7DOAN ();
         HIENTHI4LED();
}
