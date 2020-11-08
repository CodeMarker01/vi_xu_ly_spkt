
#include <tv_pickit2_shift_1.c>                                               
#include <tv_pickit2_shift_key4x4_138.c>                     

unsigned INT8 mp;                                                   
unsigned INT8 y=0;                                                       
void main()
{
   
   set_up_port_ic_chot ();
   set_tris_b (0x3c);
   xuat_32led_don_4byte (0, 0, 0, y);

   WHILE (true)
   {
      mp = key_4x4_dw ();
      
      IF (mp != 0xff)
      {
         IF (mp == 0)
         {
            y = 0b00000001|y;
         }

         IF (mp == 1)
         {
            y = 0b00000010|y;
         }

         
         IF (mp == 2)
         {
            y = 0b00000100|y;
         }

         
         IF (mp == 3)
         {
            y = 0b00001000|y;
         }

         
         IF (mp == 4)
         {
            y = 0b00010000|y;
         }

         
         IF (mp == 5)
         {
            y = 0b00100000|y;
         }

         
         IF (mp == 6)
         {
            y = 0b01000000|y;
         }

         
         IF (mp == 7)
         {
            y = 0b10000000|y;
         }

         
         IF (mp == 8)
         {
            y = 0b11111110&y;
         }

         IF (mp == 9)
         {
            y = 0b11111101&y;
         }

         
         IF (mp == 10)
         {
            y = 0b11111011&y;
         }

         
         IF (mp == 11)
         {
            y = 0b11110111&y;
         }

         
         IF (mp == 12)
         {
            y = 0b11101111&y;
         }

         
         IF (mp == 13)
         {
            y = 0b11011111&y;
         }

         
         IF (mp == 14)
         {
            y = 0b10111111&y;
         }

         
         IF (mp == 15)
         {
            y = 0b01111111&y;
         }

         xuat_32led_don_4byte (0, 0, 0, y);
      }
   }
}

   
