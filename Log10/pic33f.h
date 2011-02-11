#define USE_EC_CLOCK

#if defined(USE_EC_CLOCK)
#define FCY		40000000UL
#else
#error
#define FCY		25000000UL
#endif

#define _DI()		__asm__ volatile("disi #0x3FFF")
#define _EI()		__asm__ volatile("disi #0")

