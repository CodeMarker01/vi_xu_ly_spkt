#INCLUDE <TV_PICKIT2_SHIFT_1.C> 
#INCLUDE <TV_PICKIT2_SHIFT_LCD.C>
#INCLUDE <TV_PICKIT2_SHIFT_GLCD128X64.C>
UNSIGNED INT8 T0,CHU_S,CHU_P,HT=0; 
UNSIGNED INT8 DV, CH; 
INT1 TT=1,TT_1=0;


VOID GIAI_MA_HIEN_THI (UNSIGNED INT8 TAM) 
{
   CHU_S=0X92;
   CHU_P=0X8C;
   CH = TAM/10;
   DV = TAM%10;
}

VOID HIEN_THI()
{ 
   IF (HT==0) 
   {
      XUAT_4LED_7DOAN_4SO(CHU_S,CHU_P,MA7DOAN[CH],MA7DOAN[DV]);
      LED_7DQ[0]= MA7DOAN[DV];
      LED_7DQ[1]= MA7DOAN[CH];
      LED_7DQ[3]= 0X8C;
      LED_7DQ[4]= 0X92;

      
   }
   ELSE  
   {
      XUAT_4LED_7DOAN_4SO(MA7DOAN[CH],MA7DOAN[DV],CHU_S,CHU_P);
      LED_7DQ[3]= MA7DOAN[DV];
      LED_7DQ[4]= MA7DOAN[CH];
      LED_7DQ[0]= 0X8C;
      LED_7DQ[1]= 0X92;
   }
}


VOID START_PAUSE()
{
   IF(INPUT(BT0)==0)
   {  
      DELAY_MS(20);
      IF(INPUT(BT0)==0)
      {
         TT=~TT;
         IF(TT==1) SETUP_TIMER_0 (T0_EXT_L_TO_H | T0_DIV_1|T0_8_BIT);
         ELSE SETUP_TIMER_0 (T0_OFF);
         WHILE(INPUT(BT0)==0);
      }      
   }
}

VOID DAO()
{
   IF(INPUT(BT1)==0)
   {  
      DELAY_MS(20);
      IF(INPUT(BT1)==0)
      {
         TT_1=~TT_1;  
         IF(TT_1==0) SET_TIMER0(T0);
         ELSE SET_TIMER0(99-T0);
         WHILE(INPUT(BT1)==0);
      }      
   }
}

VOID HT_4LED()
{
   IF(INPUT(BT2)==0)
   {  
      DELAY_MS(20);
      IF(INPUT(BT2)==0)
      {
         HT=~HT;         
         WHILE(INPUT(BT2)==0);
      }      
   }
}

VOID MAIN() 
{
   SET_UP_PORT_IC_CHOT();
   SETUP_TIMER_0 (T0_EXT_L_TO_H | T0_DIV_1|T0_8_BIT);
   SET_TIMER0(0); 
   SETUP_GLCD(GLCD_TEXT_MODE);
   WHILE(TRUE)
   {
      
      IF(TT_1==0) 
      {
         T0=GET_TIMER0();         
         IF (T0>=100) SET_TIMER0(1);
         
      }
      ELSE 
      {        
         T0=99-GET_TIMER0();
         IF (T0<=0) SET_TIMER0(0);
      }
      GIAI_MA_HIEN_THI (T0);
      HIEN_THI_8LED_7DOAN_QUET();
      HIEN_THI();
      DAO();
      START_PAUSE();
      HT_4LED();
   }     
}

