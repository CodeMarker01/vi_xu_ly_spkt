/* DE BAI: CHUONG TRINH DOC THOI GIAN THUC HIEN THI LCD 20X4 */

   #INCLUDE <TV_PICKIT2_SHIFT_1.C>
   #INCLUDE <TV_PICKIT2_SHIFT_DS13B07_I2C.C>
    #INCLUDE <TV_PICKIT2_SHIFT_GLCD128X64.C>
     #INCLUDE <GRAPHICS.C>
    SIGNED INT8  I;
    
    UNSIGNED INT16 GIAY_1,GIAY_2,PHUT_1,PHUT_2,GIO_1,GIO_2;
 
   VOID HT_DS13B07 ( )
{     LCD_COMMAND (0x8C);   
      LCD_DATA(GIO_DS13/16  +0X30);    LCD_DATA(GIO_DS13%16  +0X30);
      LCD_DATA(' ');
      LCD_DATA(PHUT_DS13/16 +0X30);    LCD_DATA(PHUT_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(GIAY_DS13/16 +0X30);    LCD_DATA(GIAY_DS13%16 +0X30);
      LCD_COMMAND (0x98);
      LCD_DATA("THU");

//!        IF(THU_DS13!=1) LCD_DATA(THU_DS13 +0X30);
//!        ELSE LCD_DATA("CN");
//!      LCD_DATA(' ');
//!      LCD_DATA(NGAY_DS13/16 +0X30);    LCD_DATA(NGAY_DS13%16 +0X30);
//!      LCD_DATA(' ');
//!      LCD_DATA(THANG_DS13/16 +0X30);   LCD_DATA(THANG_DS13%16 +0X30);
//!      LCD_DATA(' ');
//!      LCD_DATA(NAM_DS13/16 +0X30);     LCD_DATA(NAM_DS13%16 +0X30); 
}
VOID LCD_HIENTHI_SO_Z_TOADO_XY(SIGNED INT8 LCD_SO,X1,Y1)
     {
       LCD_GOTO_XY(X1,Y1);
       FOR(I=0;I<6;I++)
        {
          IF  (I==3)   LCD_GOTO_XY(X1+1,Y1);
          LCD_DATA(LCD_SO_X[LCD_SO] [I]);
        }
     }
     
     VOID HT_LCD()
     {
     LCD_GOTO_XY(0,0);
     LCD_DATA("GIO");
     
     LCD_GOTO_XY(0,7);
     LCD_DATA("PHUT");
     
     LCD_GOTO_XY(0,17);
     LCD_DATA("GIAY");
     
     
     }
     
      VOID HIENTHI_LCD_KTL ()
    {
       LCD_HIENTHI_SO_Z_TOADO_XY (GIO_DS13/16, 2, 0) ;
       LCD_HIENTHI_SO_Z_TOADO_XY (GIO_DS13%16, 2, 3) ;
       
       LCD_HIENTHI_SO_Z_TOADO_XY (PHUT_DS13/16, 2, 7) ;  
       LCD_HIENTHI_SO_Z_TOADO_XY (PHUT_DS13%16, 2, 10) ;   
       
       LCD_HIENTHI_SO_Z_TOADO_XY (GIAY_DS13/16, 2, 14) ; 
       LCD_HIENTHI_SO_Z_TOADO_XY (GIAY_DS13%16, 2, 17) ;
    }
    
     VOID GM_GLCD ()
   {
       GIO_1 = GIO_DS13/16 % 10 + 0X30;
       GIO_2 = GIO_DS13%16 + 0X30;
       
       PHUT_1 = PHUT_DS13/16 + 0X30;
       PHUT_2=PHUT_DS13%16+0X30;
       
       GIAY_1= GIAY_DS13/16 + 0X30;
       GIAY_2= GIAY_DS13%16 + 0X30;
       
   }
     
      VOID HT_GLCD()
       {
       GLCD_COMMAND(GLCD_ADDR_LINE3);
       GLCD_DATA(" ");
       
       GLCD_DATA(GIO_1);
       GLCD_DATA(GIO_2);
       GLCD_DATA("   ");
       
       
       
       GLCD_DATA(PHUT_1);
       GLCD_DATA(PHUT_2);
       
       GLCD_DATA("    ");
       
       GLCD_DATA(GIAY_1);
       GLCD_DATA(GIAY_2);
       
       GLCD_COMMAND(GLCD_ADDR_LINE1);
       GLCD_DATA("GIO");
       GLCD_DATA(" ");
      
       GLCD_DATA("PHUT");
       GLCD_DATA(" ");
      
       GLCD_DATA("GIAY");
       
       }
    
     

 VOID GIAI_MA_GAN_CHO_8LED_QUET ()
  {
     LED_7DQ[7] = MA7DOAN [GIO_DS13/16];
     LED_7DQ[6] = MA7DOAN [GIO_DS13%16];
     
     LED_7DQ[5] = 0XBF;
    
    LED_7DQ[4] = MA7DOAN [PHUT_DS13/16];
    LED_7DQ[3] = MA7DOAN [PHUT_DS13%16];
    
     LED_7DQ[2] = 0XBF;;
    
    LED_7DQ[1] = MA7DOAN [GIAY_DS13/16];
    LED_7DQ[0] = MA7DOAN [GIAY_DS13%16];
    
  }
    VOID MAIN()
     {
       SET_UP_PORT_IC_CHOT();
       
       SETUP_GLCD(GLCD_TEXT_MODE);
       SETUP_LCD();
       
      
       
     
       
       
       
       DOC_THOI_GIAN_TU_REALTIME();
       IF (MA_DS13 !=MA_DS)
         {
           THIET_LAP_THOI_GIAN_HIEN_TAI();
           NAP_THOI_GIAN_HTAI_VAO_DS13B07();
         }
         
         DOC_THOI_GIAN_TU_REALTIME();
         GIAYTAM=GIAY_DS13;
         
         LCD_COMMAND(0X40);
        FOR(I=0;I<64;I++)
         {
          LCD_DATA(LCD_MA_8DOAN[I]);
         }
         
         
//!         //HIEN THI VONG TRON GLCD
         SETUP_GLCD(GLCD_GRAPHIC_MODE);
         
      GLCD_MAU_NEN(0);
      
//!      GLCD_CIRCLE(15,40,12,0,1);
      GLCD_RECT(4,30,32,48,0,1);
      GLCD_CIRCLE(60,40,12,0,1);
      GLCD_CIRCLE(105,40,12,0,1);
      
      
      GDRAM_VDK_TO_GDRAM_GLCD_ALL();

     GLCD_COMMAND(GLCD_TEXT_MODE);
         
         WHILE(TRUE)
          {
           DOC_THOI_GIAN_TU_REALTIME();
           HIEN_THI_8LED_7DOAN_QUET  ();
           IF (GIAYTAM!=GIAY_DS13)
            {
              GIAYTAM=GIAY_DS13;
              
              GIAI_MA_GAN_CHO_8LED_QUET () ;
              HIEN_THI_8LED_7DOAN_QUET  ();
              
              HT_LCD();
              HIENTHI_LCD_KTL ();
              
              
              GM_GLCD();
              HT_GLCD();
              
              
              
            }
            
          }
     }

