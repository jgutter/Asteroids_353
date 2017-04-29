#include "timers.h"

#define PRE_SCALE 100

//*****************************************************************************
// Verifies that the base address is a valid GPIO base address
//*****************************************************************************
static bool verify_base_addr(uint32_t base_addr)
{
   switch( base_addr )
   {
     case TIMER0_BASE:
     case TIMER1_BASE:
     case TIMER2_BASE:
     case TIMER3_BASE:
     case TIMER4_BASE:
     case TIMER5_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

//*****************************************************************************
// Returns the RCGC and PR masks for a given TIMER base address
//*****************************************************************************
static bool get_clock_masks(uint32_t base_addr, uint32_t *timer_rcgc_mask, uint32_t *timer_pr_mask)
{
  // Set the timer_rcgc_mask and timer_pr_mask using the appropriate
  // #defines in ../include/sysctrl.h
  switch(base_addr)
  {
    case TIMER0_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R0;
      *timer_pr_mask = SYSCTL_PRTIMER_R0;
      break;
    }
    case TIMER1_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R1;
      *timer_pr_mask = SYSCTL_PRTIMER_R1;
      break;
    }
    case TIMER2_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R2;
      *timer_pr_mask = SYSCTL_PRTIMER_R2;
      break;
    }
    case TIMER3_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R3;
      *timer_pr_mask = SYSCTL_PRTIMER_R3;
      break;
    }
    case TIMER4_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R4;
      *timer_pr_mask = SYSCTL_PRTIMER_R4;
      break;
    }
    case TIMER5_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R5;
      *timer_pr_mask = SYSCTL_PRTIMER_R5;
      break;
    }
    default:
    {
      return false;
    }
  }
  return true;
}


//*****************************************************************************
// Waits for 'ticks' number of clock cycles and then returns.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_wait(uint32_t base_addr, uint32_t ticks)
{
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }

  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;

  //*********************    
  // ADD CODE
  //*********************
	//SADEQ EDITED
  gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);	//disable timer A & B
	gp_timer->TAILR = ticks;							//set timer to ticks
	gp_timer->ICR |= TIMER_ICR_TATOCINT;	//set acknowledge clear 
	gp_timer->CTL |= TIMER_CTL_TAEN;			//enable timer A
	while ((gp_timer->RIS & TIMER_RIS_TATORIS) == 0) {
		
	}
	
  return true;
}


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
bool gp_timer_config_32(uint32_t base_addr, uint32_t mode, bool count_up, bool enable_interrupts)
{
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }
  
  // get the correct RCGC and PR masks for the base address
  get_clock_masks(base_addr, &timer_rcgc_mask, &timer_pr_mask);
  
  // Turn on the clock for the timer
  SYSCTL->RCGCTIMER |= timer_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
  
  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;
    
  //*********************    
  // ADD CODE
  //*********************
   gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);	//stop timer A & B
		//SADEQ EDIT: ~
   gp_timer->CFG &= ~TIMER_CFG_32_BIT_TIMER;		//set as 32 bit timer
		
	 gp_timer->TAMR &= ~TIMER_TAMR_TAMR_M;		//clear Timer A mode bits
	 gp_timer->TAMR |= mode;								//set Timer A mode

		
		
		if (count_up)													//config timers as count up or count down
			gp_timer->TAMR |= TIMER_TAMR_TACDIR;
		else
			gp_timer->TAMR &= ~TIMER_TAMR_TACDIR;
		
		if (enable_interrupts)								// config interrupt timers
			gp_timer->IMR |= TIMER_IMR_TATOIM;
		else
			gp_timer->IMR &= ~TIMER_IMR_TATOIM;
  return true;  
}

//*****************************************************************************
// Configure a general purpose timer to be two 16-bit timers.  
//
// Paramters
//  base_address          The base address of a general purpose timer
//
//  mode                  bit mask for Periodic, One-Shot, or Capture
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
bool gp_timer_config_16(uint32_t base_addr, uint32_t mode_A, uint32_t mode_B, bool count_up, bool enable_interrupts)
{
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }
  
  // get the correct RCGC and PR masks for the base address
  get_clock_masks(base_addr, &timer_rcgc_mask, &timer_pr_mask);
  
  // Turn on the clock for the timer
  SYSCTL->RCGCTIMER |= timer_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
  
  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;
    
  //*********************    
  // 
  //*********************
   gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);	//stop timer A & B
		
		//SADEQ
		gp_timer->CFG = 0; 												//clear cfg register
		gp_timer->CFG |= TIMER_CFG_16_BIT;				//set as 16 bit timers
		
		gp_timer->TAMR &= ~TIMER_TAMR_TAMR_M;		//clear Timer A mode bits
		gp_timer->TBMR &= ~TIMER_TBMR_TBMR_M;		//clear Timer B mode bits
		
		gp_timer->TAMR |= mode_A;								//set Timer A mode
		gp_timer->TBMR |= mode_B;								//set Timer B mode
		
		if (count_up) {													//config timers as count up or count down
			gp_timer->TAMR |= TIMER_TAMR_TACDIR;
			gp_timer->TBMR |= TIMER_TBMR_TBCDIR;
		}
		else {
			gp_timer->TAMR &= ~TIMER_TAMR_TACDIR;
			gp_timer->TBMR &= ~TIMER_TBMR_TBCDIR;
		}
		
		if (enable_interrupts)	{							// config interrupt timers
			gp_timer->IMR |= (TIMER_IMR_TATOIM | TIMER_IMR_TBTOIM);
			NVIC_SetPriority(TIMER0A_IRQn, 1);
			NVIC_SetPriority(TIMER0B_IRQn, 2);
			NVIC_EnableIRQ(TIMER0A_IRQn);
			NVIC_EnableIRQ(TIMER0B_IRQn);
			gp_timer->CTL |= TIMER_CTL_TBOTE; //enable Timer B output Trigger for ADC conversion
		}
		else {
			gp_timer->IMR &= ~(TIMER_IMR_TATOIM | TIMER_IMR_TBTOIM);
		}
  return true;  
}
//*****************************************************************************
// Configures periodic timers A & B for number of clock cycles (ticks) before triggering interrupt
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_period(uint32_t base_addr, uint32_t ticks_A, uint32_t ticks_B)
{
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }

  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;

  gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);	//disable timer A & B
	
	gp_timer->TAPR = PRE_SCALE;
	gp_timer->TBPR = PRE_SCALE;
	gp_timer->TAILR = ticks_A;							//set timer A to ticks_A
	gp_timer->TBILR = ticks_B;							//set timer B to ticks_B
	
	gp_timer->ICR |= TIMER_ICR_TATOCINT;	//clear interrupt for Timer A
	gp_timer->ICR |= TIMER_ICR_TBTOCINT;	//clear interrupt for Timer B
	
	gp_timer->CTL |= (TIMER_CTL_TAEN | TIMER_CTL_TBEN);			//enable timer A & B
	
	return true;
}


