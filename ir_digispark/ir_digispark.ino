uint32_t irdata = 0, keydata = 0;
volatile uint8_t m = 0, tcnt = 0;
bool complete = false, startflag = false, media_mode = true;

#include <avr/delay.h>
#include "TrinketHidCombo.h"

void setup() {
    DDRB |= 1 << DDB1;
    PORTB |= 1 << PB2;
    GIMSK |= 1 << INT0;
    MCUCR |= 1 << ISC00;
    GTCCR |= 1 << PSR0;
    TCCR0A = 0;
    TCCR0B = (1 << CS02) | (1 << CS00);
    TIMSK = 1 << TOIE0;
    TrinketHidCombo.begin();
}

void loop() {
    if (complete) {
        if (media_mode) {
            switch (keydata) {
                case 0xC00B87EE: // UP
                    TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);
                    break;
                case 0xC00D87EE: // DOWN
                    TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_DOWN);
                    break;
                case 0xC00887EE: // left
                    TrinketHidCombo.pressMultimediaKey(MMKEY_SCAN_PREV_TRACK);
                    break;
                case 0xC00787EE: // right
                    TrinketHidCombo.pressMultimediaKey(MMKEY_SCAN_NEXT_TRACK);
                    break;
                case 0xC05D87EE: // center
                    TrinketHidCombo.pressMultimediaKey(MMKEY_MUTE);
                    break;
                case 0xC00287EE: // menu
                    media_mode = false;
                    break;
                case 0xC05E87EE: // play pause
                    TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
                    break;
            }
        } else {
            switch (keydata) {
                case 0xC00B87EE: // UP
                    TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP);
                    break;
                case 0xC00D87EE: // DOWN
                    TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN);
                    break;
                case 0xC00887EE: // left
                    TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT);
                    break;
                case 0xC00787EE: // right
                    TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT);
                    break;
                case 0xC05D87EE: // center
                    TrinketHidCombo.pressKey(0, KEYCODE_SPACE);
                    break;
                case 0xC00287EE: // menu
                    media_mode = true;
                    break;
                case 0xC05E87EE: // play pause
                    TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
                    break;
            }
            TrinketHidCombo.pressKey(0, 0);
        }

        ms_delay(50);
        complete = 0;
    }

    _delay_ms(1);
    TrinketHidCombo.poll();
}

ISR (INT0_vect) {
    if (PINB& 1<<2) {
        TCNT0 = 0;
    }
    else {
        tcnt = TCNT0;
        if (startflag) {
            if (30 > tcnt && tcnt > 2) {
                if (tcnt > 15 && m < 32) { irdata |= ((uint32_t) 1 << m); }
                m++;
            }
        } else startflag = 1;
    }
}

ISR (TIMER0_OVF_vect) {
    if (m) {
        complete = 1;
        m = 0;
        startflag = 0;
        keydata = irdata;
        irdata = 0;
    }
}

void ms_delay(uint16_t x) {
    for (uint16_t m = 0; m < (x / 10); m++) {
        _delay_ms(10);
        TrinketHidCombo.poll();
    }
}  
