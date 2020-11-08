#INCLUDE <TV_PICKIT2_SHIFT_1.C>
#INCLUDE <TV_PICKIT2_SHIFT_DS13B07_I2C.C>

UNSIGNED INT16 K;
UNSIGNED CHAR GIATRI_MOD;

VOID HIEN_THI_GIA_TRI_MOD()
{
   LCD_COMMAND(0X8A);
   LCD_DATA(GIATRI_MOD + 0X30);
}

VOID PHIM_MOD()
{
   IF (!INPUT(MOD))
   {
      DELAY_MS(20);
      {
         IF(!INPUT(MOD))
         {
            IF(GIATRI_MOD<6)  GIATRI_MOD++;
            ELSE              GIATRI_MOD=0;
            HIEN_THI_GIA_TRI_MOD();
            DO{}
            WHILE (!INPUT(MOD));
         }
      }
   }
}

UNSIGNED INT8 HIEU_CHINH_SO_BCD_TANG(UNSIGNED INT8 X)
{
   UNSIGNED INT8 Y;
   Y = X;
   X = X & 0X0F;
   IF (X==0X0A)  Y = Y + 6;
   RETURN (Y);
}

UNSIGNED INT8 HIEU_CHINH_SO_BCD_GIAM(UNSIGNED INT8 X)
{
   UNSIGNED INT8 Y;
   Y = X;
   X = X & 0X0F;
   IF (X==0X0F)  Y = Y - 6;
   RETURN (Y);
}

VOID LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH()
{
   NAP_THOI_GIAN_HTAI_VAO_DS13B07();
   HIEN_THI_THOI_GIAN_DS13B07();
}

VOID PHIM_UP()
{
   IF(!INPUT(UP))
   {
      DELAY_MS(20);
      IF(!INPUT(UP))
      {
         SWITCH (GIATRI_MOD)
         {
            CASE 1: IF (GIAY_DS13==0X59)  GIAY_DS13=0;
                    ELSE 
                    {
                        GIAY_DS13++;
                        PHUT_DS13=HIEU_CHINH_SO_BCD_TANG(GIAY_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
            
            CASE 2: IF (PHUT_DS13==0X59)  PHUT_DS13=0;
                    ELSE 
                    {
                    PHUT_DS13++;
                    PHUT_DS13=HIEU_CHINH_SO_BCD_TANG(PHUT_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
                    
            CASE 3: IF (GIO_DS13==0X23)  GIO_DS13=0;
                    ELSE 
                    {
                    GIO_DS13++;
                    GIO_DS13=HIEU_CHINH_SO_BCD_TANG(GIO_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
                    
            CASE 4: IF (NGAY_DS13==0X31)  GIO_DS13=0;
                    ELSE 
                    {
                    NGAY_DS13++;
                    NGAY_DS13=HIEU_CHINH_SO_BCD_TANG(NGAY_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;      
                    
            CASE 5: IF (THANG_DS13==0X12)  GIO_DS13=0;
                    ELSE 
                    {
                    THANG_DS13++;
                    THANG_DS13=HIEU_CHINH_SO_BCD_TANG(THANG_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
            
            CASE 6: IF (NAM_DS13==0X99)  GIO_DS13=0;
                    ELSE 
                    {
                    NAM_DS13++;
                    NAM_DS13=HIEU_CHINH_SO_BCD_TANG(NAM_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
            DEFAULT:BREAK;
         }
         DO{}
         WHILE(!INPUT(UP));
      }
   }
}

VOID PHIM_DW()
{
   IF(!INPUT(DW))
   {
      DELAY_MS(20);
      IF(!INPUT(DW))
      {
         SWITCH (GIATRI_MOD)
         {
            CASE 1: IF (GIAY_DS13==0)  GIAY_DS13=0X59;
                    ELSE 
                    {
                        GIAY_DS13--;
                        PHUT_DS13=HIEU_CHINH_SO_BCD_GIAM(GIAY_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
            
            CASE 2: IF (PHUT_DS13==0)  PHUT_DS13=0X59;
                    ELSE 
                    {
                    PHUT_DS13--;
                    PHUT_DS13=HIEU_CHINH_SO_BCD_GIAM(PHUT_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
                    
            CASE 3: IF (GIO_DS13==0)  GIO_DS13=0X23;
                    ELSE 
                    {
                    GIO_DS13--;
                    GIO_DS13=HIEU_CHINH_SO_BCD_GIAM(GIO_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
                    
            CASE 4: IF (NGAY_DS13==0)  GIO_DS13=0X31;
                    ELSE 
                    {
                    NGAY_DS13--;
                    NGAY_DS13=HIEU_CHINH_SO_BCD_GIAM(NGAY_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;      
                    
            CASE 5: IF (THANG_DS13==0)  GIO_DS13=0X12;
                    ELSE 
                    {
                    THANG_DS13--;
                    THANG_DS13=HIEU_CHINH_SO_BCD_GIAM(THANG_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
            
            CASE 6: IF (NAM_DS13==0)  GIO_DS13=0X99;
                    ELSE 
                    {
                    NAM_DS13--;
                    NAM_DS13=HIEU_CHINH_SO_BCD_GIAM(NAM_DS13);
                    }
                    LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH();
                    BREAK;
            DEFAULT:BREAK;
         }
         DO{}
         WHILE(!INPUT(DW));
      }
   }
}

VOID NHAP_NHAY_CON_TRO()
{
   SWITCH (GIATRI_MOD)
   {
      CASE 1: LCD_COMMAND(0XD3);
              BREAK;
      CASE 2: LCD_COMMAND(0XD0);
              BREAK;
      CASE 3: LCD_COMMAND(0XCD);
              BREAK;
      CASE 4: LCD_COMMAND(0X8D);
              BREAK;
      CASE 5: LCD_COMMAND(0X90);
              BREAK;
      CASE 6: LCD_COMMAND(0X93);
              BREAK;
      DEFAULT:BREAK;
   }
}

VOID MAIN()
{
   SET_UP_PORT_IC_CHOT();
   SETUP_LCD();
   lcd_command(0x0f);
   LCD_COMMAND(LCD_ADDR_LINE1);
   DOC_THOI_GIAN_TU_REALTIME();
   IF (MA_DS13!=MA_DS)
   {
      THIET_LAP_THOI_GIAN_HIEN_TAI();
      NAP_THOI_GIAN_HTAI_VAO_DS13B07();
   }
   GIATRI_MOD=0;
   HIEN_THI_GIA_TRI_MOD();
   DOC_THOI_GIAN_TU_REALTIME();
   GIAYTAM=GIAY_DS13;
   
   WHILE(TRUE)
   {
      DOC_THOI_GIAN_TU_REALTIME();
      IF(GIAYTAM==GIAY_DS13)
      {
         GIAYTAM=GIAY_DS13;
         HIEN_THI_GIA_TRI_MOD();
         HIEN_THI_THOI_GIAN_DS13B07();
      }
      FOR (K=0; K<10000;K++)
      {
         PHIM_MOD(); PHIM_UP(); PHIM_DW();
      }
      IF(GIATRI_MOD!=0) NHAP_NHAY_CON_TRO();
   }
}
