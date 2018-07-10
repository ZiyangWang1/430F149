
#include "configuration.h"

int main( void )
{
  u8 au8DisplayNumber[8] = {1,2,3,4,5,6,7,8};
  u8 u8DisplayMask = 0xF1;
  u8 u8DisplayDot = 0x01;
  u16 u16DisplayShift = 0x01;
  u16 i = 0;
  
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P2SEL = 0x00;
  P4SEL = 0x00;
  P5SEL &= ~PX_5_Location;
  P6SEL &= ~PX_6_Location;
  
  P2DIR = 0xFF;
  P4DIR = 0xFF;
  P5DIR |= PX_5_Location;
  P6DIR |= PX_6_Location;
  
  P2OUT = 0x00;
  P4OUT = 0x00;
  P5OUT &= ~PX_5_Location;
  P6OUT &= ~PX_6_Location;
  
  for (;;)
  {
    i++;
    u16DisplayShift = u16DisplayShift << 1;
    
    if(u16DisplayShift == 0x100)
    {
      u16DisplayShift = 0x01;
    }
    
    _74HC573_SendByte(0x00);
    P6OUT |= PX_6_Location;
    P6OUT &= ~PX_6_Location;
    _74HC573_SendByte(~u16DisplayShift);
    P5OUT |= PX_5_Location;
    P5OUT &= ~PX_5_Location;
    _74HC573_Display(au8DisplayNumber,u8DisplayMask,u8DisplayDot,u16DisplayShift);
    
    if(i==5000)
    {
      //P2OUT ^= 0x08;
      
      i = 0;
    }
    
  }

}
