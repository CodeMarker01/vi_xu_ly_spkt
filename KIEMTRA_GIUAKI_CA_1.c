/*
* 1. Timer 5-15 LCD chu to d_XX voi XX l� gi�y
* 2. Counter 6-12, led qu�t, hien thi 6 led giua = Y_ _ Z =, 
*     voi Y l� don vi, Z l� chuc.
* 3. Bam n�t C ma tran ph�m, doi vi tr� XX sang YZ v� nguoc lai.
* 4. Counter < 10 s�ng 32 led ngo�i v�o trong, > 10 trong ra ngo�i.
*/

#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_32led_don.c>
#include <tv_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int1 tt_ht;
signed int8 giay, bdn, i, mp;
unsigned int8 ch_lcd, dv_lcd, t0;
const unsigned char chu_to_lcd[2][6] = {32, 32, 7, 7, 6, 7,   //d
                                        32, 32, 32, 3, 3, 3}; //_

#int_timer1
void interrupt_timer1() {
    bdn++;
    set_timer1(3036);
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, signed int8 x1, signed int8 y1) {
    lcd_goto_xy(x1, y1);
    for (i = 0; i < 6; i++) {
        if (i == 3)
            lcd_goto_xy(x1 + 1, y1);
        lcd_data(lcd_so_x[lcd_so][i]);
    }
}

void lcd_xoa_so_0_toado_xy(signed int8 x1, signed int8 y1) {
    lcd_goto_xy(x1, y1);
    for (i = 0; i < 6; i++) {
        if (i == 3)
            lcd_goto_xy(x1 + 1, y1);
        lcd_data(0x20);
    }
}

void lcd_hienthi_chu_toado_xy(signed int8 lcd_chu, signed int8 x1, signed int8 y1) {
    lcd_goto_xy(x1, y1);
    for (i = 0; i < 6; i++) {
        if (i == 3)
            lcd_goto_xy(x1 + 1, y1);
        lcd_data(chu_to_lcd[lcd_chu][i]);
    }
}

void giai_ma_hien_thi_lcd() {
    if (!tt_ht) {
        ch_lcd = giay / 10;
        dv_lcd = giay % 10;

        if (ch_lcd == 0) {
            lcd_xoa_so_0_toado_xy(2, 10);
        } else {
            lcd_hienthi_so_z_toado_xy(ch_lcd, 2, 10);
        }
        lcd_hienthi_so_z_toado_xy(dv_lcd, 2, 13);
    } else {
        dv_lcd = t0 % 10;
        ch_lcd = t0 / 10;

        lcd_hienthi_so_z_toado_xy(dv_lcd, 2, 10);
        if (ch_lcd == 0) {
            lcd_xoa_so_0_toado_xy(2, 13);
        } else {
            lcd_hienthi_so_z_toado_xy(ch_lcd, 2, 13);
        }
    }
}

void giai_ma_hien_thi_8led() {
    if (!tt_ht) {
        led_7dq[5] = ma7doan[t0 % 10];
        led_7dq[2] = ma7doan[t0 / 10];
        if (led_7dq[2] == 0xc0) {
            led_7dq[2] = 0xff;
        }
    } else {
        led_7dq[5] = ma7doan[giay / 10];
        led_7dq[2] = ma7doan[giay % 10];
        if (led_7dq[5] == 0xc0) {
            led_7dq[5] = 0xff;
        }
    }
    hien_thi_8led_7doan_quet_all();
}

void main() {
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);

    giay = 5;
    bdn = 0;

    setup_lcd();
    lcd_command(0x40);
    for (i = 0; i < 64; i++) {
        lcd_data(lcd_ma_8doan[i]);
    }
    lcd_hienthi_chu_toado_xy(0, 2, 4);
    lcd_hienthi_chu_toado_xy(1, 2, 7);

    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(6);

    led_7dq[1] = 0b10110111;
    led_7dq[6] = 0b10110111;
    led_7dq[3] = 0b11110111;
    led_7dq[4] = 0b11110111;

    tt_ht = 0;

    while (true) {
        if (bdn < 10) {
            giai_ma_hien_thi_8led();
            giai_ma_hien_thi_lcd();
        } else {
            bdn = bdn - 10;
            giay++;
            if (giay > 15) {
                giay = 5;
            }
        }

        t0 = get_timer0();
        if (t0 > 12) {
            set_timer0(6);
            t0 = get_timer0();
        }
        giai_ma_hien_thi_8led();
        giai_ma_hien_thi_lcd();

        if (t0 < 10) {
            sang_tat_dan_ngoai_vao_32led(500, 1);
        } else {
            sang_tat_dan_trong_ra_32led(500, 1);
        }

        mp = key_4x4_dw();
        if (mp != 0xff) {
            if (mp == 0x0c) {
                tt_ht = ~tt_ht;
            }
        }
    }
}
