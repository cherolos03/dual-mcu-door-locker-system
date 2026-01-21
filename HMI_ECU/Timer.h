#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

typedef enum {
    Timer0,
    Timer1,
    Timer2
} Timer_ID_Type;


typedef enum {
    NO_CLOCK = 0,       // No clock source
    F_CPU_CLOCK = 1,    // Clock = F_CPU
    F_CPU_8 = 8,        // Clock = F_CPU / 8
    F_CPU_64 = 64,      // Clock = F_CPU / 64
    F_CPU_256 = 256,    // Clock = F_CPU / 256
    F_CPU_1024 = 1024,  // Clock = F_CPU / 1024
    // For Timer2 specific prescalers
    F_CPU_32_T2 = 32,   // Clock = F_CPU / 32 (for Timer2)
    F_CPU_128_T2 = 128, // Clock = F_CPU / 128 (for Timer2)
    F_CPU_256_T2 = 256, // Clock = F_CPU / 256 (for Timer2)
    F_CPU_1024_T2 = 1024 // Clock = F_CPU / 1024 (for Timer2)
} Timer_ClockType;



typedef enum {
    Normal_Mode,
    CompareValue_Mode
} Timer_ModeType;

typedef struct {
    uint16 timer_InitialValue;
    uint16 timer_compare_MatchValue; /* Used in Compare mode only */
    Timer_ID_Type timer_ID;
    Timer_ClockType timer_clock;
    Timer_ModeType timer_mode;
} Timer_ConfigType;

/* Function Prototypes */
void Timer_init(const Timer_ConfigType * Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_type);
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* TIMER_H_ */
