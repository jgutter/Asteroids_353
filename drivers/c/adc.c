// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "adc.h"
#include "driver_defines.h"

/******************************************************************************
 * Initializes ADC to use Sample Sequencer #3, triggered by the processor,
 * no IRQs
 *****************************************************************************/
bool initialize_adc(  uint32_t adc_base )
{
  ADC0_Type  *myADC;
  uint32_t rcgc_adc_mask;
  uint32_t pr_mask;
  

  // examine the adc_base.  Verify that it is either ADC0 or ADC1
  // Set the rcgc_adc_mask and pr_mask  
  switch (adc_base) 
  {
    case ADC0_BASE :
    {
      
      //
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R0;
      //
      // Set pr_mask 
      pr_mask = SYSCTL_PRADC_R0;
      break;
    }
    case ADC1_BASE :
    {
      //
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R1;
      //
      // Set pr_mask 
      pr_mask = SYSCTL_PRADC_R1;
      break;
    }
    
    default:
      return false;
  }
  
  // Turn on the ADC Clock
  SYSCTL->RCGCADC |= rcgc_adc_mask;
  
  // Wait for ADCx to become ready
  while( (pr_mask & SYSCTL->PRADC) != pr_mask){}
    
  // Type Cast adc_base and set it to myADC
  myADC = (ADC0_Type *)adc_base;
  
  // ADD CODE
  // disable sample sequencer #3 by writing a 0 to the 
  // corresponding ASENn bit in the ADCACTSS register 
	myADC->ACTSS &= ~ADC_ACTSS_ASEN3;
  // ADD CODE
  // Set the event multiplexer to trigger conversion on a processor trigger
  // for sample sequencer #3.
	myADC->EMUX  |= ADC_EMUX_EM3_PROCESSOR;
  // ADD CODE
  // Set IE0 and END0 in SSCTL3
  myADC->SSCTL3 |= ADC_SSCTL3_END0;
	myADC->SSCTL3 |= ADC_SSCTL3_IE0;	
  return true;
}

/******************************************************************************
 * Initializes ADC to use Sample Sequencer #2, triggered by the processor,
 * IRQs enabled
 *****************************************************************************/
bool initialize_adc_HW3(  uint32_t adc_base )
{
  ADC0_Type  *myADC;
  uint32_t rcgc_adc_mask;
  uint32_t pr_mask;
  

  // examine the adc_base.  Verify that it is either ADC0 or ADC1
  // Set the rcgc_adc_mask and pr_mask  
  switch (adc_base) 
  {
    case ADC0_BASE :
    {
      
      //
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R0;
      //
      // Set pr_mask 
      pr_mask = SYSCTL_PRADC_R0;
      break;
    }
    case ADC1_BASE :
    {
      //
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R1;
      //
      // Set pr_mask 
      pr_mask = SYSCTL_PRADC_R1;
      break;
    }
    
    default:
      return false;
  }
  
  // Turn on the ADC Clock
  SYSCTL->RCGCADC |= rcgc_adc_mask;
  
  // Wait for ADCx to become ready
  while( (pr_mask & SYSCTL->PRADC) != pr_mask){}
    
  // Type Cast adc_base and set it to myADC
  myADC = (ADC0_Type *)adc_base;
  
  //
  // disable sample sequencer #2 by writing a 0 to the 
  // corresponding ASENn bit in the ADCACTSS register 
	myADC->ACTSS &= ~ADC_ACTSS_ASEN2;
  //
  // Set the event multiplexer to trigger conversion on a timer trigger
  // for sample sequencer #2.
	myADC->EMUX  |= ADC_EMUX_EM2_TIMER;
	
	
  // Set IE0 and END0 in SSCTL2
  myADC->SSCTL2 |= ADC_SSCTL2_END1; //last sample will be sample 1 (PS2 Y)
	//myADC->SSCTL2 |= ADC_SSCTL2_IE0;	//interrupt after first sample is complete
	myADC->SSCTL2 |= ADC_SSCTL2_IE1;	//Interrupt will be generate after second and last sample is completed
	myADC->SSMUX2 |= 0x0; //set first sample input for PS2_X
	myADC->SSMUX2 |= (0x1 << 4); //set second sample input for PS2_Y
	myADC->IM |= ADC_IM_MASK2; //enable interrupts for Sample sequencer 2
	NVIC_SetPriority(ADC0SS2_IRQn, 3); //set nested vector interrupt priority to 3
	NVIC_EnableIRQ(ADC0SS2_IRQn);		//enabled nested vector interrupt
	myADC->ACTSS |= ADC_ACTSS_ASEN2; //re-enable sample sequencer
	return true;
}


/******************************************************************************
 * Reads SSMUX3 for the given ADC.  Busy waits until completion
 *****************************************************************************/
uint32_t get_adc_value( uint32_t adc_base, uint8_t channel)
{
  ADC0_Type  *myADC;
  uint32_t result;
  
  if( adc_base == 0)
  {
    return false;
  }
  
  myADC = (ADC0_Type *)adc_base;
  
  myADC->SSMUX3 = channel;          // Set the Channel
  
  myADC->ACTSS |= ADC_ACTSS_ASEN3;  // Enable SS3
  
  myADC->PSSI =   ADC_PSSI_SS3;     // Start SS3
  
  while( (myADC->RIS & ADC_RIS_INR3)  == 0)
  {
    // wait
  }
  
  result = myADC->SSFIFO3 & 0xFFF;    // Read 12-bit data
  
  myADC->ISC  = ADC_ISC_IN3;          // Ack the conversion
  
  return result;
}

