UNSIGNED INT32    Y=0,YP_CHAY=1,YT_CHAY=0X80000000,Y_CODINH=0;
UNSIGNED INT16 ZT,ZT_CHAY_T=0x8000,ZT_CHAY_P=1,ZT_CODINH=0;
UNSIGNED INT16 ZP,ZP_CHAY_T=0X8000,ZP_CHAY_P=1,ZP_CODINH=0;

UNSIGNED INT16 TGDLAY=0;
UNSIGNED INT8 DEM_LED=0; 
SIGNED I32=32,J32=0,TTCT_TD=1,I16=16,J16=0;

UNSIGNED INT32    ZA=1,YA=1,XA=0XFFFFFFFE,ZB=0X80000000,YB=0X80000000,XB=0X7FFFFFFF;   
SIGNED IA=1,JA=1;  
VOID RESET_TOAN_BO_BIEN()
{ 
      TTCT_TD++;     //CHUYEN CHUONG TRINH CHO TU DONG
      Y=0;      YP_CHAY=1;      YT_CHAY=0X80000000;      Y_CODINH=0;
      ZT_CHAY_T=0x8000;    ZT_CHAY_P=1;   ZT_CODINH=0;
      ZP_CHAY_T=0X8000;    ZP_CHAY_P=1;   ZP_CODINH=0;
      ZT=ZP=0;
      I32=32;J32=0;I16=16,J16=0;
      DEM_LED=0;
      
      ZA=1;    YA=1;    XA=0XFFFFFFFE;     IA=1;    JA=1;
     ZB=0X80000000;    YB=0X80000000;    XB=0X7FFFFFFF;
} 

VOID TANG_DEM_LED_DELAY_1(UNSIGNED INT8 DL)
{ 
      UNSIGNED INT8 I;
      FOR (I=0; I<DL;I++)
      HIEN_THI_8LED_7DOAN_QUET_ALL();
      DEM_LED++;
} 

VOID TANG_DEM_LED_DELAY_0(UNSIGNED INT8 DL)
{ 
      IF (DL>0)      DELAY_MS(DL); 
      DEM_LED++;
} 

VOID DELAY_CHON(UNSIGNED INT8 DL,CHONDELAY)
{    
   IF (!CHONDELAY)   TANG_DEM_LED_DELAY_0(DL);
   ELSE              TANG_DEM_LED_DELAY_1(DL);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DON  PHAI SANG TRAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID DIEM_SANG_DICH_TRAI_MAT_DAN_32LED(UNSIGNED INT8 DL,CHONDELAY)
{       
   IF(IA<33)
   {
      IF(JA>0)
      {
         ZB = (ZB << 1);
         Y = XB|ZB;        
         XUAT_32LED_DON_1DW(Y);
         DELAY_CHON(DL,CHONDELAY);
         JA--;
      }
      ELSE 
      {
         IA++;
         JA=IA;      
         YB = YB>>1;
         XB = XB>>1;
         ZB = YB;
      }
   }
   ELSE RESET_TOAN_BO_BIEN();
}  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DON  TRAI SANG PHAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID DIEM_SANG_DICH_PHAI_MAT_DAN_32LED(UNSIGNED INT8 DL,CHONDELAY)
{       
   IF(IA<33)
   {
      IF(JA>0)
      {
         ZA = (ZA >> 1);
         Y = XA|ZA;        
         XUAT_32LED_DON_1DW(Y);
         DELAY_CHON(DL,CHONDELAY);
         JA--;
      }
      ELSE 
      {
         IA++;
         JA=IA;      
         YA = YA<<1;
         XA = XA <<1;
         ZA = YA;
      }
   }
   ELSE RESET_TOAN_BO_BIEN();
}  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: CHOP TAT 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID DAO_DL_32BIT_VA_XUAT()
{
   Y=~Y;
   XUAT_32LED_DON_1DW(Y); 
}
VOID SANG_TAT_32LED(UNSIGNED INT8 DL,CHONDELAY)
{        
      IF (TGDLAY==1)          XUAT_32LED_DON_1DW(Y); 
      ELSE IF (TGDLAY==50)    DAO_DL_32BIT_VA_XUAT();
      ELSE IF (TGDLAY==100)   DAO_DL_32BIT_VA_XUAT();          
      ELSE IF (TGDLAY==150)   DAO_DL_32BIT_VA_XUAT();                 
      ELSE IF (TGDLAY==200)  
      {
         TTCT_TD++;   Y=0;        TGDLAY=0;
      }
      TGDLAY++;
      DELAY_CHON(DL,CHONDELAY);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DAN ROI TAT DAN TU NGOAI VAO
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_TAT_DAN_NGOAI_VAO_32LED(UNSIGNED INT8 DL,CHONDELAY)
{  
   IF (DEM_LED<16)
   {  
      XUAT_32LED_DON_2WORD(ZP,ZT);        
      ZP= (ZP<<1)+1; 
      ZT= (ZT>>1)+0X8000;
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<32)
   {  
      XUAT_32LED_DON_2WORD(ZP,ZT);
      ZP= (ZP<<1); 
      ZT= (ZT>>1);
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE RESET_TOAN_BO_BIEN();

}   
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DAN ROI TAT DAN TU TRONG RA
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_TAT_DAN_TRONG_RA_32LED(UNSIGNED INT8 DL,CHONDELAY)
{  
   IF (DEM_LED<16)
   {   
      XUAT_32LED_DON_2WORD(ZP,ZT); 
      ZP= (ZP>>1)+0X8000; 
      ZT= (ZT<<1)+1;
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<32)
   {  
      XUAT_32LED_DON_2WORD(ZP,ZT);
      ZP= (ZP>>1); 
      ZT= (ZT<<1);
      DELAY_CHON(DL,CHONDELAY);
    }
   ELSE RESET_TOAN_BO_BIEN();
        
}   
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: 2NHOM 16 LED SANG DAN ROI TAT DAN TU PHAI SANG TRAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_TAT_DAN_PHAI_SANG_TRAI_2X16LED(UNSIGNED INT8 DL,CHONDELAY)
{  
   IF (DEM_LED<16)
   {   
      XUAT_32LED_DON_2WORD(ZP,ZP);
      ZP= (ZP>>1)+0X8000;
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<32)
   {  
      XUAT_32LED_DON_2WORD(ZP,ZP);
      ZP= (ZP>>1);
      DELAY_CHON(DL,CHONDELAY);
    }
   ELSE RESET_TOAN_BO_BIEN();
      
}   
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: 2NHOM 16 LED SANG DAN ROI TAT DAN TU TRAI SANG PHAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_TAT_DAN_TRAI_SANG_PHAI_2X16LED(UNSIGNED INT8 DL,CHONDELAY)
{  
   IF (DEM_LED<16)
   {   
      XUAT_32LED_DON_2WORD(ZT,ZT);  
      ZT= (ZT<<1)+1;
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<32)
   {  
      XUAT_32LED_DON_2WORD(ZT,ZT);
      ZT= (ZT<<1);
      DELAY_CHON(DL,CHONDELAY);
    }
   ELSE RESET_TOAN_BO_BIEN();
        
}   
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DAN ROI TAT DAN TU PHAI SANG TRAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_TAT_DAN_PST_32LED(UNSIGNED INT8 DL,CHONDELAY)
{        
   IF (DEM_LED<32)
   {  
      XUAT_32LED_DON_1DW(Y);
      Y= (Y<<1)+1;
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<64)
   {  
      XUAT_32LED_DON_1DW(Y);   
      Y= (Y<<1); 
      DELAY_CHON(DL,CHONDELAY);
   } 
   ELSE RESET_TOAN_BO_BIEN();

}    
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DAN ROI TAT DAN TU TRAI SANG PHAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_TAT_DAN_TSP_32LED(UNSIGNED INT8 DL,CHONDELAY)
{           
      IF (DEM_LED<32)
      {  
         XUAT_32LED_DON_1DW(Y);
         Y= (Y>>1)+0x80000000; 
         DELAY_CHON(DL,CHONDELAY);      
      }
      ELSE
      IF (DEM_LED<64)
      {  
         XUAT_32LED_DON_1DW(Y); 
         Y= (Y>>1);
         DELAY_CHON(DL,CHONDELAY);
      } 
      ELSE RESET_TOAN_BO_BIEN();
    
}         
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: DIEM SANG DI CHUEYN TU PHAI SANG TRAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID DIEM_SANG_DI_CHUYEN_PST_32LED(UNSIGNED INT8 DL,CHONDELAY)
{        
   IF (DEM_LED==0)
   {  
      Y=1;
      XUAT_32LED_DON_1DW(Y);
      Y= (Y<<1);
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<33)
   {  
      XUAT_32LED_DON_1DW(Y);   
      Y= (Y<<1); 
      DELAY_CHON(DL,CHONDELAY);
   } 
   ELSE  RESET_TOAN_BO_BIEN();
}    

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: DIEM SANG DI CHUEYN TU TRAI SANG PHAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID DIEM_SANG_DI_CHUYEN_TSP_32LED(UNSIGNED INT8 DL,CHONDELAY)
{        
   IF (DEM_LED==0)
   {  
      Y=0X80000000;
      XUAT_32LED_DON_1DW(Y);
      Y= (Y>>1);
      DELAY_CHON(DL,CHONDELAY);
   }
   ELSE  IF (DEM_LED<33)
   {  
      XUAT_32LED_DON_1DW(Y);   
      Y= (Y>>1); 
      DELAY_CHON(DL,CHONDELAY);
   } 
   ELSE RESET_TOAN_BO_BIEN();

} 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DON  PHAI SANG TRAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_DON_PST_32LED(UNSIGNED INT8 DL,CHONDELAY)
{       
   IF(I32>0)
   {
      IF(J32<I32)
      {
         Y = Y_CODINH|YP_CHAY;
         XUAT_32LED_DON_1DW(Y);
         DELAY_CHON(DL,CHONDELAY);       
         YP_CHAY = YP_CHAY <<1;
         J32++;
      }
      IF (J32==I32) 
      {
         I32--;
         J32=0;         
         Y_CODINH=Y;
         YP_CHAY = 1;
      }
   }
   ELSE RESET_TOAN_BO_BIEN();
}   
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DON  PHAI SANG TRAI
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_DON_TSP_32LED(UNSIGNED INT8 DL,CHONDELAY)
{       
   IF(I32>0)
   {
      IF(J32<I32)
      {
         Y = Y_CODINH|YT_CHAY;
         XUAT_32LED_DON_1DW(Y);
         DELAY_CHON(DL,CHONDELAY);
         YT_CHAY = YT_CHAY >>1;
         J32++;
      }
      IF (J32==I32) 
      {
         I32--;
         J32=0;         
         Y_CODINH=Y;
         YT_CHAY = 0X80000000;
      }
   }
   ELSE RESET_TOAN_BO_BIEN();

}  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DON  TU NGOAI VAO
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_DON_TNT_32LED(UNSIGNED INT8 DL,CHONDELAY)
{       
   IF(I16>0)
   {
      IF(J16<I16)
      {
         ZP = ZP_CODINH|ZP_CHAY_P;
         ZT = ZT_CODINH|ZT_CHAY_T;
         XUAT_32LED_DON_2WORD(ZT,ZP);
         DELAY_CHON(DL,CHONDELAY);

         ZP_CHAY_P = ZP_CHAY_P <<1;         
         ZT_CHAY_T = ZT_CHAY_T >>1;
         J16++;
      }
      IF (J16==I16) 
      {
         I16--;
         J16=0;         
         ZT_CODINH=ZT;  ZP_CODINH=ZP;         
         ZP_CHAY_P = 1;   ZT_CHAY_T = 0X8000;
      }
   }
   ELSE RESET_TOAN_BO_BIEN();

}   

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//32 LED: SANG DON  TU NGOAI VAO
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
VOID SANG_DON_TTR_32LED(UNSIGNED INT8 DL,CHONDELAY)
{       
   IF(I16>0)
   {
      IF(J16<I16)
      {
         ZP = ZP_CODINH|ZP_CHAY_T;
         ZT = ZT_CODINH|ZT_CHAY_P;
         XUAT_32LED_DON_2WORD(ZT,ZP);
         DELAY_CHON(DL,CHONDELAY);
         ZP_CHAY_T = ZP_CHAY_T >>1;         
         ZT_CHAY_P = ZT_CHAY_P <<1;
         J16++;
      }
      IF (J16==I16) 
      {
         I16--;
         J16=0;         
         ZT_CODINH=ZT;  
         ZP_CODINH=ZP;
         ZP_CHAY_T = 0X8000;   ZT_CHAY_P = 1;
      }
   }
   ELSE RESET_TOAN_BO_BIEN();
}   
