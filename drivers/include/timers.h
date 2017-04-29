#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdbool.h>
#include <stdint.h>

#include "driver_defines.h"


//*****************************************************************************
// Configure a general purpose timer to be a 32-bit timer.  
//
// Paramters
//  base_address          The base address of a general purpose timer
//
//  mode                  bit mask for Periodic, One-Shot, or Capture
//
//  count_up              When true, the timer counts up.  When false, it counts
//                        down
//
//  enable_interrupts     When set to true, the timer generates and interrupt
//                        when the timer expires.  When set to false, the timer
//                        does not generate interrupts.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_config_32(uint32_t base_addr, uint32_t mode, bool count_up, bool enable_interrupts);

//*****************************************************************************
// Configure a general purpose timer to be two 16-bit timers.  
//
// Paramters
//  base_address          The base address of a general purpose timer
//
//  mode_A                Timer A bit mask for Periodic, One-Shot, or Capture
//
//	mode_B								Timer B bit mask for Periodic, One-Shot, or Capture
//
//  count_up              When true, the timers counts up.  When false, they count
//                        down
//
//  enable_interrupts     When set to true, the timers generate and interrupt
//                        when the timer expires.  When set to false, the timers
//                        do not generate interrupts.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_config_16(uint32_t base_addr, uint32_t mode_A, uint32_t mode_B, bool count_up, bool enable_interrupts);
//*****************************************************************************
// Waits for 'ticks' number of clock cycles and then returns.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_wait(uint32_t base_addr, uint32_t ticks);
//*****************************************************************************
// Configures periodic timers A & B for number of clock cycles (ticks) before triggering interrupt
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_period(uint32_t base_addr, uint32_t ticks_A, uint32_t ticks_B);


#endif
