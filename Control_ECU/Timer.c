#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "gpio.h"

/* Global variables to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

ISR(TIMER0_OVF_vect){
    if(g_callBackPtr0 != NULL_PTR) {
        (*g_callBackPtr0)();
    }
}

ISR(TIMER0_COMP_vect) {
    if(g_callBackPtr0 != NULL_PTR) {
        (*g_callBackPtr0)();
    }
}

ISR(TIMER1_OVF_vect) {
    if(g_callBackPtr1 != NULL_PTR) {
        (*g_callBackPtr1)();
    }
}

ISR(TIMER1_COMPA_vect) {
    if(g_callBackPtr1 != NULL_PTR) {
        (*g_callBackPtr1)();
    }
}

ISR(TIMER2_OVF_vect) {
    if(g_callBackPtr2 != NULL_PTR) {
        (*g_callBackPtr2)();
    }
}

ISR(TIMER2_COMP_vect) {
    if (g_callBackPtr2 != NULL_PTR) {
        (*g_callBackPtr2)();
    }
}

void Timer_init(const Timer_ConfigType * Config_Ptr) {
    if(Config_Ptr->timer_ID == Timer0) {
        TCNT0 = Config_Ptr->timer_InitialValue;

        if(Config_Ptr->timer_mode == CompareValue_Mode) {
            OCR0 = Config_Ptr->timer_compare_MatchValue;
            TIMSK |= (1 << OCIE0);
            TCCR0 = (1 << FOC0) | (1 << WGM01) | (TCCR0 & 0xF8) | Config_Ptr->timer_clock;
        } else {
            TIMSK |= (1 << TOIE0);
            TCCR0 = (1 << FOC0) | (TCCR0 & 0xF8) | Config_Ptr->timer_clock;
        }
    }

    if(Config_Ptr->timer_ID == Timer1) {
        TCNT1 = Config_Ptr->timer_InitialValue;

        if(Config_Ptr->timer_mode == CompareValue_Mode) {
            OCR1A = Config_Ptr->timer_compare_MatchValue;
            TIMSK |= (1 << OCIE1A);
            TCCR1A = (1 << FOC1A);
            TCCR1B = (1 << WGM12) | (TCCR1B & 0xF8) | Config_Ptr->timer_clock;
        } else {
            TIMSK |= (1 << TOIE1);
            TCCR1A = (1 << FOC1A) | (1 << FOC1B);
            TCCR1B = (TCCR1B & 0xF8) | Config_Ptr->timer_clock;
        }
    }

    if(Config_Ptr->timer_ID == Timer2) {
        TCNT2 = Config_Ptr->timer_InitialValue;

        if(Config_Ptr->timer_mode == CompareValue_Mode) {
            OCR2 = Config_Ptr->timer_compare_MatchValue;
            TIMSK |= (1 << OCIE2);
            TCCR2 = (1 << FOC2) | (1 << WGM21) | (TCCR2 & 0xF8) | Config_Ptr->timer_clock;
        } else {
            TIMSK |= (1 << TOIE2);
            TCCR2 = (1 << FOC2) | (TCCR2 & 0xF8) | Config_Ptr->timer_clock;
        }
    }
}

void Timer_deInit(Timer_ID_Type timer_type) {
    switch(timer_type) {
        case Timer0:
            TCNT0 = 0;
            TIMSK &= ~((1 << TOIE0) | (1 << OCIE0));
            g_callBackPtr0 = NULL_PTR;
            break;
        case Timer1:
            TCCR1A = 0;
            TCCR1B = 0;
            TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));
            g_callBackPtr1 = NULL_PTR;
            break;
        case Timer2:
            TCCR2 = 0;
            TIMSK &= ~((1 << TOIE2) | (1 << OCIE2));
            g_callBackPtr2 = NULL_PTR;
            break;
    }
}

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID) {
    switch(a_timer_ID) {
        case Timer0:
            g_callBackPtr0 = a_ptr;
            break;
        case Timer1:
            g_callBackPtr1 = a_ptr;
            break;
        case Timer2:
            g_callBackPtr2 = a_ptr;
            break;
    }
}
