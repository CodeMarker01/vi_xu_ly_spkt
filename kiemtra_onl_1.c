#INCLUDE    <TV_PICKIT2_SHIFT_1.c>

UNSIGNED    INT8    I;

UNSIGNED    LONG LONG    Y;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

VOID MAIN()

{        SET_UP_PORT_IC_CHOT();

         Y=0;

         WHILE(TRUE)

{

               FOR(I=0;I<16;I++)

{

                        XUAT_32LED_DON_1DW(Y);

                        DELAY_MS(1000);

                        Y=(Y<<2)+3;

}

               FOR(I=0;I<16;I++)

{

                        XUAT_32LED_DON_1DW(Y);

                        DELAY_MS(1000);

                        Y=(Y<<2);

}

}

}
