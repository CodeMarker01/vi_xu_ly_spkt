
  #INCLUDE <TV_PICKIT2_SHIFT_1.C>

  #INCLUDE <TV_PICKIT2_SHIFT_DS18B20.C>
 
  #INCLUDE <TV_PICKIT2_SHIFT_DS13B07_I2C.C>
  
  #INCLUDE <TV_PICKIT2_SHIFT_GLCD128X64.C>
  
  #INCLUDE <GRAPHICS.C>
  
  
  UNSIGNED INT8  J,SOLAN = 100;
  UNSIGNED INT16 THAPPHAN,DV,CH;
  UNSIGNED INT16 CH_LCD,DV_LCD,TP1_LCD,TP2_LCD;
 
  FLOAT LM35A;
  UNSIGNED INT16 KQ_HT;
  

    VOID GM_LCD ()
   {
      CH_LCD=KQ_HT/1000%10  +0X30;
      DV_LCD=KQ_HT/100%10  +0X30;
      
      TP1_LCD=KQ_HT/10%10  +0X30;
      TP2_LCD=KQ_HT%10  +0X30;
   }

    VOID HT_LCD ()
    {
       LCD_GOTO_XY(0,0) ;
       
       LCD_DATA("LM35:") ;
       LCD_DATA("  ");
       LCD_DATA(CH_LCD) ;
       LCD_DATA(DV_LCD) ;
       LCD_DATA(".");
       LCD_DATA(TP1_LCD);
       LCD_DATA(TP2_LCD);
       
       LCD_GOTO_XY(2,0);
       LCD_DATA("DS18B20:");
       LCD_DATA(" ");
       LCD_DATA(NGUYEN/10 +0X30);
       LCD_DATA(NGUYEN%10 +0X30);
       LCD_DATA(".");
       LCD_DATA(TP/100%10 +0X30);
       LCD_DATA(TP/10%10 + 0X30);
       LCD_DATA(TP%10 +0X30);
    }
    
    VOID GIAI_MA_GAN_CHO_8LED_QUET ()
  {
     LED_7DQ[7] = MA7DOAN [KQ_HT/1000%10];
     LED_7DQ[6] = MA7DOAN [KQ_HT/100%10];
    
     LED_7DQ[5] = 0XBF;
     
     LED_7DQ[4] = MA7DOAN [NGUYEN/10];
     LED_7DQ[3] = MA7DOAN [NGUYEN%10];
     
     LED_7DQ[2] = 0XBF;
     
     LED_7DQ[1] = MA7DOAN [GIAY_DS13/16 ];
     LED_7DQ[0] = MA7DOAN [GIAY_DS13%16];
  }
   VOID HT_DS13B07 ( )
{     LCD_COMMAND (0x8C);   
      LCD_DATA(GIO_DS13/16  +0X30);    LCD_DATA(GIO_DS13%16  +0X30);
      LCD_DATA(' ');
      LCD_DATA(PHUT_DS13/16 +0X30);    LCD_DATA(PHUT_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(GIAY_DS13/16 +0X30);    LCD_DATA(GIAY_DS13%16 +0X30);
      LCD_COMMAND (0x98);
      LCD_DATA("THU");
//!      LCD_DATA(THU_DS13 +0X30);
        IF(THU_DS13!=1) LCD_DATA(THU_DS13 +0X30);
        ELSE LCD_DATA("CN");
      LCD_DATA(' ');
      LCD_DATA(NGAY_DS13/16 +0X30);    LCD_DATA(NGAY_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(THANG_DS13/16 +0X30);   LCD_DATA(THANG_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(NAM_DS13/16 +0X30);     LCD_DATA(NAM_DS13%16 +0X30); 
}

 VOID HT_GLCD()
       {
       GLCD_COMMAND(GLCD_ADDR_LINE1);
       GLCD_DATA(" ");
       
       GLCD_DATA(KQ_HT/1000%10 +0X30);
       GLCD_DATA(KQ_HT/100%10  +0X30);
       GLCD_DATA("       ");
       
       
       
       GLCD_DATA(NGUYEN/10 +0X30);
       GLCD_DATA(NGUYEN%10 +0X30);
       
       GLCD_COMMAND(GLCD_ADDR_LINE4);
       GLCD_DATA(" ");
       GLCD_DATA(KQ_HT/10%10 +0X30);
       GLCD_DATA(KQ_HT%10  +0X30);
       GLCD_DATA("       ");
       
       
       
       GLCD_DATA(TP/100%10 +0X30);
       GLCD_DATA(TP/10 %10  +0X30);
       GLCD_DATA(TP %10  +0X30);
       
       }
    
    VOID DOC_ND_LM35A()
  {
   
    SET_ADC_CHANNEL(0);
    LM35A = 0;
    
    FOR( J=0; J<SOLAN ; J++)
     {
        LM35A = LM35A + READ_ADC();
        
          HIEN_THI_8LED_7DOAN_QUET ();
     }
     
     LM35A = LM35A/2.046;
     LM35A = LM35A/SOLAN;
  }
  
     
    VOID MAIN()
     {
      SET_UP_PORT_IC_CHOT();
      SETUP_ADC(ADC_CLOCK_DIV_32);
      SETUP_ADC_PORTS(AN0_TO_AN2|VSS_VDD);
     

      SETUP_LCD () ;
      SETUP_GLCD(GLCD_TEXT_MODE);
      
      
      KHOI_TAO_DS18B20();
      DS18A_TAM=0;
      
       DOC_THOI_GIAN_TU_REALTIME();
       IF (MA_DS13 !=MA_DS)
         {
           THIET_LAP_THOI_GIAN_HIEN_TAI();
           NAP_THOI_GIAN_HTAI_VAO_DS13B07();
         }
         
         DOC_THOI_GIAN_TU_REALTIME();
         GIAYTAM=GIAY_DS13;
         
           //HIEN THI VONG TRON GLCD
         SETUP_GLCD(GLCD_GRAPHIC_MODE);
         
         GLCD_MAU_NEN(0);
      
//!      GLCD_CIRCLE(15,40,12,0,1);
      
      GLCD_CIRCLE(13,6,12,0,1);
      GLCD_CIRCLE(13,55,12,0,1);
      
      GLCD_RECT(80,1,105,20,0,1);
      GLCD_RECT(80,45,110,63,0,1);
      
      
      GDRAM_VDK_TO_GDRAM_GLCD_ALL();

     GLCD_COMMAND(GLCD_TEXT_MODE);
       HIEN_THI_8LED_7DOAN_QUET ();
       WHILE(TRUE)
        {
         
             DOC_THOI_GIAN_TU_REALTIME();
            HIEN_THI_8LED_7DOAN_QUET ();
           IF (GIAYTAM!=GIAY_DS13)
            {
              GIAYTAM=GIAY_DS13;
                HIEN_THI_8LED_7DOAN_QUET ();
            }
        IF(TOUCH_PRESENT()) {DOC_GIATRI_DS18B20();}
          HIEN_THI_8LED_7DOAN_QUET ();
          IF(DS18AL != DS18A_TAM)
          {
            DS18A_TAM =DS18AL;
             
              HIEN_THI_8LED_7DOAN_QUET ();
//!            XUAT_4LED_7DOAN_4SO(MA7DOAN[NGUYEN/10],MA7DOAN[NGUYEN%10]&0X7F,MA7DOAN[TP/10],MA7DOAN[TP%10]);
          }
              DOC_ND_LM35A();
            KQ_HT = (INT16)(LM35A * 100);
            
            
            
            //HIEN THI LCD
            GM_LCD();
            HT_LCD();
            
            //HIEN THI 8 LED QUET
             GIAI_MA_GAN_CHO_8LED_QUET () ;
            HIEN_THI_8LED_7DOAN_QUET  ();
            
            //HIEN THI GLCD
            HT_GLCD();
             HIEN_THI_8LED_7DOAN_QUET  ();
          
            
        }
     }
     
     
     
      
